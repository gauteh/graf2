// Copyright (c) 2009 Gaute Hope <eg@gaute.vetsj.com>
// plot.h: Gfx and drawing of each plot

# pragma once

# include <SDL.h>
# include <string>
# include <vector>

# include "sdlmisc.h"

using namespace std;

class Plot : public SDL_Item {
    private:
        int index;

        string label;
        int points;
        vector<float> x;
        vector<float> y;

        // y-axis
        float global_min;
        float global_max;

        // x-axis
        float global_start;
        float global_stop;

    public:
        Plot ();
        void draw ();
        void set_label (string s);
        string get_label ();
        void add_point (float, float);
        int get_points ();
        vector<float> get_x ();
        vector<float> get_y ();

        float get_max ();
        float get_min ();

        void set_global_min (float);
        void set_global_max (float);

        float get_global_min ();
        float get_global_max ();
        int get_point_zero (); // point on screen where 0 on the y-axis is

        float get_global_start ();
        float get_global_stop ();
        void set_global_start (float);
        void set_global_stop (float);
        int get_point_middle (); // point on screen where 0 on the x-axis is

        void set_index (int);
        int get_index ();
};

