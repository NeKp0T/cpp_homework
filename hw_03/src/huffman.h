#pragma once

#include <memory>
#include <cstddef>
#include "bitio.h"

namespace HuffmanCode {

const std::size_t BIT_CAPASITY = 256;

struct FileSizeInfo {
    uint64_t uncompressed, compressedData, metaData;
};

class Exception : public std::exception {
  public:
    virtual const char* what() const noexcept;
    Exception(const std::string& _desc);

  private:
    std::string desc;
};

typedef Exception ReadException;
typedef Exception WriteException;

class Node {
  public:
    void print(Printer& printer) const;

    // changes array
    void calcCodes(std::vector<bool> code[BIT_CAPASITY]) const;
    uint8_t findValue(std::vector<bool>::iterator& it, std::vector<bool>::iterator end) const;

    bool isLeaf() const;

    Node(uint8_t _val);
    Node(Node* l, Node* r);
    Node(Reader& reader);
    ~Node();

  private:
    uint8_t val;
    std::unique_ptr<Node> e[2];
    void calcCodesRec(std::vector<bool> code[256], std::vector<bool>& pref) const;
};


class Archiver {
  public:
    struct KeyFrequency {
      uint8_t key;
      int64_t freq;
    };
    // pairs <key, frequency>
    Archiver(const std::vector<KeyFrequency>& keyFreq);

    std::vector<bool> encode(uint8_t key);

    void printMetaInfo(Printer& printer);

    ~Archiver();

  private:
    std::unique_ptr<Node> root;
    std::vector<bool> code[256];
};

class Decoder {
  public:
    Decoder(Reader& reader);

    uint8_t decodeNext(std::vector<bool>::iterator& it, std::vector<bool>::iterator end);
    std::vector<uint8_t> decodeAll(std::vector<bool>::iterator first, std::vector<bool>::iterator second);

    ~Decoder();

  private:
    std::unique_ptr<Node> root;
};

FileSizeInfo encode(const std::vector<uint8_t> &sin, std::ostream& fout);
std::pair<std::vector<uint8_t>, FileSizeInfo> decode(std::istream& fin);

}