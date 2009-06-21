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
    public:
        Text ();
        Text (string);

        void draw ();
};

