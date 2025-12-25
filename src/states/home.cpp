#include "states/home.h"

StateFn new_home_state() {
    StateFn s;
    s.event_handler = home_fn::event_handler;
    s.draw = home_fn::draw;
    return s;
}

bool home_fn::event_handler(StateFn& fn, StateRec& rec) {
    return false;
}

void home_fn::draw(const StateRec& rec) {

}
