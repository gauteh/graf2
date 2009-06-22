// Copyright (c) 2009 Gaute Hope <eg@gaute.vetsj.com>
// axis.cpp: implementer class Axis

# include <SDL/SDL.h>
# include <string>
# include <sstream>

# include "axis.h"
# include "sdl.h"
# include "text.h"

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

        // marks
        float scale_y = static_cast<float>(rect.h) / static_cast<float>(stop - start);
        int zero = (0 - start) * scale_y;

        float inc_y = static_cast<float>(stop - start) / 20;

        int j = 0;

        for (int i = 0; i + zero < rect.h; i += static_cast<float>(rect.h) / 20) {
            draw_line (surface, 15,  zero + i, rect.w, zero + i, color);

            ostringstream no;
            float nof = j * inc_y;
            no << nof;

            Text t (no.str());
            t.set_size (10);
            t.draw ();
            
            apply_surface (0, zero + i, t.get_surface (), surface);

            j++;
        }

        j = 0;
        for (int i = 0; zero - i  > 0; i += static_cast<float>(rect.h) / 20) {
            draw_line (surface, 15,  zero - i, rect.w, zero - i, color);
            ostringstream no;
            float nof = j * inc_y;
            no << nof;

            Text t (no.str());
            t.set_size (10);
            t.draw ();
            
            apply_surface (0, zero - i, t.get_surface (), surface);

            j--;
        }


    } else if (direction == HORIZONTAL) { 
        draw_line (surface, 0, rect.h / 2, rect.w, rect.h / 2, color);
        float scale_x = static_cast<float>(rect.w) / static_cast<float>(stop - start);
        for (int i = 15; i < rect.w; i += static_cast<float>(rect.w) / 20)
            draw_line (surface, i, 5, i, rect.h - 5, color);
    }
}

void Axis::set_direction (int d) {
    direction = d;
}

int Axis::get_direction () { return direction; }

