#ifndef NONOGRAM_STATE_H
#define NONOGRAM_STATE_H

#include <tuple>
#include <vector>
#include "grid.h"
#include "bounds.h"

struct StateRec;

struct StateFn {
    /// Returns false if exit requested.
    bool (*event_handler)(StateFn& fn, StateRec& rec);

    void (*draw)(const StateRec& rec);
};

struct StateRec {
    StateFn home;
    StateFn create;
    FillType current_fill = Empty;
    std::vector<size_t> current_line_x;
    std::vector<size_t> current_line_y;
    Grid grid;
    Bounds actual_bounds;
    int padding;
    int cell_size;
    bool clear = false;
};

#include "states/home.h"
#include "states/create.h"

#endif
