#include "circle.h"
#include <cstdio>
#include <cstring>

Circle::Circle(int id, int x, int y, int radius, const char* label) :
    Figure(id, x, y),
    radius(radius) {
    this->label = new char[std::strlen(label) + 1];
    std::strcpy(this->label, label);
}

Circle::~Circle() {
    delete[] label;
}

void Circle::print() const {
    std::printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, radius, label);
}

bool Circle::is_inside(int point_x, int point_y) const {
    return (x - point_x) * (x - point_x) + (y - point_y) * (y - point_y) <= radius * radius;
}

void Circle::zoom(int factor) {
    radius *= factor;
}