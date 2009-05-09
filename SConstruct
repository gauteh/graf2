env = Environment ()

env.ParseConfig ('pkg-config --cflags --libs sdl')
		
#env.Append (LIBS = 'SDL_ttf')
env.Append (CXXFLAGS = '-g')

source_files = [
	'main.cpp',
    'graf.cpp',
    'sdlmisc.cpp',
    'plot.cpp',
	]

env.Program (target = 'graf', source = source_files)

