#ifndef NONOGRAM_BOUNDS_H
#define NONOGRAM_BOUNDS_H

struct Bounds {
    int left;
    int right;
    int top;
    int bottom;
};

/// Create a new bounds structure with the given limits.
Bounds new_bounds(int left, int right, int top, int bottom);

/// Compute the actual bounds such that each cell is a square
Bounds compute_bounds(int n_cols, int n_rows, int cell_size, int left, int right, int top, int bottom);

#endif
