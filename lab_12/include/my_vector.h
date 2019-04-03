#include <cstddef>

template <class T>
class my_vector {
  public:
    my_vector();
    explicit my_vector(size_t n);
    my_vector(size_t n, const T& value);
    my_vector(const my_vector& other);
    my_vector& operator=(const my_vector& other);
    ~my_vector();

    size_t size() const;
    size_t capacity() const;
    bool empty() const;

    void resize(size_t n);
    void resize(size_t n, const T& value);
    void reserve(size_t n);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& back();

    void push_back(const T& t);
    void pop_back();
    void clear();

    void swap(my_vector& oth);

  private:
    size_t capacity_;
    size_t size_;
    T* array_;

    // resize for n < size
    void shrink(size_t n);

    void copy_values(T* dest) const;
    void destroy_array();
};

template <class T>
void my_vector<T>::swap(my_vector& oth) {
    std::swap(size_, oth.size_);
    std::swap(capacity_, oth.capacity_);
    std::swap(array_, oth.array_);
}

template <class T>
my_vector<T>::my_vector() {
    capacity_ = size_ = 0;
    array_ = nullptr;
}

template <class T>
my_vector<T>::my_vector(size_t n)
    : my_vector() {
    resize(n);
}
template <class T>
my_vector<T>::my_vector(size_t n, const T& value)
    : my_vector() {
    resize(n, value);
}

template <class T>
my_vector<T>::my_vector(const my_vector& oth) {
    capacity_ = oth.capacity_;
    size_ = oth.size_;
    array_ = (T*)new char[sizeof(T) * capacity_];

    oth.copy_values(array_);
}

template <class T>
my_vector<T>& my_vector<T>::operator=(const my_vector<T>& oth) {
    my_vector<T> tmp(oth);
    swap(tmp);
    return *this;
}

template <class T>
my_vector<T>::~my_vector() {
    destroy_array();
}

template <class T>
size_t my_vector<T>::size() const {
    return size_;
}
template <class T>
size_t my_vector<T>::capacity() const {
    return capacity_;
}
template <class T>
bool my_vector<T>::empty() const {
    return size_ == 0;
}

template <class T>
void my_vector<T>::shrink(size_t n) {
    for (size_t i = size_; i > n; i--)
        array_[i - 1].~T();
}

template <class T>
void my_vector<T>::resize(size_t n) {
    if (n > size_) {
        reserve(n);
        for (size_t i = size_; i < n; i++)
            new (&array_[i]) T();
    } else {
        shrink(n);
    }
    size_ = n;
}
template <class T>
void my_vector<T>::resize(size_t n, const T& value) {
    if (n > size_) {
        reserve(n);
        for (size_t i = size_; i < n; i++)
            new (&array_[i]) T(value);
    } else {
        shrink(n);
    }
    size_ = n;
}

template <class T>
void my_vector<T>::reserve(size_t n) {
    if (n <= capacity_)
        return;

    size_t new_capacity = capacity_;
    if (capacity_ == 0)
        new_capacity++;
    while (new_capacity < n)
        new_capacity *= 2;

    T* new_array = (T*)new char[new_capacity * sizeof(T)];
    copy_values(new_array);
    destroy_array();

    capacity_ = new_capacity;
    array_ = new_array;
}

template <class T>
T& my_vector<T>::operator[](size_t index) {
    return array_[index];
}
template <class T>
const T& my_vector<T>::operator[](size_t index) const {
    return array_[index];
}

template <class T>
void my_vector<T>::push_back(const T& t) {
    resize(size_ + 1, t);
}

template <class T>
void my_vector<T>::pop_back() {
    resize(size_ - 1);
}

template <class T>
void my_vector<T>::clear() {
    resize(0);
}

template <class T>
T& my_vector<T>::back() {
    return array_[size_ - 1];
}

template <class T>
void my_vector<T>::copy_values(T* dest) const {
    for (size_t i = 0; i < size_; i++)
        new (&dest[i]) T(array_[i]);
}

template <class T>
void my_vector<T>::destroy_array() {
    if (array_ == nullptr)
        return;
    shrink(0);
    delete[] (char*)array_;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const my_vector<T>& v) {
    for (size_t i = 0; i + 1 < v.size(); i++)
        std::cout << v[i] << ' ';
    if (v.size() != 0)
        out << v[v.size() - 1];
    return out;
}
