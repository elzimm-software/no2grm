#ifndef NO2GRM_GRID_H
#define NO2GRM_GRID_H

#include <vector>
#include "raylib.h"
#include "rules.h"
#include "state.h"

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
    std::vector<FillType> cells;
};

struct Style {
    Color foreground;
    Color background;
    float thickness;
    float radius;
};

struct Point {
    size_t x;
    size_t y;
};

enum DragType {
    DRAW,
    CLEAR
};

/// Create a new grid structure with the given dimensions.
Grid new_grid(size_t size_x, size_t size_y);

size_t get_x(const size_t index, const Grid& grid);

size_t get_y(const size_t index, const Grid& grid);

size_t get_index(const size_t x, const size_t y, const Grid& grid);

size_t get_index(const Point& point, const Grid& grid);

/// Draws grid of squares
void draw_grid(StateRec& rec, Color color);

void color_cells(StateRec& rec, Style& style);

/// Compute the x and y index of the cell a the given position.
size_t find_cell_x(float x, StateRec& rec);
size_t find_cell_y(float y, StateRec& rec);

/// Change the state of the cell at the given index
void set_cell(StateRec& rec, Point& point);

#endif
