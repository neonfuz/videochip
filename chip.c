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
