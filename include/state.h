#ifndef NO2GRM_STATE_H
#define NO2GRM_STATE_H

#include <tuple>
#include <vector>
#include "grid.h"
#include "bounds.h"

struct StateRec;

struct StateFn {
    /// Returns false if exit requested.
    bool (*event_handler)(StateFn& fn, StateRec& rec);

    void (*draw)(StateRec& rec);
};

struct StateRec {
    FillType current_fill = Empty; // fill type of drawn line
    std::vector<Point> current_line; // coords of drawn line
    Grid grid; // grid state
    Bounds bounds; // true area of the grid after scaling
    int cell_size; // minimum size of a cell
    DragType drag = DRAW; // is drawn line clearing or setting
};

// state re-exports
#include "states/home.h"
#include "states/create.h"

#endif
