#ifndef NO2GRM_CREATE_H
#define NO2GRM_CREATE_H

#include "state.h"
#include "colors.h"
#include "grid.h"

static StateFn new_create_state();

const StateFn CREATE_STATE = new_create_state();

namespace create_fn {
    bool event_handler(StateFn& fn, StateRec& rec);
    void draw(StateRec& rec);
}

#endif
