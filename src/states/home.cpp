#include "states/home.h"

StateFn new_home_state() {
    StateFn s;
    s.event_handler = home_fn::event_handler;
    s.draw = home_fn::draw;
    return s;
}

bool home_fn::event_handler(StateFn& fn, StateRec& rec) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        return false;
    }
    if (IsKeyPressed(KEY_N)) {
        fn = rec.create;
    }
    return true;
}

void home_fn::draw(const StateRec& rec) {
    BeginDrawing();
    {
        ClearBackground(Color(0x33, 0x33, 0x33));
        DrawText("HOME", (GetScreenWidth() - MeasureText("HOME", 40)) / 2, GetScreenHeight() / 2 - 40, 40, RAYWHITE);
        DrawText("Press N to create a new Nonogram", (GetScreenWidth() - MeasureText("Press N to create a new Nonogram", 20)) / 2, GetScreenHeight() / 2 + 20, 20, RAYWHITE);
    }
    EndDrawing();
}
