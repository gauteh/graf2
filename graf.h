/*
 * graf.h: Klassa for oppsett og bakgrunn av graf
 */

# pragma once

# include <string>
# include <SDL.h>

# include "sdlmisc.h"
# include "plot.h"
# include "axis.h"


class Graf : public SDL_Item {
    private:
        int SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP;
        const char* filename;

        // TODO: Put this in vectors
        Axis axis_x;
        Axis axis_y;

        Plot plot_a;
        Plot plot_b;

    public:
        Graf (SDL_Surface*, const char*, int, int, int);

        int run ();

        void draw ();
        bool read ();
};

