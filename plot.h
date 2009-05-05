/*
 * plot.h: Gfx and drawing of each plot
 */

# pragma once
# include <SDL/SDL.h>
# include <string>
# include <vector>

# include "sdlmisc.h"

using namespace std;

class Plot : public SDL_Item {
    private:
        string label;
        int points;
        vector<float> x;
        vector<float> y;

    public:
        Plot ();
        void set_label (string s);
        void add_point (float, float);
        int get_points ();
        vector<float> get_x ();
        vector<float> get_y ();

        float get_max ();
        float get_min ();
};
