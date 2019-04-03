#include "huffman.h"
#include <fstream>
#include <queue>

using namespace HuffmanCode;

const char*
Exception::what() const noexcept {
    return &desc[0];
}

Exception::Exception(const std::string& _desc)
    : desc(_desc) {}

Node::Node(uint8_t _val)
    : val(_val)
    , e{ 0, 0 } {}

Node::Node(Node* l, Node* r)
    : val(0)
    , e({ std::unique_ptr<Node>(l), std::unique_ptr<Node>(r) }) {
}

bool Node::isLeaf() const {
    return e[0] == nullptr && e[1] == nullptr;
}

void Node::print(Printer& printer) const {
    if (isLeaf()) {
        printer.printBit(0);
        printer.printByte(val);
        if (!printer)
            throw WriteException("Cant write metainfo");
    } else {
        printer.printBit(1);
        if (!printer)
            throw WriteException("Cant write metainfo");
        for (const std::unique_ptr<Node>& son : e)
            son->print(printer);
    }
}

void Node::calcCodes(std::vector<bool> code[BIT_CAPASITY]) const {
    std::vector<bool> pref;
    calcCodesRec(code, pref);
}

void Node::calcCodesRec(std::vector<bool> code[BIT_CAPASITY], std::vector<bool>& pref) const {
    for (int i = 0; i <= 1; i++) {
        if (e[i] != nullptr) {
            pref.push_back(i);
            e[i]->calcCodesRec(code, pref);
            pref.pop_back();
        }
    }

    if (isLeaf())
        code[val] = pref;
}

uint8_t Node::findValue(std::vector<bool>::iterator& it, std::vector<bool>::iterator end) const {
    if (isLeaf())
        return val;
    if (it >= end)
        throw Exception("find: Not enough bits");
    int t = *it;
    return e[t]->findValue(++it, end);
}

Node::Node(Reader& reader)
    : e{ 0, 0 } {
    if (reader.readBit()) {
        if (!reader)
            throw ReadException("Not enough metainfo");
        for (std::unique_ptr<Node>& son : e)
            son.reset(new Node(reader));
    } else {
        if (!reader)
            throw ReadException("Not enough metainfo");
        val = reader.readByte();
    }
}

Node::~Node() {}

Archiver::Archiver(const std::vector<Archiver::KeyFrequency>& keyFreq) {
    typedef std::pair<int64_t, Node*> tmp;
    std::priority_queue<tmp, std::vector<tmp>, std::greater<tmp>> q;

    for (auto i : keyFreq)
        q.push({ i.freq, new Node(i.key) });

    while (q.size() < 2)
        q.push({ 0, new Node(0) });

    while (q.size() > 1) {
        auto a = q.top();
        q.pop();
        auto b = q.top();
        q.pop();
        q.push({ a.first + b.first, new Node(a.second, b.second) });
    }
    root.reset(q.top().second);
    root->calcCodes(code);
}

std::vector<bool> Archiver::encode(uint8_t key) {
    return code[key];
}

void Archiver::printMetaInfo(Printer& printer) {
    root->print(printer);
}

Archiver::~Archiver() {}

Decoder::Decoder(Reader& reader)
    : root(new Node(reader)) {
    if (root->isLeaf()) {
        throw Exception("Bad metainfo");
    }
}

uint8_t Decoder::decodeNext(std::vector<bool>::iterator& it, std::vector<bool>::iterator end) {
    return root->findValue(it, end);
}

std::vector<uint8_t> Decoder::decodeAll(std::vector<bool>::iterator first, std::vector<bool>::iterator second) {
    std::vector<uint8_t> res;
    while (first < second)
        res.push_back(decodeNext(first, second));
    return res;
}

Decoder::~Decoder() {}

FileSizeInfo HuffmanCode::encode(const std::vector<uint8_t>& vin, std::ostream& fout) {
    FileSizeInfo ret;
    ret.uncompressed = vin.size();

    int64_t cnt[BIT_CAPASITY] = {};
    for (uint8_t i : vin)
        cnt[i]++;
    std::vector<Archiver::KeyFrequency> keyFreq;
    for (std::size_t i = 0; i < BIT_CAPASITY; i++)
        if (cnt[i] != 0)
            keyFreq.push_back({ static_cast<uint8_t>(i), cnt[i] });

    Archiver arch(keyFreq);
    Printer printer(fout);
    arch.printMetaInfo(printer);
    ret.metaData = printer.writeCnt();

    std::vector<bool> encoded;
    for (uint8_t i : vin) {
        encoded = arch.encode(i);
        for (bool j : encoded)
            printer.printBit(j);
    }

    ret.compressedData = printer.writeCnt() - ret.metaData;
    printer.printBit(1); // last 1 is end of file
    printer.flush();
    ret.metaData = printer.writeCnt() - ret.compressedData;
    return ret;
}

std::pair<std::vector<uint8_t>, FileSizeInfo> HuffmanCode::decode(std::istream& fin) {
    FileSizeInfo ret;
    Reader reader(fin);
    Decoder dec(reader);
    ret.metaData = reader.readCnt();

    std::vector<bool> content;
    while (reader)
        content.push_back(reader.readBit());
    ret.compressedData = reader.readCnt() - ret.metaData;

    while (!content.empty() && content.back() == 0) {
        content.pop_back();
        ret.compressedData--;
        ret.metaData++;
    }
    if (!content.empty()) {
        content.pop_back();
        ret.compressedData--;
        ret.metaData++;
    } else
        throw Exception("Bad file content");

    std::vector<uint8_t> v = dec.decodeAll(content.begin(), content.end());
    ret.uncompressed = v.size();
    return { v, ret };
}
