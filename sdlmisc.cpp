/*
 * Misc SDL helper functions
 */

# include <SDL/SDL.h>
# include "sdlmisc.h"

void apply_surface (int x, int y, SDL_Surface *source, SDL_Surface *destination) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface (source, NULL, destination, &offset);
}

