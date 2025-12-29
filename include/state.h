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
    StateFn home; // home menu
    StateFn create; // puzzle creation screen
    FillType current_fill = Empty; // fill type of drawn line
    std::vector<size_t> current_line_x; // x coords of drawn line
    std::vector<size_t> current_line_y; // y coords of drawn line
    Grid grid; // grid state
    Bounds actual_bounds; // true area of the grid after scaling
    int padding; // minimum separation of grid from edge of window
    int cell_size; // minimum size of a cell
    bool clear = false; // is drawn line clearing or setting
};

// state re-exports
#include "states/home.h"
#include "states/create.h"

#endif
