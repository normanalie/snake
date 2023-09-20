CC=gcc
CFLAGS=-O2 -Wall `sdl-config --cflags`
LIBS=`sdl-config --libs` -lm -lSDL_ttf

%: dir build/graphics.o src/%.c
	rm -f $@
	$(CC) $(CFLAGS) build/graphics.o src/$@.c -o bin/$@ $(LIBS)

dir:
	mkdir -p build

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
