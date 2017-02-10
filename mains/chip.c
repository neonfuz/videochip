#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../lib/options.h"
#include "../lib/packet.h"

// Quit the program with an error message if err is zero
void sdl_assert(int err)
{
    if(err)
        return;

    fputs(SDL_GetError(), stderr);
    exit(-1);
}

int main(int argc, char **argv)
{
    Options opt = parse_args(argc, argv);

    sdl_assert( SDL_Init(SDL_INIT_EVERYTHING) == 0 );
    sdl_assert( IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG );

    SDL_Window *win = SDL_CreateWindow(
        opt.title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        opt.width, opt.height,
        SDL_WINDOW_ALLOW_HIGHDPI );
    sdl_assert(win != NULL);

    SDL_Renderer *ren = SDL_CreateRenderer(
        win, -1, SDL_RENDERER_PRESENTVSYNC );
    sdl_assert(ren != NULL);

    int loop = 1;
    SDL_Event e;
    Packet p = {"NULL", 0, NULL};
    SDL_Rect rect = { 0 };
    while (loop) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT)
                loop = 0;
        }

        do {
            getPacket(&p);

            if (!strcmp(p.type, "Quit"))
                loop = 0;

            else if (!strcmp(p.type, "Color"))
                SDL_SetRenderDrawColor(
                    ren, p.data[0], p.data[1], p.data[2], p.data[3]);

            else if (!strcmp(p.type, "Rect")) {
                rect.x = p.data[0] << 8 | p.data[1];
                rect.y = p.data[2] << 8 | p.data[3];
                rect.w = p.data[4] << 8 | p.data[5];
                rect.h = p.data[6] << 8 | p.data[7];
            }

        } while (strcmp(p.type, "Render"));

        SDL_RenderClear(ren);
        Uint8 r, g, b, a;
        SDL_GetRenderDrawColor(ren, &r, &g, &b, &a);
        SDL_SetRenderDrawColor(ren, ~r, ~g, ~b, ~a);
        SDL_RenderFillRect(ren, &rect);
        SDL_SetRenderDrawColor(ren, r, g, b, a);
        SDL_RenderPresent(ren);
    }

    IMG_Quit();
    SDL_Quit();
    return 0;
}
