/* Copyright Gaute Hope (c) 2009 <eg@gaute.vetsj.com>
 *
 * graf.cpp: Klassa for oppsett og bakgrunn av graf
 */

#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#endif

# include <SDL.h>
# include <iostream>
# include <fstream>
# include <string>
# include <vector>

# include "sdlmisc.h"
# include "graf.h"
# include "axis.h"
# include "text.h"

using namespace std;

Graf::Graf (SDL_Surface *s, const char *f, int width, int height, int bpp) {
    surface = s;
    screen = s;

    color = BLACK;

    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    SCREEN_BPP = bpp;

    filename = f;
    if (!read ()) {
        cout << "Failed to read: " << filename  << "!" << endl;
        exit (1);
    }

}

int Graf::run () {
    // SDL events
    SDL_Event event;
    int run = 1;

    while (run && SDL_WaitEvent (&event)) {
        switch (event.type) {
            case SDL_QUIT:
                cout << "Goodbye!\n";
                run = 0;
                break;

            case SDL_KEYDOWN:
            case SDL_PRESSED:
                switch (event.key.keysym.sym) {
                    case SDLK_q:
                        cout << "Goodbye!\n";
                        run = 0;
                        break;

                    case SDLK_a:
                        plot_a.toggle_active ();
                        break;

                    case SDLK_b:
                        plot_b.toggle_active ();
                        break;
                }
        }

        draw ();

    }

    return 0;
}

void Graf::draw () {
    // clear screen
    SDL_FillRect (screen, NULL, color);

    // plots
    SDL_Rect r;
    r.h = SCREEN_HEIGHT;
    r.w = SCREEN_WIDTH;
    r.x = 0;
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

    // labels for plots
    Text l_a ("Plot a: " + plot_a.get_label ());
    l_a.set_color (plot_a.get_color());
    l_a.draw ();

    Text l_b ("Plot b: " + plot_b.get_label ());
    l_b.set_color (plot_b.get_color());
    l_b.draw ();

    int widest = 0;
    if (l_a.get_surface ()->w > l_b.get_surface ()->w) {
        widest = l_a.get_surface ()->w;
    } else {
        widest = l_b.get_surface ()->w;
    }
    int hi = 0;
    if (l_a.get_surface ()->h > l_b.get_surface ()->h) {
        hi = l_a.get_surface ()->h;
    } else {
        hi = l_b.get_surface ()->h;
    }

    apply_surface (screen->w - widest - 10, screen->h - hi - 10, l_a.get_surface(), screen);
    apply_surface (screen->w - widest - 10, screen->h - 2*(hi) - 10, l_b.get_surface(), screen);

    // draw axis
    SDL_Rect * ax_rect = axis_x.get_rect ();
    SDL_Rect * ay_rect = axis_y.get_rect ();

    ax_rect->h = 50;
    ax_rect->w = SCREEN_WIDTH;
    ay_rect->h = SCREEN_HEIGHT;
    ay_rect->w = 50;

    ax_rect->x = 0;
    ax_rect->y = plot_a.get_point_zero() - 15;
    if (ax_rect->y <= -15) ax_rect->y = -14;

    ay_rect->y = 0;
    ay_rect->x = plot_a.get_point_middle () - 15;
    if (ay_rect->x <= -15) ay_rect->x = -14;

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

    data.ignore (256, '\n'); // ignorer header for now

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

    plot_a.set_label ("V1");
    plot_a.set_index (0);
    plot_b.set_label ("V2");
    plot_b.set_index (1);

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

    plot_a.set_global_start (t_start);
    plot_b.set_global_start (t_start);
    plot_a.set_global_stop (t);
    plot_b.set_global_stop (t);

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
