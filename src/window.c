#include <window.h>
#include <assert.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* Print SDL error */
#define pr_sdl_err(msg)		fprintf(stderr, msg ": %s\n", SDL_GetError())
#define pr_img_err(msg)		fprintf(stderr, msg ": %s\n", IMG_GetError())

/**
 * Show GUI window with image in it.
 *
 * @param wp Window parameters
 * @param c Window background color
 * @param image_path Path to the image to be shown in the window
 *
 * @return true on success or false on failure
 */
bool window_show_img(const struct window_params *wp, const struct color *c,
		const char *image_path)
{
	int res;
	bool ret = true;
	SDL_Window *wnd;
	SDL_Renderer *ren;
	SDL_Surface *img_sur;
	SDL_Texture *img_tex;

	assert(wp != NULL);
	assert(c != NULL);
	assert(image_path != NULL);

	res = SDL_Init(SDL_INIT_VIDEO);
	if (res != 0) {
		pr_sdl_err("Unable to initialize SDL");
		ret = false;
		goto exit_init;
	}

	res = IMG_Init(IMG_INIT_PNG);
	if ((res & IMG_INIT_PNG) != IMG_INIT_PNG) {
		pr_img_err("Failed to init required PNG support");
		ret = false;
		goto exit_init;
	}

	wnd = SDL_CreateWindow(wp->title, wp->x, wp->y, wp->w, wp->h,
			wp->flags);
	if (wnd == NULL) {
		pr_sdl_err("Could not create window");
		ret = false;
		goto exit_wnd;
	}

	ren = SDL_CreateRenderer(wnd, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL) {
		fprintf(stderr, "Unable to create accelerated renderer\n");
		fprintf(stderr, "Trying to fallback to software renderer...\n");
		ren = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_SOFTWARE);
		if (ren == NULL) {
			fprintf(stderr, "Unable to create software renderer\n");
			ret = false;
			goto exit_ren;
		}
	}

	img_sur = IMG_Load(image_path);
	if (img_sur == NULL) {
		pr_sdl_err("Unable to load BMP");
		ret = false;
		goto exit_img_sur;
	}

	img_tex = SDL_CreateTextureFromSurface(ren, img_sur);
	SDL_FreeSurface(img_sur);
	if (img_tex == NULL) {
		pr_sdl_err("Unable to create texture");
		ret = false;
		goto exit_img_tex;
	}

	/* Drawing the image texture on window */
	for (;;) {
		SDL_Event e;

		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				break;
		}

		SDL_SetRenderDrawColor(ren, c->r, c->g, c->b, c->a);
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
	IMG_Quit();
	SDL_Quit();
exit_init:
	return ret;
}
