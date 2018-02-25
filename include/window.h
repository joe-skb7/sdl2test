#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>
#include <stdint.h>

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

bool window_show_img(const struct window_params *wp, const struct color *c,
		const char *image_path);

#endif /* WINDOW_H */
