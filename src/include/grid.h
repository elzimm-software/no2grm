#ifndef NO2GRM_GRID_H
#define NO2GRM_GRID_H
#include <SDL3/SDL_render.h>

namespace grid {
    enum CellType {
        FILLED,
        MARKED,
        EMPTY,
    };

    class Grid {
    public:
        Grid(unsigned int n_rows, unsigned int n_cols);

        CellType get_cell(unsigned int x, unsigned int y) const;

        void set_cell(CellType cell_type, unsigned x, unsigned y) const;

        unsigned int get_n_cols() const;

        unsigned int get_n_rows() const;

        void draw_grid(SDL_Renderer* renderer);

        void compute_grid_points() const;

    private:
        struct RenderGridInfo {
            unsigned int n_cells;
            unsigned int n_elements;
            unsigned int grid_size;
            unsigned int offset;

            RenderGridInfo(unsigned int n_cells, unsigned int max_size);
        };

        CellType* arr;
        unsigned int* line_points;
        unsigned int n_elements;
        RenderGridInfo vertical;
        RenderGridInfo horizontal;

        unsigned int get_index(unsigned int x, unsigned int y) const;

        void compute_line_points(const RenderGridInfo& parallel, const RenderGridInfo& perpendicular,
                                 unsigned int offset) const;
    };
} // namespace grid

#endif
