#include "autotest.h"

int Test::failedNum = 0;
int Test::totalNum = 0;

bool Test::check(bool expr, const char *funcName, const char *filename, std::size_t lineNum) {
    if (!expr)
        printf("test failed: %s() in %s.cpp:%lu\n", funcName, filename, lineNum);
    return expr;
}

void Test::showFinalResult() {
    if (failedNum == 0)
        printf("All tests passed!\n");
    else
        printf("Failed %d out of %d.\n", failedNum, totalNum);
}