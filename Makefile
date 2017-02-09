MAINS:=$(wildcard mains/*.c)
EXECUTABLES:=$(addprefix bin/,$(notdir $(basename $(MAINS))))
LIBS:=$(wildcard lib/*.c)
LIB_OBJS:=$(LIBS:.c=.o)

all: $(EXECUTABLES)

test: all
	./bin/testprog | ./bin/chip

bin/%: mains/%.c $(LIB_OBJS)
	mkdir -p bin/
	$(CC) $(CFLAGS) -o $@ $^ `sdl2-config --cflags --libs` -l SDL2_image

lib/%.o: lib/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXECUTABLES) $(LIB_OBJS)

.PHONY: all test clean
