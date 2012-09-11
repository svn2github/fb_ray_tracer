
#include <iostream>
#include <Windows.h>
#include <SDL.h>
#include "vector3D.hpp"
#include "material.hpp"
#include "material_blinn_phong.hpp"
#include "surface.hpp"
#include "surface_sphere.hpp"
#include "surface_plane.hpp"
#include "surface_triangle.hpp"
#include "texture.hpp"
#include "texture_checker.hpp"
#include "texture_solid_color.hpp"
#include "view_plane.hpp"
#include "world.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "camera_orthographic.hpp"
#include "camera_pinhole.hpp"
#include "camera_thinlens.hpp"
#include "camera_fisheye.hpp"
#include "simpson.hpp"
#include "sampler.hpp"
#include "sampler_random.hpp"
#include "sampler_jittered.hpp"
#include "filter.hpp"
#include "filter_gaussian_blur.hpp"
#include "filter_invert.hpp"

using namespace ray_tracer;

const int width = 500, height = 500;

void test1(SDL_Surface *screen) {
	world world(false);
	camera *cam;
	view_plane *plane;
	surface_sphere *s1;
	surface_plane *s2;
	material_blinn_phong *m1, *m2;
	texture *t1, *t2;
	light *l;
	char buf[16];

	cam = new camera_pinhole(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), 10);
	plane = new view_plane(-20, 20, 20, -20);

	s1 = new surface_sphere(point3D(15, -7, 0), 8);
	m1 = new material_blinn_phong;
	t1 = new texture_solid_color(colorRGB(0.2, 0.6, 0.8));
	m1->set_specular_shininess(6);
	s1->set_material(m1);
	s1->set_texture(t1);

	s2 = new surface_plane(point3D(100, 0, 0), vector3D(-1, 0, 0));
	m2 = new material_blinn_phong;
	m2->set_specular_shininess(100);
	s2->set_material(m2);
	t2 = new texture_checker;
	s2->set_texture(t2);

	l = new light(point3D(0, 0, 30), color_white);

	world.set_ambient(color_white);
	world.set_camera(cam);
	world.set_view_plane(plane);
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
	world world(true);
	camera *cam;
	view_plane *plane;
	surface *s1, *s2, *s3;
	material_blinn_phong *m1, *m2;
	texture *t1, *t2, *t3;
	light *l;
	filter *f;

	// cam = new camera_fisheye(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), pi / 2);
	// cam = new camera_thinlens(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), 10, 30, 4);
	// cam = new camera_orthographic(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1));
	cam = new camera_pinhole(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), 10);
	// cam->rotate(pi / 4);
	plane = new view_plane(-20, 20, 20, -20);

	s1 = new surface_sphere(point3D(15, -7, 0), 8);
	m1 = new material_blinn_phong;
	t1 = new texture_solid_color(colorRGB(0.2, 0.6, 0.8));
	m1->set_specular_shininess(6);
	s1->set_material(m1);
	s1->set_texture(t1);

	s2 = new surface_sphere(point3D(30, 9, 0), 8);
	m2 = new material_blinn_phong;
	t2 = new texture_solid_color(colorRGB(0.8, 0.2, 0.8));
	m2->set_specular_shininess(100);
	s2->set_material(m2);
	s2->set_texture(t2);

	s3 = new surface_plane(point3D(50, 0, 0), vector3D(-1, 0, 1));
	s3->set_material(m2);
	t3 = new texture_checker(color_red, color_green);
	s3->set_texture(t3);

	l = new light(point3D(0, 0, 30), color_white);

	f = new filter_invert(NULL);

	world.set_ambient(color_white / 5);
	world.set_camera(cam);
	world.set_view_plane(plane);
	world.add_surface(s1);
	world.add_surface(s2);
	world.add_surface(s3);
	world.add_light(l);
	// world.set_filter(f);
	world.fit_window(width, height, screen->pixels);

	if (SDL_MUSTLOCK(screen)) {
		if (SDL_LockSurface(screen) < 0) {
			printf("Couldn't lock the screen: %s.\n", SDL_GetError());
			return;
		}
	}
	world.render_scene();
	if (SDL_MUSTLOCK(screen)) {
		SDL_UnlockSurface(screen);
	}
	SDL_UpdateRect(screen, 0, 0, width, height);
	SDL_SaveBMP(screen, "C:\\Users\\ForeverBell\\Desktop\\a.bmp");
}

void test3(SDL_Surface *screen) {
	srand(100);
	sampler *sam = new sampler_jittered();
	sam->generate(10000);
	sam->map_sample_to_disk();
	if (SDL_MUSTLOCK(screen)) {
		if (SDL_LockSurface(screen) < 0) {
			printf("Couldn't lock the screen: %s.\n", SDL_GetError());
			return;
		}
	}
	for (int i = 1; i <= 10000; ++i) {
		point2D p = sam->get_sampler_zoomed(width);
		int x = p.x, y = p.y;
		int *ptr = (int *)screen->pixels;
		ptr += y * width + x;
		*ptr = color_red.clamp_to_int();
	}

	if (SDL_MUSTLOCK(screen)) {
		SDL_UnlockSurface(screen);
	}
	SDL_UpdateRect(screen, 0, 0, width, height);
}

int main() {
	if (SDL_Init(SDL_INIT_VIDEO) == -1) { 
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		return 0;
	}

	SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
	if (screen == NULL) {
		printf("Couldn't set destination video mode: %s.\n", SDL_GetError());
		return 0;
	}

	test2(screen);

	SDL_Event event;
	while (SDL_WaitEvent(&event));
	SDL_Quit();
	return 0;
}
