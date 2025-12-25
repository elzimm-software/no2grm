#include "states/home.h"

State new_home_state() {
    State s;
    s.event_handler = home::event_handler;
    s.draw = home::draw;
}

namespace home {
    bool event_handler(const Grid& g, int cell_size, Bounds actual_bounds) {

    }

    void draw(const Grid& g, const int padding, const int cell_size) {

    }
}
