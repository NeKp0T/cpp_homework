#include "my_vector.h"
#include <cassert>
#include <vector>

/*

class MyVector {
public: // methods
  MyVector();
  MyVector(std::size_t init_capacity);
  ~MyVector();

  void set(std::size_t index, int value);
  int get(std::size_t index);

  std::size_t size();
  std::size_t capacity();

  void reserve(std::size_t new_capacity);
  void resize(std::size_t new_size);
  
  void push_back(int value);
  void insert(std::size_t index, int value);
  void erase(std::size_t index);
private: // fields
  std::size_t sz, cp;
  int *data;
};
*/

MyVector::MyVector() : MyVector(2){}
MyVector::MyVector(std::size_t init_capacity) : sz(0), cp(init_capacity) {
  data = new int[init_capacity];
}

MyVector::~MyVector() {
  delete[] data;
}

bool MyVector::check_index(std::size_t index, bool inclusive) {
  return index >= 0 && index < sz + inclusive;
}

void MyVector::set(std::size_t index, int value) {
  assert(check_index(index));
  data[index] = value;
}

int MyVector::get(std::size_t index) {
  assert(check_index(index));
  return data[index];
}

std::size_t MyVector::size() const {
  return sz;
}
std::size_t MyVector::capacity() const {
  return cp;
}

void MyVector::reserve(std::size_t new_capacity) {
  if (new_capacity > cp) {
    int *newdata = new int[new_capacity];
    std::copy(data, data + sz, newdata);
    delete[] data;
    data = newdata;
    cp = new_capacity;
  }
}

void MyVector::resize(std::size_t new_size) {
  if (new_size > sz) {
    if (new_size > cp)
      reserve(std::max(new_size, 2 * cp));

    std::fill(data + sz, data + new_size, 0);
  }

  sz = new_size;
}

void MyVector::push_back(int value) {
  resize(sz + 1);
  set(sz - 1, value);
}

void MyVector::pop_back() {
  erase(sz - 1);
}

void MyVector::insert(std::size_t index, int value) {
  assert(check_index(index, true));
  resize(sz + 1);
  for (std::size_t i = sz - 1; i > index; i--)
    data[i] = data[i - 1];
  set(index, value);
}

void MyVector::erase(std::size_t index) {
  assert(check_index(index));
  for (std::size_t i = index; i + 1 < sz; i++)
    data[i] = data[i + 1];
  resize(sz - 1);
}
