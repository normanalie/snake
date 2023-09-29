CC=gcc
CFLAGS=-O2 -Wall `sdl-config --cflags`
LIBS=`sdl-config --libs` -lm -lSDL_ttf

main: clean dir build 
	rm -f bin/$@
	$(CC) $(CFLAGS) build/*.o -o bin/snake $(LIBS)

dir:
	mkdir -p build

build: build/graphics.o build/main.o build/models

build/models: build/snake.o build/view.o build/fruit.o build/physic.o

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o 

build/snake.o: src/snake.c src/snake.h
	$(CC) $(CFLAGS) -c src/snake.c -o build/snake.o

build/view.o: src/view.h src/view.c 
	$(CC) $(CFLAGS) -c src/view.c -o build/view.o

build/fruit.o: src/fruit.h src/fruit.c 
	$(CC) $(CFLAGS) -c src/fruit.c -o build/fruit.o

build/physic.o: src/physic.h src/physic.c 
	$(CC) $(CFLAGS) -c src/physic.c -o build/physic.o

POLICEH=lib/graphics/police.h
build/graphics.o: lib/graphics/graphics.c lib/graphics/graphics.h
	rm -f $(POLICEH)
	touch $(POLICEH)
	if test -e /usr/include/SDL_ttf.h;           then echo "#define SDL_TTF_OK" > $(POLICEH); fi
	if test -e /usr/include/SDL/SDL_ttf.h;       then echo "#define SDL_TTF_OK" > $(POLICEH); fi
	if test -e /usr/local/include/SDL_ttf.h;     then echo "#define SDL_TTF_OK" > $(POLICEH); fi
	if test -e /usr/local/include/SDL/SDL_ttf.h; then echo "#define SDL_TTF_OK" > $(POLICEH); fi
	$(CC) $(CFLAGS) -c lib/graphics/graphics.c -o build/graphics.o


clean:
	rm -rf build
