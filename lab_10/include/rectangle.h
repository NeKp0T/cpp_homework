#pragma once

#include "figure.h"

class Rectangle : public Figure {
  public:
    Rectangle(int id, int x, int y, int width, int height);

    virtual void print() const;
    virtual bool is_inside(int point_x, int point_y) const;
    virtual void zoom(int factor);

    int get_left_bound()  const;
    int get_right_bound() const;
    int get_down_bound()  const;
    int get_up_bound()    const;

  protected:
    int width, height;
};
