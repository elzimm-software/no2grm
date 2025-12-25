#include "bounds.h"

Bounds create_bounds(const int left, const int right, const int top, const int bottom) {
    Bounds b;
    b.left = left;
    b.right = right;
    b.top = top;
    b.bottom = bottom;
    return b;
}

Bounds compute_bounds(const int n_cols, const int n_rows, const int cell_size, const int left, const int right, const int top, const int bottom) {
    const int width = cell_size * n_cols;
    const int height = cell_size * n_rows;
    const int horizontal_offset = (right - left - width) / 2;
    const int vertical_offset = (bottom - top - height) / 2;
    const int start_x = left + horizontal_offset;
    const int start_y = top + vertical_offset;
    const int end_x = right - horizontal_offset;
    const int end_y = bottom - vertical_offset;

    return create_bounds(start_x, end_x, start_y, end_y);
}
