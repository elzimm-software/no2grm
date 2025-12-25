#ifndef NONOGRAM_BOUNDS_H
#define NONOGRAM_BOUNDS_H

struct Bounds {
    int left;
    int right;
    int top;
    int bottom;
};

/// Create a new bounds structure with the given limits.
Bounds create_bounds(int left, int right, int top, int bottom);

/// Compute the actual bounds such that each cell is a square
Bounds compute_bounds(const int n_cols, const int n_rows, const int cell_size, const int left, const int right, const int top, const int bottom);

#endif
