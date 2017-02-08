MAINS:=$(wildcard mains/*.c)
EXECUTABLES:=$(addprefix bin/,$(notdir $(basename $(MAINS))))
LIBS:=$(wildcard lib/*.c)
LIB_OBJS:=$(LIBS:.c=.o)

all: $(EXECUTABLES)

test: all
	./bin/testprog | ./bin/chip

bin/%: mains/%.c $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ `sdl2-config --cflags --libs`

lib/%.o: lib/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXECUTABLES) $(LIB_OBJS)

.PHONY: all test clean
