#include <SDL2/SDL.H>

typedef struct {
    char *title;
    int width;
    int height;
} Options;

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

typedef struct {
    char type[8];
    int length;
    char *data;
} Packet;


Packet getPacket(void)
{
    Packet p;

#define GETC(out)                               \
    do {                                        \
        int c;                                  \
        if((c = getchar()) == EOF)              \
            return (Packet){"Quit"};            \
        else                                    \
            out = c;                            \
    } while(0)

#define GET32(out)                     \
          do {                         \
              char c;                  \
              GETC(c); out = c << 24;  \
              GETC(c); out |= c << 16; \
              GETC(c); out |= c << 8;  \
              GETC(c); out |= c;       \
          } while(0)

    GETC(p.type[0]);
    GETC(p.type[1]);
    GETC(p.type[2]);
    GETC(p.type[3]);
    GETC(p.type[4]);
    GETC(p.type[5]);
    GETC(p.type[6]);
    GETC(p.type[7]);

    GET32(p.length);

    p.data = malloc(p.length);
    for(int i=0; i<p.length; ++i)
        GETC(p.data[i]);

#undef GET32
#undef GETC

    return p;
}

int main(int argc, char **argv)
{
    Options opt = parse_args(argc, argv);

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *win = SDL_CreateWindow(
        opt.title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        opt.width, opt.height,
        SDL_WINDOW_ALLOW_HIGHDPI );

    SDL_Renderer *ren = SDL_CreateRenderer(
        win, -1, SDL_RENDERER_PRESENTVSYNC );

    int loop = 1;
    SDL_Event e;
    Packet p = {"NULL", 0, NULL};
    while (loop) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT)
                loop = 0;
        }

        while (strcmp(p.type, "Render")) {
            p = getPacket();
        }

        SDL_RenderClear(ren);
        SDL_RenderPresent(ren);
    }

    SDL_Quit();
    return 0;
}
