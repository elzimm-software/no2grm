#include "render.h"

#include "sdl_config.h"
#include "style.h"

namespace {

    unsigned int compute_point_array_size(const unsigned int n_cells) {
        return (n_cells + 1) * 4;
    }

    unsigned int compute_offset(const unsigned int max_len, unsigned int min_len) {
        if (max_len < min_len) {
            return 0;
        }

        return (max_len - min_len) / 2;
    }

    struct RenderGridInfo {
        unsigned int n_cells;
        unsigned int n_elements;
        unsigned int grid_size;
        unsigned int offset;

        RenderGridInfo(const unsigned int n_cells, const unsigned int max_size): n_cells(n_cells), n_elements(compute_point_array_size(n_cells)), grid_size(n_cells * CELL_SIZE) {
            offset = compute_offset(max_size, grid_size);
        }
    };

    void compute_line_points(const RenderGridInfo& parallel, const RenderGridInfo& perpendicular, unsigned int* line_points) {
        for (unsigned int i = 0, cell_pos = perpendicular.offset; i < parallel.n_cells + 1; i++, cell_pos += CELL_SIZE) {
            *(line_points + i) = cell_pos;
            *(line_points + i + 1) = parallel.offset;
            *(line_points + i + 2) = cell_pos;
            *(line_points + i + 3) = parallel.offset + parallel.grid_size;
        }
    }

}

void render::render_grid(grid::Grid& grid, SDL_Renderer* renderer) {
    const RenderGridInfo vertical(grid.get_n_cols(), WINDOW_HEIGHT);
    const RenderGridInfo horizontal(grid.get_n_rows(), WINDOW_WIDTH);

    const unsigned int n_elements = vertical.n_elements + horizontal.n_elements;
    auto* line_points = new unsigned int[n_elements];

    compute_line_points(vertical, horizontal, line_points);
    compute_line_points(horizontal, vertical, line_points + vertical.n_elements);

    delete[] line_points;
}
