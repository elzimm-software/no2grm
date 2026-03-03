#include "grid.h"

grid::Grid::Grid(const unsigned int n_rows, const unsigned int n_cols): n_rows(n_rows), n_cols(n_cols) {
    arr = new CellType[n_rows * n_cols] {EMPTY};
}

grid::CellType grid::Grid::get_cell(const unsigned int x, const unsigned int y) const {
    return *(arr + get_index(x, y));
}

void grid::Grid::set_cell(const CellType cell_type, const unsigned x, const unsigned y) const {
    *(arr + get_index(x,y)) = cell_type;
}

unsigned int grid::Grid::get_n_cols() const {
    return n_cols;
}

unsigned int grid::Grid::get_n_rows() const {
    return n_rows;
}

unsigned int grid::Grid::get_index(const unsigned int x, const unsigned int y) const {
    return x + n_cols * y;
}
