#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  /* Initialize the SDL library */
  if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) < 0) {
    fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());

    return EXIT_FAILURE; // Return with appropriate return values.
  }

  /* Register SDL_Quit to be called upon exit */
  atexit(SDL_Quit);

  /* Create a window instance */
  int windowWidth = 640, windowHeight = 480;
  SDL_Window *window =
      SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    fprintf(stderr, "Could not create a window: %s\n", SDL_GetError());

    return EXIT_FAILURE;
  }

  /* Initialize a renderer */
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == NULL) {
    fprintf(stderr, "Could not initialize a renderer: %s\n", SDL_GetError());

    return EXIT_FAILURE;
  }

  /* Draw graphics on the window */
  SDL_Rect rectangle = {.w = 40, .h = 40};
  SDL_Color skyBlue = {0x87, 0xCE, 0xEB, 0xFF};
  SDL_Color red = {0xF2, 0x42, 0x42, 0xFF};

  /* Create an animation loop */
  bool isRunning = true;
  int morphCooldownCount = 0;

  while (isRunning) {
    SDL_Event event;

    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
      isRunning = false;
    }

    if (morphCooldownCount == 48) {
      if (rectangle.w == rectangle.h) {
        rectangle.w = 80;
        rectangle.h = 20;
      } else {
        rectangle.w = rectangle.h = 40;
      }

      rectangle.x = (windowWidth - rectangle.w) / 2;
      rectangle.y = (windowHeight - rectangle.h) / 2;
      morphCooldownCount = 0;

      SDL_SetRenderDrawColor(renderer, skyBlue.r, skyBlue.g, skyBlue.b,
                             skyBlue.a);
      SDL_RenderClear(renderer);
      SDL_SetRenderDrawColor(renderer, red.r, red.g, red.b, red.a);
      SDL_RenderFillRect(renderer, &rectangle);
      SDL_RenderPresent(renderer);
    }

    ++morphCooldownCount;

    SDL_Delay(1000 / 120); // Render in 120 fps.
  }

  /* Clean up resources */
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  return EXIT_SUCCESS;
}