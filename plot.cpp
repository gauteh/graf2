/*
 * plot.cpp: Gfx and drawing of each point
 */

# include <SDL/SDL.h>
# include <vector>
# include "plot.h"

using namespace std;

Plot::Plot () {
    surface = NULL;
    points = 0;
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

void Plot::draw () {
    setup_surface ();

    float inc_x = rect.w / points; 
    int n_x = 0;

    vector<float>::iterator i_y;
    for (i_y = y.begin (); i_y != y.end (); i_y++) {
        int y = *(i_y) * (rect.h / (get_max () - get_min ()));
        int x = n_x * inc_x;
        put_pixel32 (surface, x, rect.h - y, WHITE);
    }

    //assume there exists equally many y's as x's
    //for (i_x = x.begin(); i_x != x.end (); i_x++) {
        //float t = *(i_y);
        //put_pixel32 (surface, n_x * inc_x, rect.h - (t * inc_y), WHITE);
        //i_y++;
        //n_x++;
    //}
}
