#ifndef NONOGRAM_STATE_H
#define NONOGRAM_STATE_H

#include "grid.h"
#include "bounds.h"

struct State {
    bool (*event_handler)(Grid& g, int cell_size, Bounds actual_bounds);
    void (*draw)(const Grid& g, int padding, int cell_size);
};

#include "states/home.h"
#include "states/create.h"

#endif
