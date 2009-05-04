/*
 * graf.cpp: Klassa for oppsett og bakgrunn av graf
 */

# include <SDL/SDL.h>

# include "graf.h"
# include "sdlmisc.h"

using namespace std;

Axis::Axis (float _start, float _stop, float _increment) {
    start = _start;
    stop = _stop;
    increment = _increment;
}

void Axis::set_start (float s) { start = s; }
void Axis::set_stop (float s) { stop = s; }
void Axis::set_inc (float s) { increment = s; }

SDL_Surface * Axis::get_surface () { return &surface; }
SDL_Rect * Axis::get_rect () { return &rect; }

void Axis::set_rect (SDL_Rect *r) {
    rect.x = r->x;
    rect.y = r->y;
    rect.h = r->h;
    rect.w = r->w;
}

void Axis::draw () {
    // draw/redraw axis on local surface
}


