#include "states/create.h"

StateFn new_create_state() {
    StateFn s;
    s.event_handler = create_fn::event_handler;
    s.draw = create_fn::draw;
    return s;
}

bool create_fn::event_handler(StateFn& fn, StateRec& rec) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        fn = rec.home;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        // get cell at mouse
        auto cell_index = find_cell(GetMousePosition(), rec.cell_size, rec.actual_bounds);
        // change cell
        set_cell(rec.grid, std::get<0>(cell_index), std::get<1>(cell_index), Solid);
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        auto cell_index = find_cell(GetMousePosition(), rec.cell_size, rec.actual_bounds);
        set_cell(rec.grid, std::get<0>(cell_index), std::get<1>(cell_index), Note);
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        auto cell_index = find_cell(GetMousePosition(), rec.cell_size, rec.actual_bounds);
        set_cell(rec.grid, std::get<0>(cell_index), std::get<1>(cell_index), Cross);
    }
    return true;
}

void create_fn::draw(const StateRec& rec) {
    BeginDrawing();
    {
        ClearBackground(Color(0x33, 0x33, 0x33));
        DrawFPS(0,0);
        draw_grid(rec.grid.n_cols, rec.grid.n_rows, rec.cell_size, rec.padding, GetScreenWidth() - rec.padding, rec.padding,GetScreenHeight() - rec.padding, RAYWHITE);
        color_cells(rec.grid, rec.cell_size, rec.actual_bounds, RAYWHITE, 2.0, 4.0);
    }
    EndDrawing();
}