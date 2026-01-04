#ifndef NO2GRM_HOME_H
#define NO2GRM_HOME_H

#include "state.h"

static StateFn new_home_state();

const StateFn HOME_STATE = new_home_state();

namespace home_fn {
    bool event_handler(StateFn& fn, StateRec& rec);
    void draw(StateRec& rec);
}

#endif
