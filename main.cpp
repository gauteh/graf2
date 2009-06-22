// Copyright (c) 2009 Gaute Hope <eg@gaute.vetsj.com>
// main.cpp: Styrer 

# include <iostream>
# include <SDL/SDL.h>
# include <SDL/SDL_ttf.h>
# include <string>
# include <ctime>

# include "graf.h"

using namespace std;

# ifndef BUILDTIME
    # define BUILDTIME "unknown"
# endif
# define VERSION "2-build-" BUILDTIME 

int main () {
    cout << "Graf " << VERSION << endl;
    cout << "Copyright (c) 2009 Gaute Hope <gaute.hope@stud.hib.no>" << endl;

    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 640;
    const int SCREEN_BPP = 32;

    srand (static_cast<int>(time(0)));

    const char *filename = "GRAF.DAT";

    if (SDL_Init (SDL_INIT_EVERYTHING) == -1) {
        cout << "Failed to setup SDL!\n";
        return 0;
    }

    if (TTF_Init () == -1) {
        cout << "Failed to setup SDL_ttf!\n";
        return 0;
    }

    SDL_Surface *screen = NULL;
    screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (screen == NULL) {
        cout << "Failed to setup SDL!\n";
        return 0;
    }

    string title = "Graf " VERSION ": ";
    title = title + filename;

    SDL_WM_SetCaption (title.data (), NULL);

        
    Graf g (screen, filename, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP); // init and setup graf, this runs the main application

    TTF_Quit ();
    SDL_Quit ();
    return 0;
}
