#ifndef LINQ_H_
#define LINQ_H_

#include <type_traits>
#include <utility>
#include <vector>

template <typename T, typename Iter>
class range_enumerator;
template <typename T>
class drop_enumerator;
template <typename T>
class take_enumerator;
template <typename T, typename U, typename F>
class select_enumerator;
template <typename T, typename F>
class until_enumerator;
template <typename T, typename F>
class where_enumerator;

template <typename T>
class enumerator {
  public:
    virtual const T &operator*() = 0;
    virtual operator bool() = 0;
    virtual enumerator &operator++() = 0;

    auto drop(int count) {
        return drop_enumerator<T>(*this, count);
    }

    auto take(int count) {
        return take_enumerator<T>(*this, count);
    }

    template <typename F>
    auto select_auto(F &&func) {
        return select_enumerator<typename std::remove_const<typename std::result_of<F(T)>::type>::type, T, F>(*this, std::forward<F>(func));
    }

    template <typename U = T, typename F>
    auto select(F &&func) {
        return select_enumerator<typename std::remove_const<U>::type, T, F>(*this, std::forward<F>(func));
    }

    template <typename F>
    auto until(F &&func) {
        return until_enumerator<T, F>(*this, std::forward<F>(func));
    }

    auto until_eq(const T &t) {
        return until([t](T x) { return x == t; });
    }

    template <typename F>
    auto where(F &&func) {
        return where_enumerator<T, F>(*this, std::forward<F>(func));
    }

    auto where_neq(const T &t) {
        return where([t](T x) { return x != t; });
    }

    auto to_vector() {
        std::vector<typename std::remove_const<T>::type> v;
        copy_to(std::back_inserter(v));
        return v;
    }

    template <typename Iter>
    void copy_to(Iter &&it) {
        for (; *this; ++(*this), ++it)
            *it = **this;
    }
};

template <typename T, typename Iter>
class range_enumerator : public enumerator<T> {
  public:
    range_enumerator(Iter begin, Iter end)
        : now(begin)
        , end_(end) {
    }

    virtual const T &operator*() {
        return *now;
    }
    virtual operator bool() {
        return now != end_;
    }
    virtual range_enumerator<T, Iter> &operator++() {
        ++now;
        return *this;
    }

  private:
    Iter now, end_;
};

template <typename T>
auto from(T begin, T end) {
    return range_enumerator<typename std::remove_reference<decltype((*begin))>::type, T>(begin, end);
}

template <typename T>
class drop_enumerator : public enumerator<T> {
  public:
    drop_enumerator(enumerator<T> &parent, int count)
        : parent_(parent) {
        while (parent_ && count > 0) {
            ++parent_;
            --count;
        }
    }

    virtual const T &operator*() {
        return *parent_;
    }
    virtual operator bool() {
        return (bool)(parent_);
    }
    virtual drop_enumerator<T> &operator++() {
        ++parent_;
        return *this;
    }

  private:
    enumerator<T> &parent_;
};

template <typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
  public:
    select_enumerator(enumerator<U> &parent, F &&func)
        : parent_(parent)
        , func_(std::forward<F>(func)) {
        if (parent_)
            current = func_(*parent_);
    }

    virtual const T &operator*() {
        return current;
    }
    virtual operator bool() {
        return (bool)(parent_);
    }
    virtual select_enumerator<T, U, F> &operator++() {
        ++parent_;
        if (parent_)
            current = func_(*parent_);
        return *this;
    }

  private:
    enumerator<U> &parent_;
    F func_;
    T current;
};

template <typename T, typename F>
class until_enumerator : public enumerator<T> {
  public:
    until_enumerator(enumerator<T> &parent, F &&predicate)
        : parent_(parent)
        , predicate_(std::forward<F>(predicate))
        , end(false) {
        if (!(parent_) || predicate_(*parent_))
            end = true;
    }

    virtual const T &operator*() {
        return *parent_;
    }
    virtual operator bool() {
        return !end && (bool)(parent_);
    }
    virtual until_enumerator<T, F> &operator++() {
        ++parent_;
        if ((!parent_) || predicate_(*parent_))
            end = true;
        return *this;
    }

  private:
    enumerator<T> &parent_;
    F predicate_;
    bool end;
};

template <typename T, typename F>
class where_enumerator : public enumerator<T> {
  public:
    where_enumerator(enumerator<T> &parent, F &&predicate)
        : parent_(parent)
        , predicate_(std::forward<F>(predicate)) {
        if ((parent_) && !predicate_(*parent_))
            ++(*this);
    }

    virtual const T &operator*() {
        return *parent_;
    }

    virtual operator bool() {
        return (bool)(parent_);
    }

    virtual where_enumerator<T, F> &operator++() {
        ++parent_;
        while ((bool)(parent_) && !predicate_(*parent_))
            ++parent_;
        return *this;
    }

  private:
    enumerator<T> &parent_;
    F predicate_;
};

template <typename T>
class take_enumerator : public enumerator<T> {
  public:
    take_enumerator(enumerator<T> &parent, int count)
        : parent_(parent)
        , count_(count) {
    }

    virtual const T &operator*() {
        return *parent_;
    }
    virtual operator bool() {
        return count_ > 0 && (bool)(parent_);
    }
    virtual take_enumerator<T> &operator++() {
        ++parent_;
        --count_;
        return *this;
    }

  private:
    enumerator<T> &parent_;
    int count_;
};

#endif
