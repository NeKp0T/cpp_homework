#include "my_array.h"
#include <iostream>
#include <string>

//11 #include <array>

using std::cout;

template <class T>
void check_standart_value() {
    const std::size_t N = 100;

    my_array<T, N> ma;
    bool all_zero = true;
    for (std::size_t i = 0; i < ma.size(); i++)
        all_zero &= ma[i] == T();

    if (all_zero) {
        cout << "all T()\n";
    } else {
        cout << "not all T()\n";
    }

    all_zero = true;
    T a[N];
    for (std::size_t i = 0; i < N; i++)
        all_zero &= a[i] == T();

    cout << "In normal array ";
    if (all_zero) {
        cout << "all T()\n";
    } else {
        cout << "not all T()\n";
    }
}

template <class T>
void check_sizeof() {
    const std::size_t N = 100;
    my_array<T, N> ma;
    if (sizeof(ma) == N * sizeof(T))
        cout << "Ok sizeof\n";
    else
        cout << "Bad sizeof\n";
}

template <>
void check_sizeof<bool>() {
    const std::size_t N = 100;
    my_array<bool, N> ma;
    if (sizeof(ma) == (N + 7) / 8)
        cout << "Ok sizeof\n";
    else
        cout << "Bad sizeof\n";
}

struct ratte {
    static int ratte_cnt;
    ratte() {
        ratte_cnt++;
        tail_l = 4;
    }
    ~ratte() {
        ratte_cnt--;
    }
    int tail_l;
};
int ratte::ratte_cnt = 0;

template <template <class, std::size_t> class Ta>
void constr_test() {
    ratte::ratte_cnt = 0;
    Ta<ratte, 5> hole;
    if (ratte::ratte_cnt == 5)
        cout << "Just enough rats!\n";
    else if (ratte::ratte_cnt > 5)
        cout << "too many rats!\n";
    else
        cout << "Not enough rats!\n";
    cout << ratte::ratte_cnt << '\n';

    Ta<ratte, 5> hole2(hole);
    Ta<ratte, 5> hole3(hole2);
    hole3 = hole;
    cout << "Now there are " << ratte::ratte_cnt << " of them!\n";

    hole[0].tail_l = hole2[0].tail_l - 1;
    if (hole[0].tail_l == hole2[0].tail_l)
        cout << "Constructor makes link\n";
    else
        cout << "Constructor copies\n";

    if (hole[0].tail_l == hole3[0].tail_l)
        cout << "Assignment makes link\n";
    else
        cout << "Assignment copies\n";
}


int main() {
    check_standart_value<int>();
    check_standart_value<std::string>();

    check_sizeof<int>();
    check_sizeof<std::string>();
    cout << "And for bool ";
    check_sizeof<bool>();

    my_array<bool, 10> ma;
    ma.fill(false);
    ma.set(2, true);
    ma[0] = true;
    ma[0] = ma[0];
    if (ma[0] != true || ma[2] != true || ma[1] == true)
        cout << "Assignment for bools is broken\n";
    else
        cout << "Seems like assigment for bool works well\n";

    ma.fill(true);
    bool all_true = true;
    for (std::size_t i = 0; i < ma.size(); i++) {
        all_true &= ma[i];
    }
    if (!all_true)
        cout << "Something is wrong\n";
    else
        cout << "Fill fills\n";

    cout << "\nmy_array:\n";
    constr_test<my_array>();
    cout << "After it's " << ratte::ratte_cnt << '\n';
    //11 cout << "\nstd::array:\n";
    //11 constr_test<std::array>();
    //11 cout << "After it's " << ratte::ratte_cnt << "\n\n";

    ratte::ratte_cnt = 0;

    my_array<ratte, 10> a, b;
    a[0].tail_l = 10;
    b = a;
    cout << "It is 10: " << b[0].tail_l << '\n';

    my_array<bool, 10> w;
    w[0] = false;
    w[1] = false;
    w[3] = true;
    w[4] = true;
    if (!(w[0] == w[1]) || !(w[4] == w[3])) {
        cout << "Oops\n";
    }

    return 0;
}