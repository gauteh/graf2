// Copyright (c) 2009 Gaute Hope <eg@gaute.vetsj.com>
// axis.h: Akser

# pragma once

# include <string>
# include <SDL.h>

# include "sdlmisc.h"

using namespace std;

class Axis : public SDL_Item {
    private:
        string label;
        float start;
        float stop;
        int direction;

    public:
        static const int VERTICAL = 0;
        static const int HORIZONTAL = 1;

        Axis ();
        Axis (float, float);
        void set_start (float);
        void set_stop (float);

        void set_label (string s);
        void set_direction (int);
        int get_direction ();

        void draw ();
};

