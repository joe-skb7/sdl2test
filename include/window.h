#ifndef WINDOW_H
#define WINDOW_H

#include <stdint.h>

struct window_params {
	const char *title;	/* window title */
	uint32_t flags;		/* window flags (see SDL_WindowFlags) */
	int x;			/* horizontal position (from left), px */
	int y;			/* vertical position (from top), px */
	int w;			/* width, px */
	int h;			/* height, px */
};

int window_show_img(const struct window_params *wp, const char *image_path);

#endif /* WINDOW_H */
