#pragma once

#include <iostream>
#include <string>
#include <vector>

class Printer {
  public:
    void printBit(bool b);
    void printByte(uint8_t b);

    Printer(std::ostream& _out);

    uint64_t writeCnt();

    // flush writes buffer to stream, !!filling missing bits with 0!!
    // doesn't actually flush the stream
    void flush();

    operator bool();

  private:
    std::ostream& out;
    uint8_t buff;
    uint64_t _writeCnt;
};

class Reader {
  public:
    bool readBit();
    uint8_t readByte();

    Reader(std::istream& _in);

    uint64_t readCnt();

    operator bool();

  private:
    std::istream& in;
    uint8_t buff;
    uint64_t _readCnt;
};