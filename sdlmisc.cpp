/*
 * Copyright (c) 2009 Gaute Hope <eg@gaute.vetsj.com>
 *
 * sdlmisc.cpp:
 * Misc SDL helper functions
 *
 * SDL_Item class, common members and functions of SDL objects
 */

#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#endif

# include <iostream>
# include <SDL.h>

# include "sdlmisc.h"

using namespace std;


/*
 * class SDL_Item:
 */
SDL_Item::SDL_Item () {
    color = WHITE;
    active = true;
}

SDL_Surface * SDL_Item::get_surface () { return surface; }
SDL_Rect * SDL_Item::get_rect () { return &rect; }

void SDL_Item::set_rect (SDL_Rect *r) {
    rect.x = r->x;
    rect.y = r->y;
    rect.h = r->h;
    rect.w = r->w;
}

void SDL_Item::set_screen (SDL_Surface *s) {
    screen = s;
}

void SDL_Item::setup_surface () {
    if (surface == NULL) {
        surface = SDL_CreateRGBSurface (SDL_SRCCOLORKEY, rect.w, rect.h, screen->format->BitsPerPixel, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, 0);        
        SDL_SetColorKey (surface, SDL_SRCCOLORKEY, 0x00);
    }
}

void SDL_Item::draw () {
    // bør aldri bli kalla, gjer ingenting anna enn å sette opp 
    // surface slik at det ikkje blir feil når den blir lagt på
    // skjermen
    setup_surface ();
}

bool SDL_Item::is_active () {
    return active;
}

void SDL_Item::toggle_active () {
    if (active == true) {
        active = false;
    } else {
        active = true;
    }
}

void SDL_Item::set_active (bool on) {
    active = on;
}

void SDL_Item::set_color (Uint32 c) {
    color = c;
}

Uint32 SDL_Item::get_color () {
    return color;
}

/*
 * Misc sdl functions
 */

void draw_line (SDL_Surface *s, int x0, int y0, int x1, int y1, Uint32 pixel) {
    // Bruker Bresenham's algoritme
    // http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
    //
    // Distributed under the CC-ShareAlike licence:
    // http://creativecommons.org/licenses/by-sa/3.0/

    int Dx = x1 - x0; 
    int Dy = y1 - y0;
    int steep = (abs(Dy) >= abs(Dx));
    if (steep) {
       swap(x0, y0);
       swap(x1, y1);
       // recompute Dx, Dy after swap
       Dx = x1 - x0;
       Dy = y1 - y0;
    }
    int xstep = 1;
    if (Dx < 0) {
       xstep = -1;
       Dx = -Dx;
    }
    int ystep = 1;
    if (Dy < 0) {
       ystep = -1;		
       Dy = -Dy; 
    }
    int TwoDy = 2*Dy; 
    int TwoDyTwoDx = TwoDy - 2*Dx; // 2*Dy - 2*Dx
    int E = TwoDy - Dx; //2*Dy - Dx
    int y = y0;
    int xDraw, yDraw;	
    for (int x = x0; x != x1; x += xstep) {		
       if (steep) {			
           xDraw = y;
           yDraw = x;
       } else {			
           xDraw = x;
           yDraw = y;
       }
       // plot
       put_pixel32(s, xDraw, yDraw, pixel);
       // next
       if (E > 0) {
           E += TwoDyTwoDx; //E += 2*Dy - 2*Dx;
           y = y + ystep;
       } else {
           E += TwoDy; //E += 2*Dy;
       }
    }
}

void apply_surface (int x, int y, SDL_Surface *source, SDL_Surface *destination) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = destination->h - y - source->h;

    SDL_BlitSurface (source, NULL, destination, &offset);
}

void put_pixel32 (SDL_Surface *surface, int x, int y, Uint32 pixel) {
    Uint32 *pixels = (Uint32 *)surface->pixels;
    if (y > surface->h || x > surface->w) {
        cout << "ERROR: put_pixel outside surface\n";
        cout << "Pixel:   [" << x << ", " << y << "]\n";
        cout << "Surface: [" << surface->w << ", " << surface->h << "]\n";
        return;
    }
    if (y < 0 || x < 0) {
        cout << "ERROR: put_pixel outside surface\n";
        cout << "ERROR: coordinates must be positive\n";
        cout << "Pixel:   [" << x << ", " << y << "]\n";
        return;
    }
    pixels[((surface->h - y - 1) * surface->w) + x - 1] = pixel;
}

Uint32 get_pixel32 (SDL_Surface *surface, int x, int y) {
    Uint32 *pixels = (Uint32 *)surface->pixels;
    return pixels[((surface->h - y) * surface->w) + x];
}

