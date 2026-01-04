#ifndef NO2GRM_BOUNDS_H
#define NO2GRM_BOUNDS_H


#include "state.h"

struct Bounds {
    int left;
    int right;
    int top;
    int bottom;
};

/// Compute the actual bounds such that each cell is a square
void compute_bounds(StateRec& rec, const Bounds& bounds);

#endif
