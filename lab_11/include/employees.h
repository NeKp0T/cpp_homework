#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Employee {
public:
  virtual int salary() const = 0;

  // text io
  virtual void write(std::ostream &os) const = 0;
  virtual void read(std::istream &is) = 0;
  // binary io
  virtual void write_binary(std::ostream &os) const = 0;
  virtual void read_binary(std::istream &is) = 0;

  // text io
  friend std::ostream &operator<<(std::ostream &os, const Employee &emp);
  friend std::istream &operator>>(std::istream &is, Employee &emp);
};

std::ostream &operator<<(std::ostream &os, const Employee &emp);
std::istream &operator>>(std::istream &is, Employee &emp);

class Developer : public Employee {
public:
  Developer();
  Developer(const Developer &d);
  Developer(std::istream &is);

  Developer operator=(Developer oth);

  virtual int salary() const {
    int salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
  }

  virtual void write(std::ostream &os) const;
  virtual void read(std::istream &is);
  virtual void write_binary(std::ostream &os) const;
  virtual void read_binary(std::istream &is);

private:
  std::string _name;
  int32_t _base_salary;
  bool _has_bonus;
};

class SalesManager : public Employee {
public:
  SalesManager();
  SalesManager(const SalesManager &s);
  SalesManager(std::istream &is);

  SalesManager operator=(SalesManager oth);

  int salary() const {
    return _base_salary + _sold_nm * _price * 0.01;
  }

  virtual void write(std::ostream &os) const;
  virtual void read(std::istream &is);
  virtual void write_binary(std::ostream &os) const;
  virtual void read_binary(std::istream &is);

private:
  std::string  _name;
  int32_t _base_salary;
  int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
  void add(const Employee *e);
  int total_salary() const;
  
  friend std::ostream &operator<<(std::ostream &os, const EmployeesArray &ea);
  void add_read(std::istream &is); // reads one employee

  void write_binary(std::ostream &os) const;
  void add_read_binary(std::istream &is); // reads all employees 

private:
  std::vector<std::unique_ptr<const Employee>> _employees;
};

std::ostream &operator<<(std::ostream &os, const EmployeesArray &ea);

std::string read_string_binary(std::istream &is);

#endif
