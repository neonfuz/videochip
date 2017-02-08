#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "packet.h"

Packet getPacket(Packet *p)
{
    free(p->data);

    int i, c;
    for (i = 0; i < 8 && c != EOF; ++i) {
        c = getchar();
        p->type[i] = c;
    }

    p->length = 0;
    for (i = 0; i < 4 && c != EOF; ++i) {
        c = getchar();
        p->length |= c << (i*8);
    }

    if (c == EOF)
        return (Packet){"Quit"};

    p->data = malloc(p->length);
    for(int i=0; i < p->length; ++i)
        p->data[i] = getchar();

    return *p;
}

void printPacket(Packet p)
{
    fputs(p.type, stdout);
    for(int i = strlen(p.type); i<8; ++i)
        putchar('\0');

    putchar(p.length);
    putchar(p.length >> 8);
    putchar(p.length >> 16);
    putchar(p.length >> 24);

    for(int i=0; i<p.length; ++i)
        putchar(p.data[i]);
}
