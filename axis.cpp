// axis.cpp: implementer class Axis

# include <SDL/SDL.h>
# include <string>

# include "axis.h"
# include "sdl.h"

using namespace std;

Axis::Axis (float _start, float _stop) {
    start = _start;
    stop = _stop;
    surface = NULL;
    direction = Axis::VERTICAL;
}

Axis::Axis () {
    start = 0;
    stop = 0;
    direction = Axis::VERTICAL;
    surface = NULL;
}

void Axis::set_start (float s) { start = s; }
void Axis::set_stop (float s) { stop = s; }
void Axis::set_label (string s) { label = s; }

void Axis::draw () {
    setup_surface (); 
    SDL_FillRect (surface, NULL, 0); // clear surface

    if (direction == VERTICAL) {
        draw_line (surface, rect.w / 2, 0, rect.w / 2, rect.h, color);
    } else if (direction == HORIZONTAL) { 
        draw_line (surface, 0, rect.h / 2, rect.w, rect.h / 2, color);
    }
}

void Axis::set_direction (int d) {
    direction = d;
}

int Axis::get_direction () { return direction; }

