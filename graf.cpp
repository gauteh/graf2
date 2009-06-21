/* Copyright Gaute Hope (c) 2009 <eg@gaute.vetsj.com>
 *
 * graf.cpp: Klassa for oppsett og bakgrunn av graf
 */

# include <SDL/SDL.h>
# include <iostream>
# include <fstream>
# include <string>
# include <vector>

# include "graf.h"
# include "axis.h"
# include "sdl.h"

using namespace std;

Graf::Graf (SDL_Surface *s, const char *f, int width, int height, int bpp) {
    surface = s;
    screen = s;

    color = BLACK;

    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    SCREEN_BPP = bpp;

    filename = f;
    if (!read ()) exit (1);

    draw ();
    SDL_Flip (get_surface ());
    
    while (run ());
}

int Graf::run () {
    // SDL events
    SDL_Event event;
    int run = 1;

    while (run && SDL_WaitEvent (&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
            case SDL_PRESSED:
                switch (event.key.keysym.sym) {
                    case SDLK_q:
                        cout << "\nGoodbye!\n";
                        run = 0;
                        break;

                    case SDLK_a:
                        plot_a.toggle_active ();
                        draw ();
                        break;

                    case SDLK_b:
                        plot_b.toggle_active ();
                        draw ();
                        break;
                }
        }
    }
    
    return 0;
}

void Graf::draw () {
    // clear screen
    SDL_FillRect (screen, NULL, color);

    // plots
    SDL_Rect r; 
    r.h = SCREEN_HEIGHT; 
    r.w = SCREEN_WIDTH - 15; 
    r.x = 15;
    r.y = 0; // horisontal aksa er på 30/2

    plot_a.set_rect (&r);
    plot_a.set_screen (screen);

    plot_b.set_rect (&r);
    plot_b.set_screen (screen);

    plot_a.set_color (PLOT_A);
    plot_b.set_color (PLOT_B);

    plot_a.draw ();
    plot_b.draw ();

    if (plot_a.is_active ())
        apply_surface (r.x, r.y, plot_a.get_surface (), screen);
    if (plot_b.is_active ())
        apply_surface (r.x, r.y, plot_b.get_surface (), screen);

    // draw axis
    SDL_Rect * ax_rect = axis_x.get_rect ();
    SDL_Rect * ay_rect = axis_y.get_rect ();

    ax_rect->h = 30;
    ax_rect->w = SCREEN_WIDTH;
    ay_rect->h = SCREEN_HEIGHT;
    ay_rect->w = 30;

    ax_rect->x = 0;
    ax_rect->y = plot_a.get_point_zero(); 
    ay_rect->x = 0;
    ay_rect->y = 0; 

    axis_x.set_screen (screen);
    axis_y.set_screen (screen);

    axis_x.set_color (AXIS);
    axis_y.set_color (AXIS);

    axis_x.draw ();
    axis_y.draw ();
    
    apply_surface (axis_x.get_rect()->x, axis_x.get_rect()->y, axis_x.get_surface (), surface);
    apply_surface (axis_y.get_rect()->x, axis_y.get_rect()->y, axis_y.get_surface (), surface);

    SDL_UpdateRect (screen, 0, 0, 0, 0);
}


bool Graf::read () {
    fstream data (filename, ios::in);
    if (!data) return false;

    data.ignore (256, '\n'); // ignorer header for no 

    float t, x, y;
    int i = 0;
    data >> t >> x >> y;
    float t_start = t;

    while (!data.eof ()) {
        //cout << "t=" << t << ", x=" << x << ", y=" << y << endl;
        plot_a.add_point (t, x);
        plot_b.add_point (t, y);

        data >> t >> x >> y;
        i++;
    }

    data.close ();

    plot_a.set_label ("Vi");
    plot_b.set_label ("Vo");

    // finn maks
    float max = 0;
    if (plot_a.get_max () > plot_b.get_max ()) {
        max = plot_a.get_max ();
    } else {
        max = plot_b.get_max ();
    }
    plot_a.set_global_max (max);
    plot_b.set_global_max (max);

    // finn min
    float min = 0;
    if (plot_a.get_min () < plot_b.get_min ()) {
        min = plot_a.get_min ();
    } else {
        min = plot_b.get_min ();
    }

    plot_a.set_global_min (min);
    plot_b.set_global_min (min);

    // set up axis
    axis_y.set_direction (Axis::VERTICAL);
    axis_y.set_start (min);
    axis_y.set_stop (max);
    axis_y.set_label ("[V]");

    axis_x.set_start (t_start);
    axis_x.set_stop (t);
    axis_x.set_direction (Axis::HORIZONTAL); 
    axis_x.set_label ("tid (s)");

    return true;
}
