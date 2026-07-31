CC=gcc
CFLAGS=-O2 -Wall
LIBS=-lfreeglut -lopengl32 -lglu32 -lm
all:
	@mkdir -p build
	$(CC) $(CFLAGS) src/main.c -o build/PixelCity $(LIBS)
run: all
	./build/PixelCity
clean:
	rm -rf build
