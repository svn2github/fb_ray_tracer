
#include <iostream>
#include <Windows.h>
#include <SDL.h>
#include "vector3D.hpp"
#include "surface.hpp"
#include "surface_sphere.hpp"
#include "surface_plane.hpp"
#include "view_plane.hpp"
#include "world.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "camera_orthographic.hpp"
#include "camera_pinhole.hpp"
#include "simpson.hpp"

using namespace ray_tracer;

const int width = 500, height = 500;

void test1(SDL_Surface *screen) {
	world world;
	camera *cam;
	view_plane *plane;
	surface_sphere *s1;
	surface_plane_bw *s2;
	light *l;
	char buf[16];
	
	cam = new camera_orthographic(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 1, 0));
	plane = new view_plane(-20, 20, 20, -20);

	s1 = new surface_sphere(point3D(20, -20, 0), 10);
	s1->shininess = 5;
	s1->diffuse = colorRGB(0.2, 0.6, 0.8);
	s1->specular = colorRGB(0.7, 0.7, 0.7);
	s1->ambient = colorRGB(0.3, 0.3, 0.3);

	s2 = new surface_plane_bw(point3D(100, 0, 0), vector3D(-1, 0, 0));
	s2->shininess = 3;
	s2->diffuse = colorRGB(0.8, 0.6, 0.2);
	s2->specular = color_black; // colorRGB(0.7, 0.7, 0.7);
	s2->ambient = colorRGB(0.1, 0.1, 0.1);

	l = new light(point3D(0, 0, 30), color_white);
	
	world.set_ambient(color_blue);
	world.set_camera(cam);
	world.set_view_plane(image);
	world.add_surface(s1);
	// world.add_surface(s2);
	world.add_light(l);
	world.fit_window(width, height, screen->pixels);

	double y = -20, step = 0.3;
	int fps = 0;
	DWORD old_time = GetTickCount();

	while (true) {
		if (SDL_MUSTLOCK(screen)) {
			if (SDL_LockSurface(screen) < 0) {
				printf("Couldn't lock the screen: %s.\n", SDL_GetError());
				return;
			}
		}

		y += step;
		if (y < -20 || y > 20) step = -step;
		
		point3D center = s1->get_center();
		center.y = y;
		s1->set_center(center);

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
}

void test2(SDL_Surface *screen) {
	world world;
	camera_pinhole *cam;
	view_plane *image;
	surface_sphere *s1, *s2;
	light *l;
	
	cam = new camera_pinhole(point3D(0, 0, 0), point3D(3, 0, 0), vector3D(0, 1, 0));
	image = new view_plane(-20, 20, 20, -20);

	s1 = new surface_sphere(point3D(15, -9, 0), 10);
	s1->shininess = 5;
	s1->diffuse = colorRGB(0.2, 0.6, 0.8);
	s1->specular = colorRGB(0.7, 0.7, 0.7);
	s1->ambient = colorRGB(0.2, 0.2, 0.2);

	s2 = new surface_sphere(point3D(20, 5, 0), 10);
	s2->shininess = 6;
	s2->diffuse = colorRGB(0.8, 0.2, 0.8);
	s2->specular = colorRGB(0.7, 0.7, 0.7);
	s2->ambient = colorRGB(0.2, 0.2, 0.2);

	l = new light(point3D(0, 0, 30), color_white);
	
	world.set_camera(cam);
	world.set_view_plane(image);
	world.add_surface(s1);
	world.add_surface(s2);
	world.add_light(l);
	world.fit_window(width, height, screen->pixels);

	if (SDL_MUSTLOCK(screen)) {
		if (SDL_LockSurface(screen) < 0) {
			printf("Couldn't lock the screen: %s.\n", SDL_GetError());
			return;
		}
	}
	cam->zoom(6);
	world.render_scene();
	if (SDL_MUSTLOCK(screen)) {
		SDL_UnlockSurface(screen);
	}
	SDL_UpdateRect(screen, 0, 0, width, height);

	while(1);
}

class fun {
public:
	double operator()(double x) const {
		return sin(x);
	}
};

void test3() {
	simpson<fun> s;
	fun f;
	double a = s.integration(0, acos(-1.0), f, 1e-15);
	std::cout << a << std::endl;
}

int main() {
	test3();

	if (SDL_Init(SDL_INIT_VIDEO) == -1) { 
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		return 0;
	}

	SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
	if (screen == NULL) {
		printf("Couldn't set destination video mode: %s.\n", SDL_GetError());
		return 0;
	}

	test1(screen);

	SDL_Quit();
	return 0;
}
