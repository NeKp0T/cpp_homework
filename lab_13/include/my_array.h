#include <algorithm> // fill, copy
#include <cstddef> // size_t
#include <iostream> // cerr
#include <stdlib.h> // exit

static const char wrong_index_message[] = "Wrong my_array index\n";

template <class T, std::size_t N>
class my_array {
  public:
    T& at(std::size_t index);
    const T& at(std::size_t index) const;
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    bool empty() const;
    std::size_t size() const;

    void fill(const T& val);

  private:
    void terminate_on_wrong(std::size_t index) const;

    T data[N];
};

namespace {
template <std::size_t N>
class bool_proxy {
  public:
    bool_proxy(my_array<bool, N>& ma_, std::size_t index_);

    operator bool() const;

    bool_proxy& operator=(bool value);

  private:
    my_array<bool, N>& ma;
    const std::size_t index;
    void operator=(bool_proxy& oth); // = delete
};
}

template <std::size_t N>
class my_array<bool, N> {
  public:
    bool_proxy<N> at(std::size_t index);
    bool at(std::size_t index) const;
    bool operator[](std::size_t index) const;
    bool_proxy<N> operator[](std::size_t index);

    bool empty() const;
    std::size_t size() const;

    void fill(bool val);

    bool get(std::size_t index) const;
    void set(std::size_t index, bool value);

  private:
    void terminate_on_wrong(std::size_t index) const;

    unsigned char data[(N + 7) / 8];
};

template <class T, std::size_t N>
T& my_array<T, N>::operator[](std::size_t index) {
    return data[index];
}
template <class T, std::size_t N>
const T& my_array<T, N>::operator[](std::size_t index) const {
    return data[index];
}

template <class T, std::size_t N>
T& my_array<T, N>::at(std::size_t index) {
    terminate_on_wrong(index);
    return data[index];
}
template <class T, std::size_t N>
const T& my_array<T, N>::at(std::size_t index) const {
    terminate_on_wrong(index);
    return data[index];
}

template <class T, std::size_t N>
bool my_array<T, N>::empty() const {
    return N == 0;
}
template <class T, std::size_t N>
std::size_t my_array<T, N>::size() const {
    return N;
}

template <class T, std::size_t N>
void my_array<T, N>::fill(const T& val) {
    for (std::size_t i = 0; i < N; i++)
        data[i] = val;
}

template <class T, std::size_t N>
void my_array<T, N>::terminate_on_wrong(std::size_t index) const {
    if (index > N) {
        std::cerr << wrong_index_message;
        exit(1);
    }
}

template <std::size_t N>
bool_proxy<N>::bool_proxy(my_array<bool, N>& ma_, std::size_t index_)
    : ma(ma_)
    , index(index_) {}

template <std::size_t N>
bool_proxy<N>::operator bool() const {
    return ma.get(index);
}

template <std::size_t N>
bool_proxy<N>& bool_proxy<N>::operator=(bool value) {
    ma.set(index, value);
    return *this;
}

template <std::size_t N>
bool_proxy<N> my_array<bool, N>::operator[](std::size_t index) {
    return bool_proxy<N>(*this, index);
}

template <std::size_t N>
bool my_array<bool, N>::operator[](std::size_t index) const {
    return get(index);
}

template <std::size_t N>
bool my_array<bool, N>::at(std::size_t index) const {
    terminate_on_wrong(index);
    return operator[](index);
}

template <std::size_t N>
bool_proxy<N> my_array<bool, N>::at(std::size_t index) {
    terminate_on_wrong(index);
    return operator[](index);
}

template <std::size_t N>
void my_array<bool, N>::fill(bool value) {
    unsigned char real_value = 0;
    if (value)
        real_value = (unsigned char)-1;
    std::fill(data, data + (N + 7) / 8, real_value);
}

template <std::size_t N>
bool my_array<bool, N>::empty() const {
    return N == 0;
}
template <std::size_t N>
std::size_t my_array<bool, N>::size() const {
    return N;
}

template <std::size_t N>
bool my_array<bool, N>::get(std::size_t index) const {
    return (data[index / 8] >> (index % 8)) & 1;
}

template <std::size_t N>
void my_array<bool, N>::set(std::size_t index, bool value) {
    unsigned char& block = data[index / 8];
    if (value)
        block |= 1 << (index % 8);
    else
        block &= ~(1 << (index % 8));
}

template <std::size_t N>
void my_array<bool, N>::terminate_on_wrong(std::size_t index) const {
    if (index > N) {
        std::cerr << wrong_index_message;
        exit(1);
    }
}