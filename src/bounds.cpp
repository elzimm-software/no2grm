#include "bounds.h"

void compute_bounds(StateRec& rec, const Bounds& bounds) {
    const int width = rec.cell_size * rec.grid.n_cols;
    const int height = rec.cell_size * rec.grid.n_rows;
    const int horizontal_offset = (bounds.right - bounds.left - width) / 2;
    const int vertical_offset = (bounds.bottom - bounds.top - height) / 2;
    const int start_x = bounds.left + horizontal_offset;
    const int start_y = bounds.top + vertical_offset;
    const int end_x = bounds.right - horizontal_offset;
    const int end_y = bounds.bottom - vertical_offset;

    rec.bounds = {
            .left = start_x,
            .right = end_x,
            .top = start_y,
            .bottom = end_y,
    };
}
