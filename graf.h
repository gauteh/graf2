/*
 * graf.h: Klassa for oppsett og bakgrunn av graf
 */

# pragma once

class Axis {
    private:
        SDL_Surface surface;
        SDL_Rect rect;

        float start;
        float stop;
        float increment;

    public:
        Axis (float, float, float);
        void set_start (float);
        void set_stop (float);
        void set_inc (float);

        void draw ();
        SDL_Surface *get_surface ();
        SDL_Rect *get_rect ();
        void set_rect (SDL_Rect *);
};

class Graf {
    private:
        SDL_Surface surface;
        SDL_Rect rect;

        Axis x_axis;
        Axis y_axis;

    public:
        Graf ();
        
        void draw ();
        SDL_Surface *get_surface ();
        SDL_Rect *get_rect ();
};

