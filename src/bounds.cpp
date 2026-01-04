#include "bounds.h"
#include "state.h"

Bounds new_bounds(const int left, const int right, const int top, const int bottom) {
    Bounds b;
    b.left = left;
    b.right = right;
    b.top = top;
    b.bottom = bottom;
    return b;
}

Bounds compute_bounds(const StateRec& rec, const Bounds& bounds) {
    const int width = rec.cell_size * rec.grid.n_cols;
    const int height = rec.cell_size * rec.grid.n_rows;
    const int horizontal_offset = (bounds.right - bounds.left - width) / 2;
    const int vertical_offset = (bounds.bottom - bounds.top - height) / 2;
    const int start_x = bounds.left + horizontal_offset;
    const int start_y = bounds.top + vertical_offset;
    const int end_x = bounds.right - horizontal_offset;
    const int end_y = bounds.bottom - vertical_offset;

    return new_bounds(start_x, end_x, start_y, end_y);
}
