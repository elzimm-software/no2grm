#ifndef NONOGRAM_GRID_H
#define NONOGRAM_GRID_H

#include <vector>
#include "raylib.h"
#include "bounds.h"
#include "rules.h"

enum FillType {
    Empty,
    Solid,
    Cross,
    Note,
};

struct Grid {
    int n_rows;
    int n_cols;
    int row_max_rules;
    int col_max_rules;
    std::vector<Rules> row_rules;
    std::vector<Rules> col_rules;
    std::vector<std::vector<FillType>> cells;
};

/// Create a new grid structure with the given dimensions.
Grid new_grid(int size_x, int size_y);

/// Draws grid of squares
/// Returns actual size of grid after scaling
Bounds draw_grid(int n_cols, int n_rows, int cell_size, int left, int right, int top, int bottom, Color color);

void color_cells(const Grid& g, int cell_size, const Bounds& bounds,
                 Color color, float thickness, float radius);

/// Compute the x and y index of the cell a the given position.
std::tuple<size_t, size_t> find_cell(const Vector2& pos, int cell_size, Bounds bounds);

/// Change the state of the cell at the given index
void set_cell(Grid& g, size_t x, size_t y, FillType fill);

#endif
