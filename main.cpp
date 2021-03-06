// Copyright (c) 2009 Gaute Hope <eg@gaute.vetsj.com>
// main.cpp

#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "SDL_ttf.lib")
#endif

# include <iostream>
# include <SDL.h>
# include <SDL_ttf.h>
# include <string>
# include <ctime>

# include "graf.h"

using namespace std;

# define VERSION "2 - 0.2 (beta)"

void myexit () {
#ifdef WIN32
    system ("pause");
#endif
}

int main (int argc, char *argv[]) {
    atexit (myexit);

    cout << "Graf " << VERSION << endl;
    cout << "Copyright (c) 2009 Gaute Hope <gaute.hope@stud.hib.no>" << endl;

    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 640;
    const int SCREEN_BPP = 32;

    srand (static_cast<int>(time(0)));

    const char *filename = "GRAF.DAT";

    if (SDL_Init (SDL_INIT_EVERYTHING) == -1) {
        cout << "Failed to setup SDL!\n";
        exit (1);
    }
    atexit (SDL_Quit);

    if (TTF_Init () == -1) {
        cout << "Failed to setup SDL_ttf!\n";
        exit (1);
    }
    atexit (TTF_Quit);

    SDL_Surface *screen = NULL;
    screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (screen == NULL) {
        cout << "Failed to setup SDL window!\n";
        exit (1);
    }

    string title = "Graf " VERSION ": ";
    title = title + filename;

    SDL_WM_SetCaption (title.data (), NULL);

    // init and setup graf, this runs the main loop
    Graf g (screen, filename, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
    g.run ();

    exit (0);
    return 0;
}

