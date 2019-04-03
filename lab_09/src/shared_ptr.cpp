#include "shared_ptr.h"
#include <utility>

shared_ptr::shared_ptr(Matrix* obj) {
    storage_ = new Storage(obj);
    storage_->incr();
}

shared_ptr::shared_ptr(const shared_ptr& other) {
    storage_ = other.storage_;
    storage_->incr();
}

shared_ptr::~shared_ptr() {
    storage_->decr();
    if (storage_->getCounter() == 0)
        delete storage_;
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {
    shared_ptr tmp(other);
    std::swap(this->storage_, other.storage_);
    return *this;
}

void shared_ptr::reset(Matrix* obj) {
    *this = shared_ptr(obj);
}

Matrix* shared_ptr::ptr() const {
    return storage_->getObject();
}

Matrix* shared_ptr::operator->() const {
    return ptr();
}

Matrix& shared_ptr::operator*() const {
    return *ptr();
}

bool shared_ptr::isNull() const {
    return ptr() == 0;
}


shared_ptr::Storage::Storage(Matrix *mtx) : data_(mtx), ref_count_(0) {}

shared_ptr::Storage::~Storage() {
    if (data_ != 0)
        delete data_;
}

void shared_ptr::Storage::incr() {
    ref_count_++;
}
void shared_ptr::Storage::decr() {
    ref_count_--;
}

int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const {
    return data_;
}