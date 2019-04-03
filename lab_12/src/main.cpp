#include <iostream>
#include <string>

#include "my_vector.h"

class Product {
  public:
    Product(const std::string& name, int quantity, double price);
    Product(const Product& oth);
    Product();

    ~Product() {}

    Product& operator=(Product oth);

    bool operator==(const Product& oth);

    friend std::ostream&
    operator<<(std::ostream& out, const Product& a);

  private:
    std::string name_;
    int quantity_;
    double price_;
};

std::ostream& operator<<(std::ostream& out, const Product& a) {
    out << a.name_ << ' ' << a.quantity_ << ' ' << a.price_;
    return out;
}

Product::Product(const std::string& name, int quantity, double price) {
    name_ = name;
    quantity_ = quantity;
    price_ = price;
}

Product::Product(const Product& oth) {
    name_ = oth.name_;
    quantity_ = oth.quantity_;
    price_ = oth.price_;
}

Product::Product()
    : name_()
    , quantity_(0)
    , price_(0) {
}

Product& Product::operator=(Product oth) {
    name_ = oth.name_;
    price_ = oth.price_;
    quantity_ = oth.quantity_;
    return *this;
}

bool Product::operator==(const Product& oth) {
    return name_ == oth.name_
        && price_ == oth.price_
        && quantity_ == oth.quantity_;
}

void print(const my_vector<Product>& v) {
    std::cout << v << std::endl;
}

void check(bool expr, const char* func_name, const char* filename, std::size_t line_num) {
    if (!expr)
        std::cerr << "test failed: " << func_name << "()"
                  << " in " << filename
                  << " at line " << line_num << '\n';
}

#define DO_CHECK(EXPR) check(EXPR, __FUNCTION__, __FILE__, __LINE__)
template <class T>
void test_my_vector(T a, T b) {
    struct test_input {
        T value;
        size_t size;
        my_vector<T> v;
    };

    test_input arr[]
        = {
              { T(), 0, my_vector<T>() },
              { T(), 2, my_vector<T>(2) },
              { a, 3, my_vector<T>(3, a) },
              { b, 4, my_vector<T>(4, b) }
          };

    for (test_input& i : arr) {
        my_vector<T>& v = i.v;
        DO_CHECK(v.size() == i.size);
        DO_CHECK(v.empty() == !i.size);

        my_vector<T> v_copy(i.v);
        // on first iteration tests my_vector(my_vector&)
        // on second iteration tests operator=
        for (int k = 0; k < 2; k++) {
            if (k == 1)
                v_copy = v;

            DO_CHECK(v.size() == v_copy.size());
            for (size_t j = 0; j < v_copy.size(); j++)
                DO_CHECK(v[j] == v_copy[j]);

            v_copy.push_back(a);
            DO_CHECK(v.size() + 1 == v_copy.size());

            if (v.size() != 0) {
                v[0] = a;
                v_copy[0] = b;
                DO_CHECK(v[0] == a);
            }
        }

        v.push_back(a);
        DO_CHECK(v.back() == v[v.size() - 1]);
        DO_CHECK(v.back() == a);
        v.push_back(b);
        DO_CHECK(v.back() == v[v.size() - 1]);
        DO_CHECK(v.back() == b);

        my_vector<T> v_copy2;
        v_copy2 = v;

        size_t cap = 1;
        while (cap < v.size())
            cap *= 2;
        DO_CHECK(cap == v.capacity());

        v.push_back(a);
        v.push_back(b);
        v.push_back(T());
        v.pop_back();
        DO_CHECK(v.back() == b);
        v.pop_back();
        DO_CHECK(v.back() == a);
        v.pop_back();

        v.resize(20);
        DO_CHECK(v.size() == 20);
        v.reserve(40);
        DO_CHECK(v.capacity() == 64);
        v.resize(64, a);
        DO_CHECK(v.capacity() == 64);
        DO_CHECK(v[63] == a);

        v.clear();
        DO_CHECK(v.size() == 0);

        my_vector<T> copy_copy = v_copy2;
        v.swap(v_copy2);
        DO_CHECK(v.size() == copy_copy.size());
        for (size_t j = 0; j < v.size(); j++)
            DO_CHECK(v[j] == copy_copy[j]);
    }
}

int main() {
    test_my_vector<int>(5, 10);
    test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));

    return 0;
}
