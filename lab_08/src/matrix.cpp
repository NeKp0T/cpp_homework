#include "matrix.h"
#include <cstring>
#include <algorithm>
#include <cassert>


Matrix::Matrix(std::size_t r, std::size_t c) : _rows(r), _cols(c) {
  _data = new int*[r];
  for (std::size_t row = 0; row < r; row++) {
    _data[row] = new int[c];
    std::fill(_data[row], _data[row] + c, 0);
  }
}

Matrix::~Matrix() {
  for (std::size_t r = 0; r < _rows; r++)
    delete[] _data[r];
  delete[] _data;
}

Matrix::Matrix(const Matrix &m) : Matrix(m._rows, m._cols) {
  for (std::size_t row = 0; row < _rows; row++)
    memcpy(_data[row], m._data[row], _cols * sizeof(int));
}

void swap(Matrix &a, Matrix &b) {
  std::swap(a._rows, b._rows);
  std::swap(a._cols, b._cols);
  std::swap(a._data, b._data);
}

Matrix& Matrix::operator=(Matrix m) {
  swap(*this, m);
  return *this;
}

std::size_t Matrix::get_rows() const { return _rows; }
std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
  _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
  return _data[i][j];
}

void Matrix::print(FILE* f) const {
  for (std::size_t r = 0; r < _rows; r++) {
    for (std::size_t c = 0; c < _cols; c++)
      fprintf(f, "%d ", _data[r][c]);
    fprintf(f, "\n");
  }
}

bool Matrix::operator==(const Matrix& m) const {
  bool yes = _rows == m._rows && _cols == m._cols;

  for (std::size_t r = 0; r < _rows && yes; r++)
    for (std::size_t c = 0; c < _cols && yes; c++)
      yes &= _data[r][c] == m._data[r][c];

    return yes;
}

bool Matrix::operator!=(const Matrix& m) const {
  return !operator==(m);
}

Matrix Matrix::operator-() const {
  Matrix res(*this);
  for (std::size_t r = 0; r < _rows; r++)
    for (std::size_t c = 0; c < _cols; c++)
      res._data[r][c] = -res._data[r][c];
  return res;
}

Matrix& Matrix::operator+=(const Matrix& m) {
  for (std::size_t r = 0; r < _rows; r++)
    for (std::size_t c = 0; c < _cols; c++)
      _data[r][c] += m._data[r][c];
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
  return *this += -m;
}

Matrix& Matrix::operator*=(const Matrix& m) {
  *this = *this * m;
  return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
  Matrix res(*this);
  return res += m;
}

Matrix Matrix::operator-(const Matrix& m) const {
  Matrix res(*this);
  return res -= m;
}

Matrix Matrix::operator*(const Matrix& m) const {
  assert(_cols == m._rows);
  Matrix res(_rows, m._cols);
  for (std::size_t r = 0; r < _rows; r++)
    for (std::size_t k = 0; k < _cols; k++)
      for (std::size_t c = 0; c < m._cols; c++)
        res._data[r][c] += _data[r][k] * m._data[k][c];

  return res;
}
