#ifndef NO2GRM_RENDER_H
#define NO2GRM_RENDER_H
#include "grid.h"
#include "SDL3/SDL_render.h"

namespace render {

    void render_grid(grid::Grid& grid, SDL_Renderer* renderer);

} // namespace render

#endif