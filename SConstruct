env = Environment ()

env.ParseConfig ('pkg-config --cflags --libs sdl')
		
env.Append (LIBS = 'SDL_ttf')
env.Append (CXXFLAGS = '-g')

source_files = [
	'main.cpp',
    'graf.cpp',
    'sdl.cpp',
    'plot.cpp',
    'axis.cpp',
    'text.cpp',
	]

env.Program (target = 'graf', source = source_files)

