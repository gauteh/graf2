import os

env = Environment ()

env.Append (CXXFLAGS = "-D" + os.uname()[0])
print "Building for: " + os.uname ()[0]

env.ParseConfig ('pkg-config --cflags --libs sdl')

env.Append (LIBS = 'SDL_ttf')
env.Append (CXXFLAGS = '-g') # debug

from time import strftime
env.Append (CXXFLAGS = "-DBUILDTIME=\\\"" + strftime ("%Y%m%d") + "\\\"")

source_files = [
    'main.cpp',
    'graf.cpp',
    'sdlmisc.cpp',
    'plot.cpp',
    'axis.cpp',
    'text.cpp',
    ]

env.Program (target = 'graf', source = source_files)

env.Program (target = 'prepare', source = 'prepare_data.cpp')

