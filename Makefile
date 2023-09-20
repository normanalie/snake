CC=gcc
CFLAGS=-O2 -Wall `sdl-config --cflags`
LIBS=`sdl-config --libs` -lm -lSDL_ttf

main: clean dir build
	rm -f bin/$@
	$(CC) $(CFLAGS) build/graphics.o build/main.o build/snake.o -o bin/snake $(LIBS)

dir:
	mkdir -p build

build: build/graphics.o build/main.o build/models

build/models: build/snake.o

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o 

build/snake.o: src/models/snake.c src/models/snake.h
	$(CC) $(CFLAGS) -c src/models/snake.c -o build/snake.o

build/graphics.o: src/graphics/graphics.c src/graphics/graphics.h
	rm -f src/graphics/police.h
	touch src/graphics/police.h
	if test -e /usr/include/SDL_ttf.h;           then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/include/SDL/SDL_ttf.h;       then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/local/include/SDL_ttf.h;     then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/local/include/SDL/SDL_ttf.h; then echo "#define SDL_TTF_OK" > police.h; fi
	$(CC) $(CFLAGS) -c src/graphics/graphics.c -o build/graphics.o


clean:
	rm -rf build
