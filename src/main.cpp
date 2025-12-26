#include "raylib.h"
#include "state.h"
#include "grid.h"



int main() {
    // ----- INIT WINDOW -----
    const int display = GetCurrentMonitor();
    const int monitor_width = GetMonitorWidth(display);
    const int monitor_height = GetMonitorHeight(display);
    InitWindow(monitor_width, monitor_height, "Nonograms");
    if (!IsWindowFullscreen()) {
        ToggleBorderlessWindowed();
    }

    SetTargetFPS(60);
    SetExitKey(NULL);

    // ----- INIT STATE -----
    StateRec state_rec;
    state_rec.grid = new_grid(15, 15);
    state_rec.padding = 100;
    state_rec.cell_size = 50;
    state_rec.actual_bounds = compute_bounds(state_rec.grid.n_cols, state_rec.grid.n_rows, state_rec.cell_size, state_rec.padding, GetScreenWidth() - state_rec.padding, state_rec.padding, GetScreenHeight() - state_rec.padding);

    // ----- DEFINE STATES -----
    state_rec.home = new_home_state();
    state_rec.create = new_create_state();
    StateFn state_fn = state_rec.home;

    // ----- EVENT AND RENDER LOOP -----
    while (!WindowShouldClose()) {
        // ----- EVENT HANDING -----
        if (!state_fn.event_handler(state_fn, state_rec)) {
            break;
        }

        // ----- RENDERING -----
        state_fn.draw(state_rec);
    }

    // ----- CLEANUP -----
    CloseWindow();

    return 0;
}
