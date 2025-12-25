#include <vector>
#include <iostream>
#include "raylib.h"

enum FillType {
    Empty,
    Solid,
    Cross,
    Note,
};

struct Rules {
    int n_rules;
    std::vector<int> rules;
};

struct Grid {
    int n_rows;
    int n_cols;
    int row_max_rules;
    int col_max_rules;
    std::vector<Rules> row_rules;
    std::vector<Rules> col_rules;
    std::vector<std::vector<FillType>> cells;
};

struct Bounds {
    int left;
    int right;
    int top;
    int bottom;
};

/// Create a new grid structure with the given dimensions.
Grid create_grid(const int size_x, const int size_y) {
    Grid g;
    g.n_cols = size_x;
    g.n_rows = size_y;
    g.row_rules.resize(size_y);
    g.col_rules.resize(size_x);
    g.row_max_rules = 0;
    g.col_max_rules = 0;
    g.cells.resize(size_y);
    for (int i = 0; i < size_y; i++) {
        g.cells[i].resize(size_x);
    }
    return g;
}

/// Create a new bounds structure with the given limits.
Bounds create_bounds(const int left, const int right, const int top, const int bottom) {
    Bounds b;
    b.left = left;
    b.right = right;
    b.top = top;
    b.bottom = bottom;
    return b;
}

/// Compute the actual bounds such that each cell is a square
Bounds compute_bounds(const int n_cols, const int n_rows, const int cell_size, const int left, const int right, const int top, const int bottom) {
    const int width = cell_size * n_cols;
    const int height = cell_size * n_rows;
    const int horizontal_offset = (right - left - width) / 2;
    const int vertical_offset = (bottom - top - height) / 2;
    const int start_x = left + horizontal_offset;
    const int start_y = top + vertical_offset;
    const int end_x = right - horizontal_offset;
    const int end_y = bottom - vertical_offset;

    return create_bounds(start_x, end_x, start_y, end_y);
}

/// Draws grid of squares
/// Returns actual size of grid after scaling
Bounds draw_grid(const int n_cols, const int n_rows, const int cell_size, const int left, const int right, const int top, const int bottom, const Color color) {
    // why draw n*m boxes when you could draw n+m lines
    Bounds b = compute_bounds(n_cols, n_rows, cell_size, left, right, top, bottom);
    // draw vertical lines
    for (int i = 0; i <= n_cols; i++) {
        const int x = i * cell_size + b.left;
        DrawLine(x, b.top, x, b.bottom, color);
    }
    // draw horizontal lines
    for (int i = 0; i <= n_rows; i++) {
        const int y = i * cell_size + b.top;
        DrawLine(b.left, y, b.right, y, color);
    }
    return b;
}

/// Compute the x and y index of the cell a the given position.
std::tuple<size_t, size_t> find_cell(const Vector2& pos, const int cell_size, const Bounds bounds) {
    int x = (pos.x - bounds.left) / cell_size;
    int y = (pos.y - bounds.top) / cell_size;
    return std::make_tuple(x, y);
}

/// Change the state of the cell at the given index
void set_cell(Grid& g, const size_t x, const size_t y, const FillType fill) {
    if (x >= g.n_cols || y >= g.n_rows) {
        return;
    }
    g.cells[y][x] = fill;
}

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

    // ----- INIT STATE -----
    Grid g = create_grid(15,  15);
    const int padding = 100;
    const int cell_size = 50;
    Bounds actual_bounds = compute_bounds(g.n_cols, g.n_rows, cell_size, padding, GetScreenWidth() - padding, padding, GetScreenHeight() - padding);


    // ----- EVENT AND RENDER LOOP -----
    while (!WindowShouldClose()) {
        // ----- EVENT HANDING -----
        if (IsKeyPressed(KEY_ESCAPE)) {
            break;
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

        // ----- RENDERING -----
        BeginDrawing(); {
            ClearBackground(Color(0x33, 0x33, 0x33));
            actual_bounds = draw_grid(g.n_cols, g.n_rows, cell_size, padding, GetScreenWidth() - padding, padding, GetScreenHeight() - padding, RAYWHITE);
        } EndDrawing();
    }

    // ----- CLEANUP -----
    CloseWindow();

    return 0;
}
