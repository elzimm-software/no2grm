#include "states/create.h"

bool state_create_event_handler(Grid g, int cell_size, Bounds actual_bounds) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        return false;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        // get cell at mouse
        auto cell_index = find_cell(GetMousePosition(), cell_size, actual_bounds);
        // change cell
        set_cell(g, std::get<1>(cell_index), std::get<0>(cell_index), Solid);
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        auto cell_index = find_cell(GetMousePosition(), cell_size, actual_bounds);
        set_cell(g, std::get<1>(cell_index), std::get<0>(cell_index), Note);
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        auto cell_index = find_cell(GetMousePosition(), cell_size, actual_bounds);
        set_cell(g, std::get<1>(cell_index), std::get<0>(cell_index), Cross);
    }
    return true;
}

void state_create_draw(Grid g, int padding, int cell_size, Bounds actual_bounds) {
    BeginDrawing(); {
        ClearBackground(Color(0x33, 0x33, 0x33));
        actual_bounds = draw_grid(g.n_cols, g.n_rows, cell_size, padding, GetScreenWidth() - padding, padding, GetScreenHeight() - padding, RAYWHITE);
    } EndDrawing();
}
