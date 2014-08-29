#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <window.h>

static const struct window_params wp = {
	.title	= "Long Live Rock 'n' Roll!",
	.flags	= SDL_WINDOW_SHOWN,
	.x	= SDL_WINDOWPOS_UNDEFINED,
	.y	= SDL_WINDOWPOS_UNDEFINED,
	.w	= 640,
	.h	= 480,
};

/* Purple color (Deep Purple rocks!) */
static const struct color color = {
	.r = 127,
	.g = 0,
	.b = 127,
	.a = 255,
};

static const char *image_path = "share/rock-tux.png";

int main(int argc, char *argv[])
{
	int res;

	/* Unused for now */
	(void)argc;
	(void)argv;

	res = window_show_img(&wp, &color, image_path);
	if (res != 0) {
		fprintf(stderr, " ** Error: fail to run SDL2 window; "
				"error code: %d\n", res);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
