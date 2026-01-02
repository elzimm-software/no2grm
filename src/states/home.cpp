#include "states/home.h"
#include "colors.h"

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

const char* TITLE_TEXT = "HOME";
const int TITLE_SIZE = 40;
const char* NEW_TEXT = "Press N to create a new Nonogram";
const int NEW_SIZE = 20;

void home_fn::draw(const StateRec& rec) {
    BeginDrawing();
    {
        ClearBackground(BACKGROUND);
        DrawText(TITLE_TEXT, (GetScreenWidth() - MeasureText(TITLE_TEXT, TITLE_SIZE)) / 2, GetScreenHeight() / 2 - TITLE_SIZE, TITLE_SIZE, FILL);
        DrawText(NEW_TEXT, (GetScreenWidth() - MeasureText(NEW_TEXT, NEW_SIZE)) / 2, GetScreenHeight() / 2 + NEW_SIZE, NEW_SIZE, FILL);
    }
    EndDrawing();
}
