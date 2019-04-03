#include "scheme.h"

Scheme::Scheme(int capacity) : capacity(capacity),
    size(0),
    figures(new Figure *[capacity]) 
    {}

Scheme::~Scheme() {
    for (int i = 0; i < size; i++)
        delete figures[i];
    delete[] figures;
}

void Scheme::push_back_figure(Figure* fg) {
    figures[size++] = fg;
}

void Scheme::remove_figure(int id) {
    int i = find_figure(id);
    delete figures[i];
    if (i < size) {
        for (; i + 1 < size; i++)
            figures[i] = figures[i + 1];
        size--;
    }
}

void Scheme::print_all_figures() const {
    for (int i = 0; i < size; i++)
        figures[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
    figures[find_figure(id)]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) const {
    for (int i = 0; i < size; i++)
        if (figures[i]->is_inside(x, y))
            return figures[i];
    return 0;
}

void Scheme::move(int id, int new_x, int new_y) {
    figures[find_figure(id)]->move(new_x, new_y);
}

int Scheme::find_figure(int id) const {
    for (int i = 0; i < size; i++)
        if (figures[i]->get_id() == id)
            return i;
    return -1;
}