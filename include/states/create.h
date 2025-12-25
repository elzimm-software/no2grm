#ifndef NONOGRAM_CREATE_H
#define NONOGRAM_CREATE_H

#include "../grid.h"

bool state_create_event_handler(Grid g, int cell_size, Bounds actual_bounds);

void state_create_draw(Grid g, int padding, int cell_size, Bounds actual_bounds);

#endif
