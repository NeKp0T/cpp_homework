#include <cstdio>
#include "rectangle.h"

Rectangle::Rectangle(int id, int x, int y, int width, int height) :
    Figure(id, x, y),
    width(width),
    height(height) {}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d, y = %d, width = %d, height = %d\n", id, x, y, width, height);
}

bool Rectangle::is_inside(int point_x, int point_y) const {
    return x <= get_left_bound() &&
           point_x <= get_right_bound() &&
           y <= get_down_bound() &&
           point_y <= get_up_bound();
}

void Rectangle::zoom(int factor) {
    width *= factor;
    height *= factor;
}

int Rectangle::get_left_bound() const {
    if (height > 0) 
        return x;
    else
        return x + height;
}

int Rectangle::get_right_bound() const {
    if (height > 0) 
        return x + height;
    else
        return x;
}

int Rectangle::get_down_bound() const {
    if (width > 0) 
        return y;
    else
        return y + width;
}

int Rectangle::get_up_bound() const {
    if (width > 0) 
        return y + width;
    else
        return y;
}