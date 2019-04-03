#pragma once

#include <cstdio>

#define DO_CHECK(EXPR) check((EXPR), __FUNCTION__, __FILE__, __LINE__)

class Test {
  public:
    static int failedNum;
    static int totalNum;

  public:
    static bool check(bool expr, const char *funcName, const char *filename, std::size_t lineNum);
    static void showFinalResult();

    virtual void runAllTests() = 0;
};