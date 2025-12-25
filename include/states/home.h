#ifndef NONOGRAM_HOME_H
#define NONOGRAM_HOME_H

#include "state.h"
#include "grid.h"
#include "bounds.h"

State new_home_state();

namespace home {
    bool event_handler(Grid& g, int cell_size, Bounds actual_bounds);
    void draw(const Grid& g, int padding, int cell_size);
}

#endif
