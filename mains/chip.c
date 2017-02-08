#include <SDL2/SDL.H>

#include "../lib/options.h"
#include "../lib/packet.h"

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
