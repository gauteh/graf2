// Copyright (c) 2009 Gaute Hope <eg@gaute.vetsj.com>
// class for sdl text objects

# pragma once

# include <iostream>
# include <string>

# include <SDL/SDL.h>
# include <SDL_ttf.h>

# include "sdl.h"

using namespace std;

class Text : public SDL_Item {
    private:
        string text;
        TTF_Font *font;
        float size;
    public:
        Text ();
        Text (string);

        void set_size (float);
        float get_size ();

        void draw ();
};

