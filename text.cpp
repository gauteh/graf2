// Copyright (c) 2009 Gaute Hope <eg@gaute.vetsj.com>
// text.cpp: sdl text objects

#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "SDL_ttf.lib")
#endif

# include <iostream>
# include <cstdlib>
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

void Text::set_size (int s) {
    size = s;
}

int Text::get_size () {
    return size;
}

void Text::draw () {
    string fonturi;
# ifdef WIN32
    char *pValue;
    size_t len;
    _dupenv_s (&pValue, &len, "SYSTEMROOT");

    fonturi += pValue;
    free (pValue);

    fonturi += "\\Fonts\\verdana.ttf";
# else
    // TODO: ^^ Proper define that catches Linux

    fonturi = "/usr/share/fonts/TTF/verdana.ttf";
    if (access (fonturi.data (), R_OK)) {
        cout << "Failed to open system font: " << fonturi << ", trying local.." << endl;
        if (access ("verdana.ttf", R_OK)) {
            cout << "Could not open font verdana.ttf!" << endl
                 << "It should either be located in:" << endl
                 << "/usr/share/fonts/TTF/ or" << endl
                 << "the local directory."  << endl;
            exit (1);
        } else {
            fonturi = "./verdana.ttf";
        }
    }
# endif


    if (font == NULL)
        font = TTF_OpenFont (fonturi.data(), size);
    if (font == NULL) {
        cout << "Failed to open font: " << fonturi << "!" << endl;
        exit (1);
    }

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
        cout << "Could not render text: " << TTF_GetError () << endl;
    }
    rect.w = surface->h;
    rect.h = surface->w;

    if (font != NULL)
        TTF_CloseFont (font);
}

