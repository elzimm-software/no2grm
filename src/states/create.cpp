#include "states/create.h"

State new_create_state() {
    State s;
    s.event_handler = create::event_handler;
    s.draw = create::draw;
    return s;
}

namespace create {
    bool event_handler(Grid& g, const int cell_size, const Bounds actual_bounds) {
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

    void draw(const Grid& g, const int padding, const int cell_size) {
        BeginDrawing();
        {
            ClearBackground(Color(0x33, 0x33, 0x33));
            draw_grid(g.n_cols, g.n_rows, cell_size, padding, GetScreenWidth() - padding, padding,
                                      GetScreenHeight() - padding, RAYWHITE);
        }
        EndDrawing();
    }
}