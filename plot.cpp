// Copyright (c) 2009 Gaute Hope <eg@gaute.vetsj.com>
// plot.cpp: Gfx and drawing of each point

# include <iostream>
# include <iomanip>
# include <SDL/SDL.h>
# include <vector>
# include <cmath>

# include "plot.h"
# include "text.h"

using namespace std;

Plot::Plot () {
    screen = NULL;
    surface = NULL;
    points = 0;
    index = 0;
    color = rand () % 0xFFFFFF;
}

void Plot::set_label (string s) {
    label = s;
}

string Plot::get_label () {
    return label;
}

int Plot::get_points () { return points; }
vector<float> Plot::get_x () { return x; }
vector<float> Plot::get_y () { return y; }

void Plot::add_point (float _x, float _y) {
   x.push_back (_x);
   y.push_back (_y);
   points++;
}

void Plot::set_index (int i) {
    index = i;
}

int Plot::get_index () {
    return index;
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

void Plot::set_global_min (float m) {
    global_min = m;
}

float Plot::get_global_min () {
    return global_min;
}

float Plot::get_global_max () {
    return global_max;
}

int Plot::get_point_zero () {
    float scale_y = static_cast<float>(rect.h) / static_cast<float>(global_max - global_min);

    int y = (0 - global_min) * scale_y;
    return y;
}

void Plot::set_global_max (float m) {
    global_max = m;
}

void Plot::draw () {
    setup_surface ();

    SDL_FillRect (surface, NULL, 0); // clear surface

    float scale_x = static_cast<float>(rect.w) / static_cast<float>(points);
    float scale_y = static_cast<float>(rect.h) / static_cast<float>(global_max - global_min);

    int n_x = 0;

    vector<float>::iterator i_y;
    int p_x = 0;
    int p_y = 0;

    //cout << "Draw plot [" << label << "]:" << endl;
    //cout << "Height: " << setw(3) << rect.h << endl;
    //cout << "Width:  " << setw(3) << rect.w << endl;
    //cout << "Points: " << setw(3) << points << ", scale_x: " << scale_x << endl;
    //cout << "             scale_y: " << scale_y << endl;
    //cout << "Color: 0x" << hex << color << endl;
    
    for (i_y = y.begin (); i_y != y.end (); i_y++) {
        int y = (*(i_y) - global_min) * scale_y;
        int x = static_cast<float>(n_x) * scale_x;

        //put_pixel32 (surface, x, y, WHITE);

        if (p_x)
            draw_line (surface, p_x, p_y, x, y, color);

        p_x = x;
        p_y = y;

        n_x++;

        //cout << "[Plot=" << label << "] x=" << x << ", y=" << y << " (scale=" << scale_y << ", max=" << global_max << ", min=" << global_min << ")" << endl;
    }
}
