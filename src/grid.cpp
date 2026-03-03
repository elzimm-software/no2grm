#include "grid.h"

#include "sdl_config.h"
#include "style.h"

namespace {
    unsigned int compute_point_array_size(const unsigned int n_cells) {
        return (n_cells + 1) * 4;
    }

    unsigned int compute_offset(const unsigned int max_len, const unsigned int min_len) {
        if (max_len < min_len) {
            return 0;
        }

        return (max_len - min_len) / 2;
    }
}

grid::Grid::Grid(const unsigned int n_rows, const unsigned int n_cols) : vertical(n_cols, WINDOW_HEIGHT),
                                                                         horizontal(n_rows, WINDOW_WIDTH) {
    arr = new CellType[vertical.n_cells * horizontal.n_cells]{EMPTY};
    n_elements = (vertical.n_elements + horizontal.n_elements) / 2;
    line_points = new unsigned int[n_elements];
}

grid::CellType grid::Grid::get_cell(const unsigned int x, const unsigned int y) const {
    return *(arr + get_index(x, y));
}

void grid::Grid::set_cell(const CellType cell_type, const unsigned x, const unsigned y) const {
    *(arr + get_index(x, y)) = cell_type;
}

unsigned int grid::Grid::get_n_cols() const {
    return horizontal.n_cells;
}

unsigned int grid::Grid::get_n_rows() const {
    return vertical.n_cells;
}

void grid::Grid::draw_grid(SDL_Renderer* renderer) {
}

void grid::Grid::compute_grid_points() const {
    compute_line_points(vertical, horizontal, 0);
    compute_line_points(horizontal, vertical, vertical.n_elements);
}

grid::Grid::RenderGridInfo::RenderGridInfo(unsigned int n_cells, unsigned int max_size) : n_cells(n_cells),
    n_elements(compute_point_array_size(n_cells)), grid_size(n_cells * CELL_SIZE) {
    offset = compute_offset(max_size, grid_size);
}

void grid::Grid::compute_line_points(const RenderGridInfo& parallel, const RenderGridInfo& perpendicular,
                                     const unsigned int offset) const {
    for (unsigned int i = offset, cell_pos = perpendicular.offset; i < parallel.n_cells + 1;
         i++, cell_pos += CELL_SIZE) {
        *(line_points + i) = cell_pos;
        *(line_points + i + 1) = parallel.offset;
        *(line_points + i + 2) = cell_pos;
        *(line_points + i + 3) = parallel.offset + parallel.grid_size;
    }
}

unsigned int grid::Grid::get_index(const unsigned int x, const unsigned int y) const {
    return x + get_n_cols() * y;
}
