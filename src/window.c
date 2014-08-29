#include <window.h>
#include <stdio.h>
#include <SDL2/SDL.h>

/* Print SDL error */
#define pr_sdl_err(msg) fprintf(stderr, msg ": %s\n", SDL_GetError())

/* Shows GUI window with image in it.
 *
 * wp: pointer to window params structure
 * image_path: path to image to show in window
 *
 * Returns 0 on success or error code on failure.
 */
int window_show_img(const struct window_params *wp, const char *image_path)
{
	int ret = 0;
	SDL_Window *wnd;
	SDL_Renderer *ren;
	SDL_Surface *img_sur;
	SDL_Texture *img_tex;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		pr_sdl_err("Unable to initialize SDL");
		ret = 1;
		goto exit_init;
	}

	wnd = SDL_CreateWindow(wp->title, wp->x, wp->y, wp->w, wp->h,
			wp->flags);
	if (wnd == NULL) {
		pr_sdl_err("Could not create window");
		ret = 2;
		goto exit_wnd;
	}

	ren = SDL_CreateRenderer(wnd, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL) {
		pr_sdl_err("Unable to create renderer");
		ret = 3;
		goto exit_ren;
	}

	img_sur = SDL_LoadBMP(image_path);
	if (img_sur == NULL) {
		pr_sdl_err("Unable to load BMP");
		ret = 4;
		goto exit_img_sur;
	}

	img_tex = SDL_CreateTextureFromSurface(ren, img_sur);
	SDL_FreeSurface(img_sur);
	if (img_tex == NULL) {
		pr_sdl_err("Unable to create texture");
		ret = 5;
		goto exit_img_tex;
	}

	/* Drawing the image texture on window */
	for (;;) {
		SDL_Event e;

		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				break;
		}

		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, img_tex, NULL, NULL);
		SDL_RenderPresent(ren);
	}

	/* Freeing of all allocated memory */
	SDL_DestroyTexture(img_tex);
exit_img_tex:
exit_img_sur:
	SDL_DestroyRenderer(ren);
exit_ren:
	SDL_DestroyWindow(wnd);
exit_wnd:
	SDL_Quit();
exit_init:
	return ret;
}
