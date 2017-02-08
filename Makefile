EXECUTABLES=chip testprog

all: $(EXECUTABLES)

test: chip testprog
	./testprog | ./chip

chip: chip.c
	$(CC) $(CFLAGS) -o chip chip.c `sdl2-config --cflags --libs`

testprog: testprog.c
	$(CC) $(CFLAGS) -o testprog testprog.c

clean:
	rm $(EXECUTABLES)

.PHONY: all test chip testprog clean
