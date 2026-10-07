#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 320
#define HEIGHT 200

uint32_t framebuffer[WIDTH * HEIGHT];

void put_pixel(int x, int y, uint32_t color);

int main()
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);

	if((window = SDL_CreateWindow("SDL Framebuffer", WIDTH * 4, HEIGHT * 4, 0)) == NULL) {
        fprintf(stderr, "SDL_CreateWindow failed %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
	if((renderer = SDL_CreateRenderer(window, NULL)) == NULL) {
        fprintf(stderr, "SDL_CreateRenderer failed %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_XRGB8888,
								SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

	uint8_t is_running = 1;
	while (is_running) {
		/* Poll the events */
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				is_running = 0;
			}
		}

        put_pixel();

        SDL_UpdateTexture(texture, NULL, framebuffer, WIDTH * sizeof(uint32_t));

		/* Display the window and the renderer */
		SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}

/* put_pixel - paint a pixel at the given x any y position */
void put_pixel(int x, int y, uint32_t color)
{
   framebuffer[(WIDTH*y) + x] = color; 
}
