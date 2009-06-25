// Copyright (c) 2009 Gaute Hope <eg@gaute.vetsj.com>
// axis.cpp: implementer class Axis

#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#endif

# include <SDL.h>
# include <string>
# include <sstream>
# include <iomanip>

# include "axis.h"
# include "sdlmisc.h"
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
string Axis::get_label () { return label; }

void Axis::draw () {
    setup_surface ();
    SDL_FillRect (surface, NULL, 0); // clear surface

    if (direction == VERTICAL) {
        // label
        Text t_label (label);
        t_label.set_size (13);
        t_label.draw ();
        apply_surface (30, rect.h - t_label.get_surface ()->h - 3, t_label.get_surface (), surface);

        draw_line (surface, 15, 0, 15, rect.h, color);

        // marks
        float scale_y = static_cast<float>(rect.h) / static_cast<float>(stop - start);
        int zero = static_cast<int>((0 - start) * scale_y);

        float inc_y = static_cast<float>(stop - start) / 20;


        int j = 0;

        for (int i = 0; i + zero < rect.h; i += static_cast<int>(static_cast<float>(rect.h) / 20)) {
            draw_line (surface, 15,  zero + i, rect.w, zero + i, color);

            ostringstream no;
            float nof = j * inc_y;
            no << setprecision(3) << setfill('0') << nof;

            Text t (no.str());
            t.set_size (10);
            t.draw ();

            apply_surface (16, zero + i +1, t.get_surface (), surface);

            j++;
        }

        j = 0;
        for (int i = 0; zero - i  > 0; i += static_cast<int>(static_cast<float>(rect.h) / 20)) {
            draw_line (surface, 15,  zero - i, rect.w, zero - i, color);
            ostringstream no;
            float nof = j * inc_y;
            no << setprecision(3) << setfill('0') << nof;

            Text t (no.str());
            t.set_size (10);
            t.draw ();

            apply_surface (16, zero - i +1, t.get_surface (), surface);

            j--;
        }

    } else if (direction == HORIZONTAL) {
        // label
        Text t_label (label);
        t_label.set_size (13);
        t_label.draw ();
        apply_surface (rect.w - t_label.get_surface ()->w - 5, 20, t_label.get_surface (), surface);

        draw_line (surface, 0, 15, rect.w, 15, color);
        float scale_x = static_cast<float>(rect.w) / static_cast<float>(stop - start);
        int zero = static_cast<int>((0 - start) * scale_x);
        float inc_x = static_cast<float>(stop - start) / 20;
        int j = 0;

        for (int i = 0; i + zero < rect.w; i += static_cast<int>(static_cast<float>(rect.w) / 20)) {
            draw_line (surface, zero + i, 15, zero + i, 20, color);

            if (j) { // skip 0
                ostringstream no;
                float nof = j * inc_x;
                no << setprecision(3) << setfill('0') << nof;

                Text t (no.str());
                t.set_size (10);
                t.draw ();

                apply_surface (zero + i - static_cast<int>(static_cast<float>(t.get_surface ()->w) / 2.0), 1, t.get_surface (), surface);
            }

            j++;
        }
        j = 0;
        for (int i = 0; zero - i  > 0; i += static_cast<int>(static_cast<float>(rect.w) / 20)) {
            draw_line (surface, zero - i, 15, zero - i, 20, color);

            if (j) { // skip 0
                ostringstream no;
                float nof = j * inc_x;
                no << setprecision(3) << setfill('0') << nof;

                Text t (no.str());
                t.set_size (10);
                t.draw ();

                apply_surface (zero - i - static_cast<int>(static_cast<float>(t.get_surface ()->w) / 2.0), 1, t.get_surface (), surface);
            }

            j--;
        }
    }
}

void Axis::set_direction (int d) {
    direction = d;
}

int Axis::get_direction () { return direction; }
