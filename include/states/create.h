#ifndef NONOGRAM_CREATE_H
#define NONOGRAM_CREATE_H

#include "grid.h"
#include "state.h"
#include "bounds.h"

StateFn new_create_state();

namespace create_fn {
    bool event_handler(StateFn& fn, StateRec& rec);
    void draw(const StateRec& rec);
}

#endif
