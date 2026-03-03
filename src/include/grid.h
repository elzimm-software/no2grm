#ifndef NO2GRM_GRID_H
#define NO2GRM_GRID_H

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

    private:
        unsigned int n_rows;
        unsigned int n_cols;
        CellType* arr;

        unsigned int get_index(unsigned int x, unsigned int y) const;
    };
} // namespace grid

#endif