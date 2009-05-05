/*
 * plot.cpp: Gfx and drawing of each point
 */

# include <SDL/SDL.h>
# include <vector>
# include "plot.h"

using namespace std;

Plot::Plot () {
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
