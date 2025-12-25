#include "grid.h"

Grid new_grid(const int size_x, const int size_y) {
    Grid g;
    g.n_cols = size_x;
    g.n_rows = size_y;
    g.row_rules.resize(size_y);
    g.col_rules.resize(size_x);
    g.row_max_rules = 0;
    g.col_max_rules = 0;
    g.cells.resize(size_y);
    for (int i = 0; i < size_y; i++) {
        g.cells[i].resize(size_x);
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

std::tuple<size_t, size_t> find_cell(const Vector2& pos, const int cell_size, const Bounds bounds) {
    int x = (pos.x - bounds.left) / cell_size;
    int y = (pos.y - bounds.top) / cell_size;
    return std::make_tuple(x, y);
}

void set_cell(Grid& g, const size_t x, const size_t y, const FillType fill) {
    if (x >= g.n_cols || y >= g.n_rows) {
        return;
    }
    g.cells[y][x] = fill;
}