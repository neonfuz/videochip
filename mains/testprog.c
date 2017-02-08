#include <stdio.h>

#include "../lib/packet.h"

static const Packet p_render = {"Render", 0, NULL};
static const Packet p_quit = {"Quit", 0, NULL};

int main(int argc, char **argv)
{
    Packet p_color = {
        .type = "Color",
        .length = 4,
        .data = (char[]){0, 0, 0, 0xff}
    };

    FILE *urandom = fopen("/dev/urandom", "rb");
    if(urandom == NULL) {
        fprintf(stderr, "Error opening /dev/urandom");
        return -1;
    }

    int color_idx = 0;
    char target = 0;
    while(1) {
        if(target < p_color.data[color_idx])
            --p_color.data[color_idx];
        else if(target > p_color.data[color_idx])
            ++p_color.data[color_idx];
        else {
            color_idx = fgetc(urandom) % 3;
            target = fgetc(urandom);
        }

        printPacket(p_color);
        printPacket(p_render);
    }

    return 0;
}
