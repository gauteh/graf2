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

        float global_min;
        float global_max;

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

        void set_global_min (float);
        void set_global_max (float);
};

