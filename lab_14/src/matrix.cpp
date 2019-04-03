#include "matrix.h"

Matrix::Matrix()
    : n(0)
    , m(0)
    , v(0) {}
Matrix::Matrix(Matrix &otn)
    : n(otn.n)
    , m(otn.m)
    , v(otn.v) {
}
Matrix::Matrix(std::size_t n, std::size_t m)
    : n(n)
    , m(m)
    , v(n, std::vector<int>(m)) {}

Matrix::Matrix(std::istream &in) {
    in >> n >> m;
    v = std::vector<std::vector<int>>(n, std::vector<int>(m));
    for (auto &i : v)
        for (auto &j : i)
            in >> j;
}

Matrix &Matrix::operator=(const Matrix &oth) {
    n = oth.n;
    m = oth.m;
    v = oth.v;
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &oth) {
    if (n != oth.n || m != oth.m)
        throw MatrixException("ADD: dimension do not match.");
    for (std::size_t i = 0; i < n; i++)
        for (std::size_t j = 0; j < m; j++)
            v[i][j] += oth.v[i][j];
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &oth) {
    if (m != oth.n)
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    std::vector<std::vector<int>> newV(n, std::vector<int>(oth.m));
    for (std::size_t i = 0; i < n; i++)
        for (std::size_t j = 0; j < oth.m; j++)
            for (std::size_t k = 0; k < m; k++)
                newV[i][j] += v[i][k] * oth.v[k][j];
    v = newV;
    return *this;
}

int Matrix::get(std::size_t x, std::size_t y) const {
    if (x >= n || y >= m)
        throw MatrixException("ACCESS: bad index");
    return v[x][y];
}

std::size_t Matrix::getN() const {
    return n;
}
std::size_t Matrix::getM() const {
    return m;
}

Matrix operator+(Matrix a, const Matrix &b) {
    return a += b;
}
Matrix operator*(Matrix a, const Matrix &b) {
    return a *= b;
}

std::ostream &operator<<(std::ostream &out, const Matrix &mat) {
    for (std::size_t i = 0; i < mat.getN(); i++) {
        for (std::size_t j = 0; j < mat.getM(); j++)
            out << mat.get(i, j) << ' ';
        out << '\n';
    }
    return out;
}

MatrixException::MatrixException(std::string text_)
    : text(text_) {}

std::string MatrixException::what() const {
    return text;
}
