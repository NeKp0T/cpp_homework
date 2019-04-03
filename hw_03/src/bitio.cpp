#include "bitio.h"

Printer::Printer(std::ostream& _out) : out(_out), _writeCnt(0) {}

void Printer::printBit(bool b) {
    _writeCnt++;
    buff = (buff << 1) | b;
    if (_writeCnt % 8 == 0) {
        out.write(reinterpret_cast<char*>(&buff), 1);
        buff = 0;
    }
}

void Printer::printByte(uint8_t b) {
    for (int i = 0; i < 8; i++) {
        printBit(b & (1));
        b >>= 1;
    }
}

void Printer::flush() {
    while (_writeCnt % 8 != 0)
        printBit(0);
}

uint64_t Printer::writeCnt() {
    return _writeCnt;
}

Printer::operator bool(){
    return static_cast<bool>(out);
}

Reader::Reader(std::istream& _in)
    : in(_in)
    , _readCnt(0) {}

bool Reader::readBit() {
    if (_readCnt++ % 8 == 0)
        in.read(reinterpret_cast<char*>(&buff), 1);
    bool ans = (buff >> 7) & 1;
    buff <<= 1;
    return ans;
}

uint8_t Reader::readByte() {
    uint8_t ans = 0;
    for (int i = 0; i < 8; i++)
        ans |= readBit() << i;
    return ans;
}

uint64_t Reader::readCnt() {
    return _readCnt;
}

Reader::operator bool() {
    return static_cast<bool>(in);
}