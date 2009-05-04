/*
 * main.cpp: Styrer 
 */

# include <iostream>
# include <SDL/SDL.h>
# include <string>

# include "graf.h"

using namespace std;

# define VERSION "0.1"

int main () {
    
    cout << "Graf v" << VERSION << endl;
    cout << "Copyright (c) 2009 Gaute Hope <eg@gaute.vetsj.com> <gaute.hope@stud.hib.no>" << endl;

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 640;
    const int SCREEN_BPP = 32;

    if (SDL_Init (SDL_INIT_EVERYTHING) == -1) {
        cout << "Failed to setup SDL!\n";
        return 0;
    }

    SDL_Surface *screen = NULL;
    screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if (screen == NULL) {
        cout << "Failed to setup SDL!\n";
        return 0;
    }

    SDL_WM_SetCaption ("Graf - v" VERSION " - 2009 (c) Gaute Hope", NULL);

        
    SDL_Quit ();
    return 0;
}
