CC=gcc
CFLAGS=-O2 -Wall `sdl-config --cflags`
LIBS=`sdl-config --libs` -lm -lSDL_ttf

main: clean dir build 
	rm -f bin/$@
	$(CC) $(CFLAGS) build/*.o -o bin/snake $(LIBS)

dir:
	mkdir -p build

build: build/graphics.o build/main.o build/models

build/models: build/snake.o build/view.o

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o 

build/snake.o: src/models/snake.c src/models/snake.h
	$(CC) $(CFLAGS) -c src/models/snake.c -o build/snake.o

build/view.o: src/view.h src/view.c 
	$(CC) $(CFLAGS) -c src/view.c -o build/view.o

POLICEH=src/graphics/police.h
build/graphics.o: src/graphics/graphics.c src/graphics/graphics.h
	rm -f $(POLICEH)
	touch $(POLICEH)
	if test -e /usr/include/SDL_ttf.h;           then echo "#define SDL_TTF_OK" > $(POLICEH); fi
	if test -e /usr/include/SDL/SDL_ttf.h;       then echo "#define SDL_TTF_OK" > $(POLICEH); fi
	if test -e /usr/local/include/SDL_ttf.h;     then echo "#define SDL_TTF_OK" > $(POLICEH); fi
	if test -e /usr/local/include/SDL/SDL_ttf.h; then echo "#define SDL_TTF_OK" > $(POLICEH); fi
	$(CC) $(CFLAGS) -c src/graphics/graphics.c -o build/graphics.o


clean:
	rm -rf build
