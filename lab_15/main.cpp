#include "linq.h"
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <vector>

using namespace std;

void drop() {
    std::vector<int> xs = { 1, 2, 3, 4, 5 };
    std::vector<int> res = from(xs.begin(), xs.end()).drop(3).to_vector();
    assert(res == vector<int>({ 4, 5 }));
}

void take() {
    const int xs[] = { 1, 2, 3, 4, 5 };
    vector<int> res = from(xs, xs + 5).take(3).to_vector();
    vector<int> expected = { 1, 2, 3 };
    assert(res == expected);
}

void select() {
    vector<int> xs = { 1, 2, 3, 4, 5 };
    std::vector<int> res = from(xs.begin(), xs.end()).select([](int x) { return x + 5; }).to_vector();
    std::vector<int> expected = { 6, 7, 8, 9, 10 };
    assert(res == expected);
}

void until() {
    vector<int> xs = { 1, 2, 3, 4, 5 };
    std::vector<int> res = from(xs.begin(), xs.end()).until([](int x) { return x % 3 == 0; }).to_vector();
    std::vector<int> expected = { 1, 2 };
    assert(res == expected);
}

void until2() {
    vector<int> xs = { 1, 2, 3, 4, 5 };
    std::vector<int> res = from(xs.begin(), xs.end()).until([](int x) { return x % 3 == 1; }).to_vector();
    std::vector<int> expected = {};
    assert(res == expected);
}

void until_eq() {
    vector<int> xs = { 1, 2, 3, 4, 5 };
    std::vector<int> res = from(xs.begin(), xs.end()).until_eq(3).to_vector();
    std::vector<int> expected = { 1, 2 };
    assert(res == expected);
}

void where_neq() {
    vector<int> xs = { 1, 2, 3, 4, 3 };
    std::vector<int> res = from(xs.begin(), xs.end()).where_neq(3).to_vector();
    std::vector<int> expected = { 1, 2, 4 };
    assert(res == expected);
}

void where() {
    vector<int> xs = { 1, 4, 9, 16 };
    std::vector<int> res = from(xs.begin(), xs.end()).where([](int x) { return x > 3; }).to_vector();
    std::vector<int> expected = { 4, 9, 16 };
    assert(res == expected);
}

void where2() {
    vector<int> xs = { 1, 4, 9, 16 };
    std::vector<int> res = from(xs.begin(), xs.end()).where([](int x) { return x % 3 == 0; }).to_vector();
    std::vector<int> expected = { 9 };
    assert(res == expected);
}

void many() {
    vector<int> xs;
    int c = 0;
    generate_n(back_inserter(xs), 100, [&c]() { return c++; });
    auto res = from(xs.begin(), xs.end()).drop(10).take(80).select<char>([](int x) -> char { return -(char)x; }).where_neq(-60).to_vector();

    vector<char> expected;
    for (int i = 10; i < 90; i++)
        if (i != 60)
            expected.push_back(-i);
    assert(expected == res);
}

void empty() {
    vector<int> xs;
    auto res = from(xs.begin(), xs.end()).drop(3).take(3).select_auto([](int x) { return (char)x; }).select<bool>([](int x) { return (bool)x; }).until([](bool f) { return !f; }).where([](bool g) { return g; }).to_vector();
    assert(res.empty());
    // vector<bool> xs;
    // auto res = from(xs.begin(), xs.end()).until([](bool f) { return !f; }).to_vector();
    // assert(res.empty());
}

int main() {
    drop();
    take();
    select();
    until();
    until2();
    until_eq();
    where_neq();
    where();
    empty();
    many();

    auto f = [](int x) {
        static int cnt = 0;
        cout << "f: " << ++cnt << '\n';
        return x;
    };

    vector<int> xs = { 1, 2, 3 };
    auto res = from(xs.begin(), xs.end()).select_auto(f).select_auto(f).to_vector();
    auto res2 = from(xs.begin(), xs.end())
                    .select_auto([](int x) {
                        static int cnt = 0;
                        cout << "g1: " << ++cnt << '\n';
                        return x;
                    })
                    .select_auto([](int x) {
                        static int cnt = 0;
                        cout << "g2: " << ++cnt << '\n';
                        return x;
                    })
                    .to_vector();

    return 0;
}
