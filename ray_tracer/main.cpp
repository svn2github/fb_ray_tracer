
#include <iostream>
#include <Windows.h>
#include <SDL.h>
#include "vector3D.hpp"
#include "surface.hpp"
#include "raster_image.hpp"
#include "world.hpp"
#include "light.hpp"
#include "camera.hpp"

using namespace ray_tracer;

const int width = 300, height = 300;

int main() {
	world world;
	camera *cam;
	raster_image *image;
	surface_sphere *s;
	// surface_plane *s;
	light *l;
	char buf[16];

	if (SDL_Init(SDL_INIT_VIDEO) == -1) { 
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		return -1;
	}

	SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
	if (screen == NULL) {
		printf("Couldn't set destination video mode: %s.\n", SDL_GetError());
		return -1;
	}

	cam = new camera(point3D(0, 0, 0), vector3D(-1, 0, 0), vector3D(0, 1, 0));
	image = new raster_image(-20, 20, 20, -20);
	image->fit(width, height, screen->pixels);
	s = new surface_sphere(point3D(20, -20, 0), 10);
	// s = new surface_plane(point3D(91, 19, 12), vector3D(-1, 0, 2));
	s->shininess = 5;
	l = new light(point3D(0, 0, 30), colorRGB(0.2, 0.6, 0.8), colorRGB(0.7, 0.7, 0.7), colorRGB(0.2, 0.2, 0.2));

	world.set_camera(cam);
	world.set_raster_image(image);
	world.add_surface(s);
	world.add_light(l);

	double y = -20, step = 0.3;
	int fps = 0;
	DWORD old_time = GetTickCount();

	while (true) {
		if (SDL_MUSTLOCK(screen)) {
			if (SDL_LockSurface(screen) < 0) {
				printf("Couldn't lock the screen: %s.\n", SDL_GetError());
				return -1;
			}
		}

		y += step;
		if (y < -20 || y > 20) step = -step;
		s->center.y = y;

		if (GetTickCount() - old_time > 1000) {
			old_time = GetTickCount();

			strcpy(buf, "fps: ");
			itoa(fps, buf + 5, 10);

			SDL_WM_SetCaption(buf, NULL);
			fps = 0;
		} else {
			++fps;
		}
		world.render_scene();

		if (SDL_MUSTLOCK(screen)) {
			SDL_UnlockSurface(screen);
		}
		SDL_UpdateRect(screen, 0, 0, width, height);
	}

	SDL_Quit();
	return 0;
}
