/*
 * plot.h: Gfx and drawing of each plot
 */

# pragma once
# include <SDL/SDL.h>
# include <string>
# include <vector>

# include "sdl.h"

using namespace std;

class Plot : public SDL_Item {
    private:
        string label;
        int points;
        vector<float> x;
        vector<float> y;

        int inc_x;
        int inc_y;

        float draw_min;
        float draw_max;

        float global_min;
        float global_max;

        Uint32 color;

    public:
        Plot ();
        void draw ();
        void set_label (string s);
        void add_point (float, float);
        int get_points ();
        vector<float> get_x ();
        vector<float> get_y ();

        float get_max ();
        float get_min ();

        void set_inc (int, int);
        void set_draw_min (float);
        void set_draw_max (float);

        void set_global_min (float);
        void set_global_max (float);
};

