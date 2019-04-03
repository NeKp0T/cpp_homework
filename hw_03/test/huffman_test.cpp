#include "huffman_test.h"
#include <iostream>
#include <memory>
#include <sstream>

using namespace std;
using namespace HuffmanCode;

void HuffmanTest::runAllTests() {
    testPrinter();
    testNodePrint();
    testNodeCalcCodes();
    testNodeFindValue();
}

string vectostr(const vector<uint8_t> &v) {
    string res;
    for (uint8_t i : v)
        res.push_back(static_cast<char>(i));
    return res;
}

void HuffmanTest::testPrinter() {
    totalNum++;
    ostringstream ost;
    Printer p(ost);
    p.printBit(0);
    p.printBit(1);
    p.printBit(1);
    p.printBit(0);
    p.printByte(255);
    p.flush();
    p.printBit(1);
    p.flush();
    ost.flush();
    if (!DO_CHECK(ost.str() == vectostr({ 0b01101111, 0b11110000, 0b10000000 })))
        failedNum++;
}

void HuffmanTest::testNodePrint() {
    totalNum++;
    ostringstream ost;
    Printer p(ost);
    Node nd(
        new Node(3),
        new Node(
            new Node(1),
            new Node(2)));
    nd.print(p);
    p.flush();
    ost.flush();
    // 10[11000000]10[10000000]0[01000000]
    // 10000000111000000001000000010
    // 10000000 11100000 00010000 00010
    // 0b10000000, 0b11100000, 0b00010000, 0b00010000
    if (!DO_CHECK(ost.str() == vectostr({ 0b10110000, 0b00101000, 0b00000010, 0b00000000 })))
        failedNum++;
}

void HuffmanTest::testNodeCalcCodes() {
    totalNum++;
    Node nd(
        new Node(3),
        new Node(
            new Node(1),
            new Node(2)));

    vector<bool> codes[BIT_CAPASITY];
    nd.calcCodes(codes);

    bool b1 = codes[3] == vector<bool>{ false };
    DO_CHECK(b1);
    bool b2 = codes[1] == vector<bool>{ true, false };
    DO_CHECK(b2);
    bool b3 = codes[2] == vector<bool>{ true, true };
    DO_CHECK(b3);
    DO_CHECK(codes[16].empty());

    if (!b1 || !b2 || !b3 || !codes[16].empty())
        failedNum++;
}

void HuffmanTest::testNodeFindValue() {
    totalNum++;
    Node nd(
        new Node(0),
        new Node(
            new Node(
                new Node(100),
                new Node(101)
            ),
            new Node(11)
        )
    );

    vector<bool> v{ 0, 1, 0, 0, 1, 0, 1, 1, 1 };
    bool ok = true;
    auto b = v.begin();
    ok &= DO_CHECK(nd.findValue(b, v.end()) == 0);
    ok &= DO_CHECK(b - v.begin() == 1);
    ok &= DO_CHECK(nd.findValue(b, v.end()) == 100);
    ok &= DO_CHECK(b - v.begin() == 4);
    ok &= DO_CHECK(nd.findValue(b, v.end()) == 101);
    ok &= DO_CHECK(b - v.begin() == 7);
    ok &= DO_CHECK(nd.findValue(b, v.end()) == 11);
    ok &= DO_CHECK(b - v.begin() == 9);
    if (!ok)
        failedNum++;
}
