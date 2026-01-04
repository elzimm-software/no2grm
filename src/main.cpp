#include "raylib.h"
#include "bounds.h"

const int PADDING = 100;
const Bounds MAX_BOUNDS = {
        .left = PADDING,
        .right = GetScreenWidth() - PADDING,
        .top = PADDING,
        .bottom = GetScreenHeight() - PADDING
};

/*
 * Its worth noting that none of this works at present but Im losing my mind and I cant figure out why it doesnt work.
 * I suspect some sort of circular dependency issue that Im just not invested enough right now to fix.
 */

int main() {
    // ----- INIT WINDOW -----
    const int DISPLAY = GetCurrentMonitor();
    const int MONITOR_WIDTH = GetMonitorWidth(DISPLAY);
    const int MONITOR_HEIGHT = GetMonitorHeight(DISPLAY);
    InitWindow(MONITOR_WIDTH, MONITOR_HEIGHT, "Nonograms");
    if (!IsWindowFullscreen()) {
        ToggleBorderlessWindowed();
    }

    SetTargetFPS(60);
    // prevent esc key from closing program
    SetExitKey(NULL);

    // ----- INIT STATE -----
    StateRec rec = {
            .grid = new_grid(15, 15),
            .cell_size = 50,
    };

    compute_bounds(rec, {.left = rec.cell_size, .right = GetScreenWidth() - PADDING, .top = PADDING, .bottom = GetScreenHeight() - PADDING});

    rec.current_line.resize(rec.grid.n_rows * rec.grid.n_cols);
    rec.current_line.clear();

    // ----- DEFINE STATES -----
    // home menu is initial state
    StateFn state_fn = HOME_STATE;

    // ----- EVENT AND RENDER LOOP -----
    while (!WindowShouldClose()) {
        // ----- EVENT HANDING -----
        if (!state_fn.event_handler(state_fn, rec)) {
            break;
        }

        // ----- RENDERING -----
        state_fn.draw(rec);
    }

    // ----- CLEANUP -----
    CloseWindow();

    return 0;
}
