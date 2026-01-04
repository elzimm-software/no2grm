#include "states/create.h"

static StateFn new_create_state() {
    StateFn s;
    s.event_handler = create_fn::event_handler;
    s.draw = create_fn::draw;
    return s;
}

void add_cell(StateRec& rec, const size_t x, const size_t y) {
    if (rec.current_line.empty() || (rec.current_line.back().x == x && rec.current_line.back().y)) {
        return;
    }
    size_t index = get_index(x, y, rec.grid);
    if (((rec.drag == CLEAR && rec.grid.cells[index] == rec.current_fill) || (rec.drag == DRAW && rec.grid.cells[index] != rec.current_fill))) {
        Point p;
        p.x = x;
        p.y = y;
        rec.current_line.push_back(p);
    }
}

bool create_fn::event_handler(StateFn& fn, StateRec& rec) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        fn = HOME_STATE;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && rec.current_fill == Empty) {
        Vector2 mouse_pos = GetMousePosition();
        size_t x = find_cell_x(mouse_pos.x, rec);
        size_t y = find_cell_y(mouse_pos.y, rec);
        rec.current_fill = Solid;
        if (x < rec.grid.n_cols && y < rec.grid.n_rows) {
            if (rec.grid.cells[y][x] == Solid) {
                rec.drag = CLEAR;
            }
            if (rec.grid.cells[y][x] != Cross) {
                Point p;
                p.x = x;
                p.y = y;
                rec.current_line.push_back(p);
            }
        }
    } else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && rec.current_fill == Solid) {
        Vector2 mouse_pos = GetMousePosition();
        size_t x = find_cell_x(mouse_pos.x, rec);
        size_t y = find_cell_y(mouse_pos.y, rec);
        if (x < rec.grid.n_cols && y < rec.grid.n_rows) {
            if (rec.grid.cells[y][x] != Cross) {
                add_cell(rec, x, y);
            }
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) && rec.current_fill == Empty) {
        Vector2 mouse_pos = GetMousePosition();
        size_t x = find_cell_x(mouse_pos.x, rec);
        size_t y = find_cell_y(mouse_pos.y, rec);
        rec.current_fill = Note;
        if (x < rec.grid.n_cols && y < rec.grid.n_rows) {
            if (rec.grid.cells[y][x] == Note) {
                rec.drag = CLEAR;
            }
            if (rec.grid.cells[y][x] == Empty || rec.grid.cells[y][x] == Note) {
                Point p;
                p.x = x;
                p.y = y;
                rec.current_line.push_back(p);
            }
        }
    } else if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE) && rec.current_fill == Note) {
        Vector2 mouse_pos = GetMousePosition();
        size_t x = find_cell_x(mouse_pos.x, rec);
        size_t y = find_cell_y(mouse_pos.y, rec);
        if (x < rec.grid.n_cols && y < rec.grid.n_rows) {
            if (rec.grid.cells[y][x] == Empty || rec.grid.cells[y][x] == Note) {
                add_cell(rec, x, y);
            }
        }
    }


    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && rec.current_fill == Empty) {
        Vector2 mouse_pos = GetMousePosition();
        size_t x = find_cell_x(mouse_pos.x, rec);
        size_t y = find_cell_y(mouse_pos.y, rec);
        rec.current_fill = Cross;
        if (x < rec.grid.n_cols && y < rec.grid.n_rows) {
            if (rec.grid.cells[y][x] == Cross) {
                rec.drag = CLEAR;
            }
            if (rec.grid.cells[y][x] != Solid) {
                Point p;
                p.x = x;
                p.y = y;
                rec.current_line.push_back(p);
            }
        }
    } else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && rec.current_fill == Cross) {
        Vector2 mouse_pos = GetMousePosition();
        size_t x = find_cell_x(mouse_pos.x, rec);
        size_t y = find_cell_y(mouse_pos.y, rec);
        if (x < rec.grid.n_cols && y < rec.grid.n_rows) {
            if (rec.grid.cells[y][x] != Solid) {
                add_cell(rec, x, y);
            }
        }
    }

    if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && rec.current_fill == Solid) || (IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE) && rec.current_fill == Note) || (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && rec.current_fill == Cross)) {
        for (auto& p: rec.current_line) {
            set_cell(rec, p);
        }
        rec.drag = DRAW;
        rec.current_fill = Empty;
        rec.current_line.clear();
    }
    return true;
}

static char SAVE_TEXT[] = "Press S to save the current Nonogram";
static int SAVE_SIZE = 20;


static Style style = {
        .foreground = FOREGROUND,
        .background = BACKGROUND,
        .thickness = 2.0,
        .radius = 4.0
};

void create_fn::draw(StateRec& rec) {
    BeginDrawing();
    {
        ClearBackground(BACKGROUND);
        DrawFPS(0,0);
        DrawText(SAVE_TEXT, (GetScreenWidth() - MeasureText(SAVE_TEXT, SAVE_SIZE)) / 2, rec.bounds.top - SAVE_SIZE * 2, SAVE_SIZE, FILL);
        color_cells(rec, style);
        draw_grid(rec, style.foreground);
    }
    EndDrawing();
}