#include <iostream>
#include "grid.h"
#include "colors.h"

Grid new_grid(const int size_x, const int size_y) {
    Grid g;
    g.n_cols = size_x;
    g.n_rows = size_y;
    // there will always be exactly as many rule sets as rows or cols
    g.row_rules.resize(size_y);
    g.col_rules.resize(size_x);
    // clear before first use
    g.row_rules.clear();
    g.col_rules.clear();
    g.row_max_rules = 0;
    g.col_max_rules = 0;
    // resize for rows
    g.cells.resize(size_y);
    // resize each column
    for (int i = 0; i < size_y; i++) {
        g.cells[i].resize(size_x, Empty);
    }
    return g;
}

Bounds draw_grid(const int n_cols, const int n_rows, const int cell_size, const int left, const int right, const int top, const int bottom, const Color color) {
    // why draw n*m boxes when you could draw n+m lines
    Bounds b = compute_bounds(n_cols, n_rows, cell_size, left, right, top, bottom);
    // draw vertical lines
    for (int i = 0; i <= n_cols; i++) {
        const int x = i * cell_size + b.left;
        DrawLine(x, b.top, x, b.bottom, color);
    }
    // draw horizontal lines
    for (int i = 0; i <= n_rows; i++) {
        const int y = i * cell_size + b.top;
        DrawLine(b.left, y, b.right, y, color);
    }
    return b;
}

void color_cells(const std::vector<size_t>& x, const std::vector<size_t>& y, const FillType fill, const int cell_size, const Bounds& bounds, const Color color, const float thickness, const float radius) {
    float left;
    float right;
    float top;
    float bottom;
    // because this is designed to overwrite the already drawn grid state,
    // all fills have a background rect added to them
    for (int i = 0; i < x.size(); i++) {
        switch (fill) {
            case Solid:
                DrawRectangle(bounds.left + x[i] * cell_size, bounds.top + y[i] * cell_size, cell_size, cell_size, color);
                break;
            case Empty:
                DrawRectangle(bounds.left + x[i] * cell_size, bounds.top + y[i] * cell_size, cell_size, cell_size, BACKGROUND);
                break;
            case Cross:
                left = bounds.left + x[i] * cell_size;
                right = left + cell_size;
                top = bounds.top + y[i] * cell_size;
                bottom = top + cell_size;
                DrawRectangle(left, top, cell_size, cell_size, BACKGROUND);
                DrawLineEx({left, top}, {right, bottom}, thickness, color);
                DrawLineEx({left, bottom}, {right, top}, thickness, color);
                break;
            case Note:
                DrawCircle(bounds.left + x[i] * cell_size + cell_size / 2, bounds.top + y[i] * cell_size + cell_size / 2, radius, color);
                break;
        }
    }
}

void color_cells(const Grid& g, const int cell_size, const Bounds& bounds,
                 const Color color, const float thickness, const float radius) {
    float left;
    float right;
    float top;
    float bottom;
    for (int y = 0; y < g.n_rows; y++) {
        for (int x = 0; x < g.n_cols; x++) {
            switch (g.cells[y][x]) {
                case Solid:
                    DrawRectangle(bounds.left + x * cell_size, bounds.top + y * cell_size, cell_size, cell_size, color);
                    break;
                case Empty:
                    break;
                case Cross:
                    left = bounds.left + x * cell_size;
                    right = left + cell_size;
                    top = bounds.top + y * cell_size;
                    bottom = top + cell_size;
                    DrawLineEx({left, top}, {right, bottom}, thickness, color);
                    DrawLineEx({left, bottom}, {right, top}, thickness, color);
                    break;
                case Note:
                    DrawCircle(bounds.left + x * cell_size + cell_size / 2, bounds.top + y * cell_size + cell_size / 2, radius, color);
                    break;
            }
        }
    }
}

std::tuple<size_t, size_t> find_cell(const Vector2& pos, const int cell_size, const Bounds bounds) {
    int x = (pos.x - bounds.left) / cell_size;
    int y = (pos.y - bounds.top) / cell_size;
    return std::make_tuple(x, y);
}

void set_cell(Grid& g, const size_t x, const size_t y, const FillType fill, bool clear) {
    if (x >= g.n_cols || y >= g.n_rows) {
        return;
    }
    switch (g.cells[y][x]) {
        case Empty:
            g.cells[y][x] = fill;
            break;
        case Solid:
            if (fill == Solid) {
                g.cells[y][x] = Empty;
            }
            break;
        case Cross:
            if (fill == Cross) {
                g.cells[y][x] = Empty;
            }
            break;
        case Note:
            if (fill == Note) {
                g.cells[y][x] = Empty;
            } else {
                g.cells[y][x] = fill;
            }
            break;
    }


}