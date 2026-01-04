#include "grid.h"

Grid new_grid(const int size_x, const int size_y) {
    Grid g = {
            .n_rows = size_y,
            .n_cols = size_x,
            .row_max_rules = 0,
            .col_max_rules = 0,
    };
    g.row_rules.resize(size_y);
    g.col_rules.resize(size_x);
    g.row_rules.clear();
    g.col_rules.clear();
    g.cells.resize(size_x * size_y, Empty);
    return g;
}

size_t get_x(const size_t index, const Grid& grid) {
    return index % grid.n_cols;
}

size_t get_y(const size_t index, const Grid& grid) {
    return index / grid.n_cols;
}

size_t get_index(const size_t x, const size_t y, const Grid& grid) {
    return y * grid.n_cols + x;
}

size_t get_index(const Point& point, const Grid& grid) {
    return get_index(point.x, point.y, grid);
}

void draw_grid(StateRec& rec, const Color color) {
    // why draw n*m boxes when you could draw n+m lines
    // draw vertical lines
    for (int i = 0; i <= rec.grid.n_cols; i++) {
        const int x = i * rec.cell_size + rec.bounds.left;
        DrawLine(x, rec.bounds.top, x, rec.bounds.bottom, color);
    }
    // draw horizontal lines
    for (int i = 0; i <= rec.grid.n_rows; i++) {
        const int y = i * rec.cell_size + rec.bounds.top;
        DrawLine(rec.bounds.left, y, rec.bounds.right, y, color);
    }
}

void color_cells(const StateRec& rec, const Style& style) {
    float left;
    float right;
    float top;
    float bottom;
    for (int i = 0; i < rec.grid.n_rows * rec.grid.n_cols; i++) {
        size_t x = get_x(i, rec.grid);
        size_t y = get_y(i, rec.grid);
        left = rec.bounds.left + x * rec.cell_size;
        top = rec.bounds.top + y * rec.cell_size;

        switch (rec.grid.cells[i]) {
            case Solid:
                DrawRectangle(left, top, rec.cell_size, rec.cell_size, style.foreground);
                break;
            case Empty:
                break;
            case Cross:
                right = left + rec.cell_size;
                bottom = top + rec.cell_size;
                DrawLineEx({left, top}, {right, bottom}, style.thickness, style.foreground);
                DrawLineEx({left, bottom}, {right, top}, style.thickness, style.foreground);
                break;
            case Note:
                DrawCircle(left + rec.cell_size / 2, top + rec.cell_size / 2, style.radius, style.foreground);
                break;
        }
    }

    FillType fill;
    if (rec.drag == CLEAR) {
        fill = Empty;
    } else {
        fill = rec.current_fill;
    }

    // because this is designed to overwrite the already drawn grid state,
    // all fills have a background rect added to them
    for (auto& p: rec.current_line) {
        switch (fill) {
            case Solid:
                DrawRectangle(rec.bounds.left + p.x * rec.cell_size, rec.bounds.top + p.y * rec.cell_size, rec.cell_size, rec.cell_size, style.foreground);
                break;
            case Empty:
                DrawRectangle(rec.bounds.left + p.x * rec.cell_size, rec.bounds.top + p.y * rec.cell_size, rec.cell_size, rec.cell_size, style.background);
                break;
            case Cross:
                left = rec.bounds.left + p.x * rec.cell_size;
                right = left + rec.cell_size;
                top = rec.bounds.top + p.y * rec.cell_size;
                bottom = top + rec.cell_size;
                DrawRectangle(left, top, rec.cell_size, rec.cell_size, style.background);
                DrawLineEx({left, top}, {right, bottom}, style.thickness, style.foreground);
                DrawLineEx({left, bottom}, {right, top}, style.thickness, style.foreground);
                break;
            case Note:
                DrawCircle(rec.bounds.left + p.x * rec.cell_size + rec.cell_size / 2, rec.bounds.top + p.y * rec.cell_size + rec.cell_size / 2, style.radius, style.foreground);
                break;
        }
    }
}

size_t find_cell_x(const float x, const StateRec& rec) {
    return (x - rec.bounds.left) / rec.cell_size;
}

size_t find_cell_y(const float y, const StateRec& rec) {
    return (y - rec.bounds.top) / rec.cell_size;
}

void set_cell(const StateRec& rec, const Point& point) {
    if (point.x >= rec.grid.n_cols || point.y >= rec.grid.n_rows) {
        return;
    }
    size_t index = get_index(point, rec.grid);
    switch (rec.grid.cells[index]) {
        case Empty:
            rec.grid.cells[index] = rec.current_fill;
            break;
        case Solid:
            if (rec.current_fill == Solid) {
                rec.grid.cells[index] = Empty;
            }
            break;
        case Cross:
            if (rec.current_fill == Cross) {
                rec.grid.cells[index] = Empty;
            }
            break;
        case Note:
            if (rec.current_fill == Note) {
                rec.grid.cells[index] = Empty;
            } else {
                rec.grid.cells[index] = rec.current_fill;
            }
            break;
    }


}