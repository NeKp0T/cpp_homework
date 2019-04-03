#pragma once

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <exception>

class MAtrix;
class MatrixException;

class Matrix {
  public:
    Matrix();
    Matrix(Matrix &oth);
    Matrix(std::size_t n_, std::size_t m_);
    Matrix(std::istream &in);

    Matrix &operator=(const Matrix &oth);

    Matrix &operator+=(const Matrix &oth);
    Matrix &operator*=(const Matrix &oth);

    int get(std::size_t x, std::size_t y) const ;

    std::size_t getN() const;
    std::size_t getM() const;

  private:
    std::size_t n, m;
    std::vector<std::vector<int>> v;
};

Matrix operator+(Matrix a, const Matrix &b);
Matrix operator*(Matrix a, const Matrix &b);
std::ostream &operator<<(std::ostream &out, const Matrix &mat);


class MatrixException {
  public:
    MatrixException(std::string text_);
    std::string what() const;

  private:
    std::string text;
};