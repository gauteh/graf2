// Copyright (c) 2009 Gaute Hope <eg@gaute.vetsj.com>
// text.cpp: sdl text objects

#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "SDL_ttf.lib")
#endif

# include <iostream>
# include <string>

# include <SDL.h>
# include <SDL_ttf.h>

# include "text.h"
# include "sdlmisc.h"

Text::Text () {
    font = NULL;
    text = "";
    size = 14;
}

Text::Text (string t) {
    text = t;
    font = NULL;
    size = 14;
}

void Text::set_size (float s) {
    size = s;
}

float Text::get_size () {
    return size;
}

void Text::draw () {
    if (font == NULL)
        font = TTF_OpenFont ("verdana.ttf", size);

    SDL_Color c;
    c.r = color >> 16;
    c.g = color >> 8;
    c.b = color;

    SDL_Color b;
    b.r = BLACK >> 16;
    b.g = BLACK >> 8;
    b.b = BLACK;

    surface = TTF_RenderText_Shaded (font, text.data(), c, b);
    if (surface == NULL) {
        cout << "Could not render text!\n" << TTF_GetError () << endl;
    }
    rect.w = surface->h;
    rect.h = surface->w;

    if (font != NULL)
        TTF_CloseFont (font);
}

