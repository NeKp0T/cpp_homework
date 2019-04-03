#include "employees.h"

std::ostream &operator<<(std::ostream &os, const Employee &emp) {
    emp.write(os);
    return os;
}
std::istream &operator>>(std::istream &is, Employee &emp) {
    emp.read(is);
    return is;
}

Developer::Developer() : _name(), _base_salary(), _has_bonus() {}
Developer::Developer(const Developer &d) : _name(d._name), _base_salary(d._base_salary), _has_bonus(d._has_bonus) {}
Developer::Developer(std::istream &is) : Developer() {
    is >> *this;
}

Developer Developer::operator=(Developer oth) {
    std::swap(*this, oth);
    return *this;
}

void Developer::write(std::ostream &os) const {
    os << "Developer\n"
       << "Name: " << _name
       << "\nBaseSalary: " << _base_salary
       << "\nHas bonus: " << (_has_bonus ? '+' : '-')
       << '\n';
}
void Developer::read(std::istream &is) {
    int bonus;
    is >> _name >> _base_salary >> bonus;
    _has_bonus = bonus;
}

void Developer::write_binary(std::ostream &os) const {
    int32_t type = 1;
    os.write((char *)&type, sizeof(int32_t));
    os.write((char *)&_name[0], _name.size());
    os.write("", 1);
    os.write((char *)&_base_salary, sizeof(int32_t));
    os.write((char *)&_has_bonus, sizeof(bool));
}
void Developer::read_binary(std::istream &is) {
    _name = read_string_binary(is);
    is.read((char *)&_base_salary, sizeof(int32_t));
    is.read((char *)&_has_bonus, sizeof(bool));
}

SalesManager::SalesManager() : _name(), _base_salary(), _sold_nm(), _price() {}
SalesManager::SalesManager(const SalesManager &s) : _name(s._name), _base_salary(s._base_salary), _sold_nm(s._sold_nm), _price(s._price) {}
SalesManager::SalesManager(std::istream &is) {
    is >> *this;
}

SalesManager SalesManager::operator=(SalesManager oth) {
    std::swap(*this, oth);
    return *this;
}

void SalesManager::write(std::ostream &os) const {
    os << "SalesManager\n"
       << "Name: " << _name
       << "\nBaseSalary: " << _base_salary
       << "\nSold items: " << _sold_nm
       << "\nItem price: " << _price 
       << '\n';
}
void SalesManager::read(std::istream &is) {
    is >> _name >> _base_salary >> _sold_nm >> _price;
}
void SalesManager::read_binary(std::istream &is) {
    _name = read_string_binary(is);
    is.read((char *)&_base_salary, sizeof(int32_t));
    is.read((char *)&_sold_nm, sizeof(int32_t));
    is.read((char *)&_price, sizeof(int32_t));
}
void SalesManager::write_binary(std::ostream &os) const {
    int32_t type = 2;
    os.write((char *)&type, sizeof(int32_t));
    os.write((char *)&_name[0], _name.size());
    os.write("", 1);
    os.write((char *)&_base_salary, sizeof(int32_t));
    os.write((char *)&_sold_nm, sizeof(int32_t));
    os.write((char *)&_price, sizeof(int32_t));
}

std::string read_string_binary(std::istream &is)
{
    std::string result;
    char buff = 1;
    while (buff != 0)
    {
        is.read(&buff, 1);
        if (buff != 0)
            result.push_back(buff);
    }
    return result;
}


void EmployeesArray::add(const Employee *e) {
    _employees.push_back(std::unique_ptr<const Employee>(e));
}
int EmployeesArray::total_salary() const {
    int32_t salary_sum = 0;
    for (auto &i : _employees)
        salary_sum += i->salary();
    return salary_sum;
}

std::ostream &operator<<(std::ostream &os, const EmployeesArray &ea) {
    for (std::size_t i = 0; i < ea._employees.size(); i++)
        os << i + 1 << ". " << *ea._employees[i];
    os << "== Total salary: " << ea.total_salary() << '\n';
    return os;
}
void EmployeesArray::add_read(std::istream &is) {
    int32_t type;

    Employee *new_employee;
    is >> type;
    if (type == 1)
        new_employee = new Developer();
    if (type == 2)
        new_employee = new SalesManager();

    new_employee->read(is);
    add(new_employee);
}

void EmployeesArray::write_binary(std::ostream &os) const {
    int32_t employees_count = _employees.size();
    os.write((char *)&employees_count, sizeof(int32_t));
    for (auto& i : _employees)
        i->write_binary(os);
}
void EmployeesArray::add_read_binary(std::istream &is) {
    int32_t size;
    is.read((char *)&size, sizeof(int32_t));
    for (int32_t i = 0; i < size; i++) {
        int32_t type;
        is.read((char *)&type, sizeof(int32_t));
        Employee *new_employee;
        
        if (type == 1)
            new_employee = new Developer();
        if (type == 2)
            new_employee = new SalesManager();

        new_employee->read_binary(is);
        add(new_employee);
    }
}