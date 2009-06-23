/*
 * Copyright (c) 2009 Gaute Hope <eg@gaute.vetsj.com>
 *
 * sdlmisc.h: Misc SDL helper functions
 *            SDL_Item class for common members and functions of sdl objects
 */

# pragma once

# include <SDL.h>

using namespace std;

# define WHITE 0xFFFFFF
# define BLACK 0x0

# define LILA 0x7C48E8
# define GREEN 0x197900

# define AXIS WHITE
# define PLOT_A LILA
# define PLOT_B GREEN

void apply_surface (int, int, SDL_Surface *, SDL_Surface *);
void draw_line (SDL_Surface *, int, int, int, int, Uint32);
Uint32 get_pixel32 (SDL_Surface *, int, int);
void put_pixel32 (SDL_Surface *, int, int, Uint32);

class SDL_Item {
    protected:
        SDL_Surface *surface;
        SDL_Surface *screen;
        SDL_Rect rect;

        Uint32 color;
        bool active;

    public:
        SDL_Item ();
        virtual void draw ();
        void setup_surface ();
        SDL_Surface *get_surface ();
        SDL_Rect *get_rect ();
        void set_rect (SDL_Rect *);
        void set_screen (SDL_Surface *);

        bool is_active ();
        void toggle_active ();
        void set_active (bool);

        void set_color (Uint32);
        Uint32 get_color ();
};

