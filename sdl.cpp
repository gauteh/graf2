/*
 * sdlmisc.cpp:
 * Misc SDL helper functions
 *
 * SDL_Item class, common members and functions of SDL objects
 */

# include <iostream>
# include <SDL/SDL.h>

# include "sdl.h"

using namespace std;


/*
 * class SDL_Item:
 */
SDL_Item::SDL_Item () {
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

bool SDL_Item::toggle_active () {
    if (active == true) {
        active = false;
    } else {
        active = true;
    }
}

bool SDL_Item::set_active (bool on) {
    active = on;
}

/*
 * Misc sdl functions
 */

void draw_line (SDL_Surface *s, int x1, int y1, int x2, int y2, Uint32 pixel) {
    // alle punkt på ei linje følger likninga y = ax + b
    cout << "Draw line: [" << x1 << "," << y1 << "] -> ";
    cout << "[" << x2 << "," << y2 << "]" << endl;

    y1 = s->h - y1;
    y2 = s->h - y2;

    if ((x2 - x1) == 0) {
        // vertical
        //cout << "v" << endl;
        for (int i = 0; i < s->w; i++) {
            for (int j = 0; j < s->h; j++) {
                if (i == x2) {
                    if ((j > y1) && ( j < y2)) 
                        put_pixel32 (s, i, j, pixel);
                    if ((j < y1) && (j > y2)) 
                        put_pixel32 (s, i, j, pixel);
                }
            }
        }
    } else if ((y2 - y1) == 0) {
        // horizontal
        //cout << "h" << endl;
        for (int i = 0; i < s->w; i++) {
            for (int j = 0; j < s->h; j++) {
                if (j == y2) {
                    if ((j > x2) && (j < x1))
                        put_pixel32 (s, i, j, pixel);
                    if ((j < x2) && (j > x1))
                        put_pixel32 (s, i, j, pixel);
                }
            }
        }
    } else {
        cout << "draw custom line..\n";
        int a, b;
        a = (y2 - y1)/(x2 - x1);
        b = y1;
       
        if (x2 < x1) {
            int t = x1;
            x1 = x2;
            x2 = x1;
        }
        for (int x = x1; x <= x1; x++) {
            int y = a*x + y1;
            put_pixel32 (s, x, y, pixel);
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
    pixels[((surface->h - y) * surface->w) + x] = pixel;
}

Uint32 get_pixel32 (SDL_Surface *surface, int x, int y) {
    Uint32 *pixels = (Uint32 *)surface->pixels;
    return pixels[((surface->h - y) * surface->w) + x];
}

