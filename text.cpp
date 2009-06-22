// Copyright (c) 2009 Gaute Hope <eg@gaute.vetsj.com>
// text.cpp: sdl text objects

# include <iostream>
# include <string>

# include <SDL/SDL.h>
# include <SDL/SDL_ttf.h>

# include "text.h"
# include "sdl.h"

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

