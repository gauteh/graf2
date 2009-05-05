env = Environment ()

dependencies = {
	'sdl' : 'pkg-config'
	}

for k, v in dependencies.iteritems():
	if v == 'pkg-config':
		env.ParseConfig ('pkg-config --cflags --libs ' + k)
		
env.Append (LIBS = 'SDL_ttf')
env.Append (CXXFLAGS = '-g')

source_files = [
	'main.cpp',
    'graf.cpp',
    'sdlmisc.cpp',
    'plot.cpp',
	]

env.Program (target = 'graf', source = source_files)

