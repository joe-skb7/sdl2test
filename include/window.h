#ifndef WINDOW_H
#define WINDOW_H

#include <stdint.h>

/* Error codes for window_show_img() function */
#define EWSI_SDL_INIT		1	/* SDL_Init() */
#define EWSI_IMG_INIT		2	/* IMG_Init() */
#define EWSI_SDL_CW		3	/* SDL_CreateWindow() */
#define EWSI_SDL_CR		4	/* SDL_CreateRenderer() */
#define EWSI_IMG_LOAD		5	/* IMG_Load() */
#define EWSI_SDL_CTFS		6	/* SDL_CreateTextureFromSurface() */

struct window_params {
	const char *title;	/* window title */
	uint32_t flags;		/* window flags (see SDL_WindowFlags) */
	int x;			/* horizontal position (from left), px */
	int y;			/* vertical position (from top), px */
	int w;			/* width, px */
	int h;			/* height, px */
};

struct color {
	uint8_t r;		/* red component */
	uint8_t g;		/* green component */
	uint8_t b;		/* blue component */
	uint8_t a;		/* alpha (transparent) component */
};

int window_show_img(const struct window_params *wp, const struct color *c,
		const char *image_path);

#endif /* WINDOW_H */
