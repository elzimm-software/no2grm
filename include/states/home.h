#ifndef NONOGRAM_HOME_H
#define NONOGRAM_HOME_H

#include "state.h"
#include "grid.h"
#include "bounds.h"

StateFn new_home_state();

namespace home_fn {
    bool event_handler(StateFn& fn, StateRec& rec);
    void draw(const StateRec& rec);
}

#endif
