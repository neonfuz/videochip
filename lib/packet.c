#include <stdio.h>
#include <stdlib.h>

#include "packet.h"

Packet getPacket(void)
{
    Packet p;

    int i, c;
    for (i = 0, c = getchar(); i < 8 && c != EOF; ++i, c = getchar())
        p.type[i] = c;

    p.length = 0;
    for (i = 3, c = getchar(); i >= 0 && c != EOF; --i, c = getchar())
        p.length |= c << (i*8);

    if (c == EOF)
        return (Packet){"Quit"};

    p.data = malloc(p.length);
    for(int i=0; i < p.length; ++i)
        p.data[i] = getchar();

    return p;
}
