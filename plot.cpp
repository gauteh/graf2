/*
 * plot.cpp: Gfx and drawing of each point
 */

# include <iostream>
# include <SDL/SDL.h>
# include <vector>
# include <cmath>
# include "plot.h"

using namespace std;

Plot::Plot () {
    screen = NULL;
    surface = NULL;
    points = 0;
    color = WHITE;
    inc_x = 0;
    inc_y = 0;
    draw_min = 0;
}

void Plot::set_label (string s) {
    label = s;
}

int Plot::get_points () { return points; }
vector<float> Plot::get_x () { return x; }
vector<float> Plot::get_y () { return y; }

void Plot::add_point (float _x, float _y) {
   x.push_back (_x);
   y.push_back (_y);
   points++;
}

float Plot::get_max () {
    float max = y[0];
    vector<float>::iterator iter;
    for (iter = y.begin (); iter != y.end (); iter++) {
        if (*iter > max) max = *iter;
    }

    return max;
}

float Plot::get_min () {
    float min = y[0];
    vector<float>::iterator iter;
    for (iter = y.begin (); iter != y.end (); iter++) {
        if (*iter < min) min = *iter;
    }

    return min;
}

void Plot::set_inc (int ix, int iy) {
    inc_x = ix;
    inc_y = iy;
}

void Plot::set_draw_min (float m) {
    draw_min = m;
}

void Plot::set_draw_max (float m) {
    draw_max = m;
}

void Plot::set_global_min (float m) {
    global_min = m;
}

void Plot::set_global_max (float m) {
    global_max = m;
}

void Plot::draw () {
    setup_surface ();

    SDL_FillRect (surface, NULL, 0); // clear surface

    float scale_x = rect.w / points;
    float scale_y = rect.h / (global_max - global_min);

    int n_x = 0;

    vector<float>::iterator i_y;
    int p_x = 0;
    int p_y = 0;
    
    for (i_y = y.begin (); i_y != y.end (); i_y++) {
        int y = (*(i_y) - global_min) * scale_y;
        int x = n_x * scale_x;

        put_pixel32 (surface, x,  y, WHITE);

        n_x++;
        //cout << "[Plot=" << label << "] y=" << y << " (scale=" << scale_y << ", max=" << global_max << ", min=" << global_min << ")" << endl;

        if (p_x)
            draw_line (surface, p_x, p_y, x, y, WHITE);
        p_x = x;
        p_y = y;
    }
}
