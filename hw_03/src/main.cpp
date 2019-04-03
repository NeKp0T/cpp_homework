#include "bitio.h"
#include "huffman.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace HuffmanCode;

bool v = false;
bool s = false; // silent
string finname;
string foutname;
char job = 0;

void parseArgs(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        if (argv[i] == string("-c"))
            job = 'c';
        else if (argv[i] == string("-u"))
            job = 'u';
        else if (argv[i] == string("-v"))
            v = true;
        else if (argv[i] == string("-s"))
            s = true;

        else if (argv[i] == string("-f") || argv[i] == string("--file")) {
            if (i + 1 < argc) {
                i++;
                finname = argv[i];
            } else {
                throw std::runtime_error("-f given, but no file specified");
            }
        }

        else if (argv[i] == string("-o") || argv[i] == string("--output")) {
            if (i + 1 < argc) {
                i++;
                foutname = argv[i];
            } else {
                throw std::runtime_error("-o given, but no file specified");
            }
        }

        else {
            throw std::runtime_error("Unknown key");
        }
    }
}

void writeFileInfo(std::ostream& out, FileSizeInfo inf, bool v = false) {
    if (!v)
        out << inf.uncompressed << '\n'
            << (inf.compressedData + 7) / 8 << '\n'
            << (inf.metaData + 7) / 8 << '\n';
    else
        out << "Uncompressed size: " << inf.uncompressed * 8 << " bits, " << inf.uncompressed << " bytes\n"
            << "Compressed data size: " << inf.compressedData << " bits, " << (inf.compressedData + 7) / 8 << " bytes\n"
            << "Meta data size: " << inf.metaData << " bits, " << (inf.metaData + 7) / 8 << " bytes\n";
}

int main(int argc, char* argv[]) {

    try {
        parseArgs(argc, argv);
    } catch (const std::exception& e) {
        cerr << e.what() << '\n';
        return 2;
    }

    if (job == 0) {
        cerr << "No job specified\n";
        return 1;
    }

    ifstream in;
    try {
        in.open(finname, iostream::in);
    } catch (...) {
        cerr << "Can't open input file\n";
        return 3;
    }

    ofstream out;
    try {
        out.open(foutname, iostream::out);
    } catch (...) {
        cerr << "Can't open output file\n";
        return 4;
    }

    if (job == 'c') {
        vector<uint8_t> vec;
        uint8_t t;
        while (in.read(reinterpret_cast<char*>(&t), 1))
            vec.push_back(static_cast<uint8_t>(t));

        FileSizeInfo inf;
        try {
            inf = encode(vec, out);
        } catch (const Exception& ex) {
            cerr << ex.what() << '\n';
            return 5;
        }
        if (!s)
            writeFileInfo(cout, inf, v);
    } else if (job == 'u') {
        pair<vector<uint8_t>, FileSizeInfo> items;
        try {
            items = decode(in);
        } catch(const Exception &ex) {
            cerr << ex.what() << '\n';
            return 6;
        }
        vector<uint8_t> vec = items.first;
        FileSizeInfo inf = items.second;
        if (!s)
            writeFileInfo(cout, inf, v);
        for (char i : vec) out << i;
    }

    std::unique_ptr<int> p(new int(3));

    return 0;
}