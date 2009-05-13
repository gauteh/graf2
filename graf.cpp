/*
 * graf.cpp: Klassa for oppsett og bakgrunn av graf
 */

# include <SDL/SDL.h>
# include <iostream>
# include <fstream>
# include <string>
# include <vector>

# include "graf.h"
# include "sdlmisc.h"

using namespace std;

Axis::Axis (float _start, float _stop, float _increment) {
    start = _start;
    stop = _stop;
    increment = _increment;
    surface = NULL;
    direction = 0;
    color = WHITE;
}

Axis::Axis () {
    start = 0;
    stop = 0;
    increment = 0;
    direction = 0;
    surface = NULL;
    color = WHITE;
}

void Axis::set_start (float s) { start = s; }
void Axis::set_stop (float s) { stop = s; }
void Axis::set_inc (float s) { increment = s; }
void Axis::set_label (string s) { label = s; }
void Axis::set_color (Uint32 c) { color = c; }
Uint32 Axis::get_color () { return color; }

void Axis::draw () {
    setup_surface (); 
    if (direction) {
        draw_line (surface, rect.w / 2, 0, rect.w / 2, rect.h, color);
    } else {
        draw_line (surface, 0, rect.h / 2, rect.w, rect.h / 2, color);
    }
}

void Axis::set_direction (int d) {
    direction = d;
}

int Axis::get_direction () { return direction; }

Graf::Graf (SDL_Surface *s, const char *f, int width, int height, int bpp) {
    surface = s;
    screen = s;

    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    SCREEN_BPP = bpp;

    filename = f;
    if (!read ()) exit (1);

    draw ();
    SDL_Flip (get_surface ());
    
    while (run ());
}

void Graf::draw () {
    // draw axis
    SDL_Rect * ax_rect = axis_x.get_rect ();
    SDL_Rect * ay_rect = axis_y.get_rect ();

    ax_rect->h = SCREEN_HEIGHT;
    ax_rect->w = 30;
    ay_rect->h = 30;
    ay_rect->w = SCREEN_WIDTH;

    ax_rect->x = 0;
    ax_rect->y = 0; 
    ay_rect->x = 0;
    ay_rect->y = SCREEN_HEIGHT - ay_rect->h; 

    axis_x.set_screen (screen);
    axis_y.set_screen (screen);

    axis_x.draw ();
    axis_y.draw ();
    
    apply_surface (axis_x.get_rect()->x, axis_x.get_rect()->y, axis_x.get_surface (), surface);
    apply_surface (axis_y.get_rect()->x, axis_y.get_rect()->y, axis_y.get_surface (), surface);

    // plots
    vector<Plot>::iterator p;
    float max = 0;
    float min = 0;
    int points = 0;
    for (p = plots.begin (); p != plots.end (); p++) {
        if (p->get_min () < min)
            min = p->get_min ();
        
        if (p->get_max() > max)
            max = p->get_max ();

        if (p->get_points () > points) 
            points = p->get_points ();
    }

    SDL_Rect r;
    r.h = SCREEN_HEIGHT - 30;
    r.w = SCREEN_WIDTH - 30;
    r.x = 30;
    r.y = 0;
   
    if (min > 0)
        min = 0; // start på 0 uansett
    int inc_x = r.w / points;
    int inc_y = r.h / (max - min);

    //bool first = true;
    for (p = plots.begin (); p != plots.end (); p++) {
        p->set_inc (inc_x, inc_y);
        p->set_draw_min (min);
        p->set_rect (&r);
        p->set_screen(screen);

        p->draw ();
        apply_surface (r.x, r.y, p->get_surface (), screen);
        cout << "Draw plot.." << endl;
    }
}

int Graf::run () {
    // events
    SDL_Event event;
    int run = 1;

    while (run) {
        while (SDL_PollEvent (&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                case SDL_PRESSED:
                    switch (event.key.keysym.sym) {
                        case SDLK_q:
                            cout << "'Q' pressed, Goodbye!\n";
                            run = 0;
                            break;
                    }
            }
        }
    }
    
    return 0;
}

bool Graf::read () {
    fstream data (filename, ios::in);
    if (!data) return false;

    data.ignore (256, '\n'); // ignorer header for no 

    /*
     * TODO: Ta hensyn til meir eller mindre enn tre kolonner
     */
    
    Plot a, b;

    float t, x, y;
    int i = 0;
    data >> t >> x >> y;
    float t_start = t;

    while (!data.eof ()) {
        //cout << "t=" << t << ", x=" << x << ", y=" << y << endl;
        a.add_point (t, x);
        b.add_point (t, y);

        data >> t >> x >> y;
        i++;
    }

    data.close ();

    a.set_label ("Vi");
    b.set_label ("Vo");

    plots.push_back (a);
    plots.push_back (b);

    float t_end = t;

    float inc; // rekn ut mellomrom på x aksa
    inc = (t_end - t_start) / i;

    axis_x.set_start (t_start);
    axis_x.set_stop (t_end);
    axis_x.set_inc (inc);
    axis_x.set_direction (1); 
    axis_x.set_label ("tid (s)");

    // finn maks
    float max = 0;
    if (a.get_max () > b.get_max ()) {
        max = a.get_max ();
    } else {
        max = b.get_max ();
    }

    // finn min
    float min = 0;
    if (a.get_min () < b.get_min ()) {
        min = a.get_min ();
    } else {
        min = b.get_min ();
    }

    inc = (t_end - t_start) / i;
    axis_y.set_direction (0);
    axis_y.set_start (min);
    axis_y.set_stop (max);
    axis_y.set_inc (inc);
    axis_y.set_label ("[V]");

    return true;
}
