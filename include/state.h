#ifndef NONOGRAM_STATE_H
#define NONOGRAM_STATE_H

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
    Grid grid;
    Bounds actual_bounds;
    int padding;
    int cell_size;
};

#include "states/home.h"
#include "states/create.h"

#endif
