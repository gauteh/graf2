/*
 * graf.h: Klassa for oppsett og bakgrunn av graf
 */

# pragma once
# include <string>
# include <SDL/SDL.h>

# include "sdlmisc.h"
# include "plot.h"

class Axis : public SDL_Item {
    private:
        string label;
        float start;
        float stop;
        float increment;
        int direction; // 0 = vertical, 1 = horizontal
        Uint32 color;

    public:
        Axis ();
        Axis (float, float, float);
        void set_start (float);
        void set_stop (float);
        void set_inc (float);

        void set_label (string s);
        void set_direction (int);
        int get_direction ();

        void set_color (Uint32);
        Uint32 get_color ();

        void draw ();
};

class Graf : public SDL_Item {
    private:
        int SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP;
        const char* filename;

        Axis axis_x;
        Axis axis_y;

        vector<Plot> plots; // array of plots

    public:
        Graf (SDL_Surface*, const char*, int, int, int);
        int run ();
        void draw ();

        bool read ();
};

