#pragma once

#include "autotest.h"
#include "huffman.h"
#include "bitio.h"

class HuffmanTest : public Test {
  public:
    virtual void runAllTests();

    HuffmanTest() = default;

  private:
    void testPrinter();
    void testNodePrint();
    void testNodeCalcCodes();
    void testNodeFindValue();
};