#include <stdio.h>
#include <stdlib.h>

#include "options.h"

Options parse_args(int argc, char **argv)
{
    Options o = { .title = "chip", .width = 320, .height = 240 };

    for (int arg = 1; arg < argc; ++arg) {
        char *c = argv[arg];

        if(*c == '-') {
            ++c;
            switch(*c) {
            case 't': o.title = argv[++arg]; break;
            case 'w': o.width = atoi(argv[++arg]); break;
            case 'h': o.height = atoi(argv[++arg]); break;
            }
        }
    }

    return o;
}
