#include "raylib.h"
#include "state.h"
#include "grid.h"
#include "states/create.h"

int main() {
    // ----- DEFINE STATES -----
    State create;
    create.event_handler = state_create_event_handler;
    create.draw = state_create_draw;
    // ----- INIT WINDOW -----
    const int display = GetCurrentMonitor();
    const int monitor_width = GetMonitorWidth(display);
    const int monitor_height = GetMonitorHeight(display);
    InitWindow(monitor_width, monitor_height, "Nonograms");
    if (!IsWindowFullscreen()) {
        ToggleBorderlessWindowed();
    }

    SetTargetFPS(60);

    // ----- INIT STATE -----
    State state = create;
    Grid g = create_grid(15,  15);
    const int padding = 100;
    const int cell_size = 50;
    Bounds actual_bounds = compute_bounds(g.n_cols, g.n_rows, cell_size, padding, GetScreenWidth() - padding, padding, GetScreenHeight() - padding);


    // ----- EVENT AND RENDER LOOP -----
    while (!WindowShouldClose()) {
        // ----- EVENT HANDING -----
        if (!state.event_handler(g, cell_size, actual_bounds)) {
            break;
        }

        // ----- RENDERING -----
        state.draw(g, padding, cell_size, actual_bounds);
    }

    // ----- CLEANUP -----
    CloseWindow();

    return 0;
}
