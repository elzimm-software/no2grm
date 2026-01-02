#include "states/create.h"
#include "colors.h"

StateFn new_create_state() {
    StateFn s;
    s.event_handler = create_fn::event_handler;
    s.draw = create_fn::draw;
    return s;
}

void add_cell(StateRec& rec, const size_t x, const size_t y) {
    if (rec.current_line_x.empty() || rec.current_line_y.empty() || (rec.current_line_x.back() == x && rec.current_line_y.back() == y)) {
        return;
    }
    if (((rec.clear && rec.grid.cells[y][x] == rec.current_fill) || (!rec.clear && rec.grid.cells[y][x] != rec.current_fill))) {
        rec.current_line_x.push_back(x);
        rec.current_line_y.push_back(y);
    }
}

bool create_fn::event_handler(StateFn& fn, StateRec& rec) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        fn = rec.home;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && rec.current_fill == Empty) {
        auto cell_index = find_cell(GetMousePosition(), rec.cell_size, rec.actual_bounds);
        rec.current_fill = Solid;
        size_t x = std::get<0>(cell_index);
        size_t y = std::get<1>(cell_index);
        if (x < rec.grid.n_cols && y < rec.grid.n_rows) {
            if (rec.grid.cells[y][x] == Solid) {
                rec.clear = true;
            }
            if (rec.grid.cells[y][x] != Cross) {
                rec.current_line_x.push_back(x);
                rec.current_line_y.push_back(y);
            }
        }
    } else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && rec.current_fill == Solid) {
        auto cell_index = find_cell(GetMousePosition(), rec.cell_size, rec.actual_bounds);
        size_t x = std::get<0>(cell_index);
        size_t y = std::get<1>(cell_index);
        if (x < rec.grid.n_cols && y < rec.grid.n_rows) {
            if (rec.grid.cells[y][x] != Cross) {
                add_cell(rec, x, y);
            }
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) && rec.current_fill == Empty) {
        auto cell_index = find_cell(GetMousePosition(), rec.cell_size, rec.actual_bounds);
        rec.current_fill = Note;
        size_t x = std::get<0>(cell_index);
        size_t y = std::get<1>(cell_index);
        if (x < rec.grid.n_cols && y < rec.grid.n_rows) {
            if (rec.grid.cells[y][x] == Note) {
                rec.clear = true;
            }
            if (rec.grid.cells[y][x] == Empty || rec.grid.cells[y][x] == Note) {
                rec.current_line_x.push_back(x);
                rec.current_line_y.push_back(y);
            }
        }
    } else if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE) && rec.current_fill == Note) {
        auto cell_index = find_cell(GetMousePosition(), rec.cell_size, rec.actual_bounds);
        size_t x = std::get<0>(cell_index);
        size_t y = std::get<1>(cell_index);
        if (x < rec.grid.n_cols && y < rec.grid.n_rows) {
            if (rec.grid.cells[y][x] == Empty || rec.grid.cells[y][x] == Note) {
                add_cell(rec, x, y);
            }
        }
    }


    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && rec.current_fill == Empty) {
        auto cell_index = find_cell(GetMousePosition(), rec.cell_size, rec.actual_bounds);
        rec.current_fill = Cross;
        size_t x = std::get<0>(cell_index);
        size_t y = std::get<1>(cell_index);
        if (x < rec.grid.n_cols && y < rec.grid.n_rows) {
            if (rec.grid.cells[y][x] == Cross) {
                rec.clear = true;
            }
            if (rec.grid.cells[y][x] != Solid) {
                rec.current_line_x.push_back(x);
                rec.current_line_y.push_back(y);
            }
        }
    } else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && rec.current_fill == Cross) {
        auto cell_index = find_cell(GetMousePosition(), rec.cell_size, rec.actual_bounds);
        size_t x = std::get<0>(cell_index);
        size_t y = std::get<1>(cell_index);
        if (x < rec.grid.n_cols && y < rec.grid.n_rows) {
            if (rec.grid.cells[y][x] != Solid) {
                add_cell(rec, x, y);
            }
        }
    }

    if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && rec.current_fill == Solid) || (IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE) && rec.current_fill == Note) || (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && rec.current_fill == Cross)) {
        for (int i = 0; i < rec.current_line_x.size(); i++) {
            set_cell(rec.grid, rec.current_line_x[i], rec.current_line_y[i], rec.current_fill, rec.clear);
        }
        rec.clear = false;
        rec.current_fill = Empty;
        rec.current_line_x.clear();
        rec.current_line_y.clear();
    }
    return true;
}

const char* SAVE_TEXT = "Press S to save the current Nonogram";
const int SAVE_SIZE = 20;

void create_fn::draw(const StateRec& rec) {
    BeginDrawing();
    {
        ClearBackground(BACKGROUND);
        DrawFPS(0,0);
        DrawText(SAVE_TEXT, (GetScreenWidth() - MeasureText(SAVE_TEXT, SAVE_SIZE)) / 2, rec.actual_bounds.top - SAVE_SIZE * 2, SAVE_SIZE, FILL);
        color_cells(rec.grid, rec.cell_size, rec.actual_bounds, FILL, 2.0, 4.0);
        FillType fill;
        if (rec.clear) {
            fill = Empty;
        } else {
            fill = rec.current_fill;
        }
        color_cells(rec.current_line_x, rec.current_line_y, fill, rec.cell_size, rec.actual_bounds, FILL, 2.0, 4.0);
        draw_grid(rec.grid.n_cols, rec.grid.n_rows, rec.cell_size, rec.padding, GetScreenWidth() - rec.padding, rec.padding,GetScreenHeight() - rec.padding, FILL);
    }
    EndDrawing();
}