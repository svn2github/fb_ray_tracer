
#include <iostream>
#include <Windows.h>
#include <SDL.h>
#include "vector3D.hpp"
#include "material.hpp"
#include "material_phong.hpp"
#include "material_matte.hpp"
#include "material_mirror.hpp"
#include "surface.hpp"
#include "surface_sphere.hpp"
#include "surface_plane.hpp"
#include "surface_triangle.hpp"
#include "texture.hpp"
#include "texture_checker.hpp"
#include "texture_image.hpp"
#include "texture_solid_color.hpp"
#include "texture_mapping.hpp"
#include "texture_mapping_sphere.hpp"
#include "view_plane.hpp"
#include "fog.hpp"
#include "world.hpp"
#include "light.hpp"
#include "light_point.hpp"
#include "light_spot.hpp"
#include "light_area.hpp"
#include "camera.hpp"
#include "camera_orthographic.hpp"
#include "camera_pinhole.hpp"
#include "camera_thinlens.hpp"
#include "camera_fisheye.hpp"
#include "sampler.hpp"
#include "sampler_random.hpp"
#include "sampler_jittered.hpp"

using namespace ray_tracer;

const int width = 1000, height = 1000;

void test1(SDL_Surface *screen) {
	world world;
	camera *cam;
	view_plane *plane;
	surface_sphere *s1;
	surface_plane *s2;
	material_phong *m1, *m2;
	texture *t1, *t2;
	light *l;
	char buf[16];

	cam = new camera_pinhole(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), 10);
	plane = new view_plane(-20, 20, 20, -20);

	s1 = new surface_sphere(point3D(15, -7, 0), 8);
	m1 = new material_phong;
	t1 = new texture_solid_color(colorRGB(0.2, 0.6, 0.8));
	m1->set_specular_shininess(6);
	s1->set_material(m1);
	s1->set_texture(t1);

	s2 = new surface_plane(point3D(100, 0, 0), vector3D(-1, 0, 0));
	m2 = new material_phong;
	m2->set_specular_shininess(100);
	s2->set_material(m2);
	t2 = new texture_checker;
	s2->set_texture(t2);

	l = new light_point(point3D(0, 0, 30), color_white, false);

	world.set_ambient(color_white / 5);
	world.set_camera(cam);
	world.set_view_plane(plane);
	world.add_surface(s1);
	// world.add_surface(s2);
	world.add_light(l);
	world.fit_window(width, height, screen->pixels);

	int fps = 0;
	DWORD old_time = GetTickCount();

	while (true) {
		if (SDL_MUSTLOCK(screen)) {
			if (SDL_LockSurface(screen) < 0) {
				printf("Couldn't lock the screen: %s.\n", SDL_GetError());
				return;
			}
		}

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
	camera *cam;
	view_plane *plane;
	surface *s1, *s2, *s3;
	//material_phong *m1;
	material_mirror *m1, *m2;
	material_phong *m3;
	texture *t1, *t2, *t3;
	light *l, *l2;

	// cam = new camera_fisheye(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), pi / 2);
	// cam = new camera_thinlens(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), 10, 30, 4);
	// cam = new camera_orthographic(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1));
	cam = new camera_pinhole(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), 10);
	// cam->rotate(pi / 4);
	plane = new view_plane(-20, 20, 20, -20);

	s1 = new surface_sphere(point3D(15, -7, 0), 9);
	// m1 = new material_phong;
	// m1->set_specular_shininess(6);
	m1 = new material_mirror;
	m1->set_mirror_coefficient(colorRGB(0.2, 0.6, 0.8));
	t1 = new texture_solid_color(colorRGB(0.2, 0.6, 0.8));
	
	s1->set_material(m1);
	s1->set_texture(t1);

	s2 = new surface_sphere(point3D(30, 9, 0), 12);
	// m2 = new material_phong;
	// m2->set_specular_shininess(50);
	m2 = new material_mirror;
	m2->set_mirror_coefficient(colorRGB(0.8, 0.2, 0.8));
	t2 = new texture_solid_color(color_white);

	s2->set_material(m2);
	s2->set_texture(t2);

	s3 = new surface_plane(point3D(50, 0, 16), vector3D(-1, 0, 1));
	m3 = new material_phong;
	m3->set_specular_shininess(50);
	s3->set_material(m3);
	t3 = new texture_checker;
	s3->set_texture(t3);

	// l = new light_spot(point3D(0, 0, 30), color_white, true, vector3D(30, 9, -30), pi / 7, 5);
	// l = new light_point(point3D(0, 0, 0), color_white, true);
	l = new light_area(point3D(0, 0, 0), color_white, true, 10, vector3D(30, 9, -30));
	//l->set_attenuation_constant(1);
	//l->set_attenuation_linear(0.001);
	//l->set_attenuation_quadratic(0.0005);
	l2 = new light_point(point3D(0, 0, 30), color_white, true);

	world.set_ambient(color_white / 5);
	world.set_sampler(new sampler_jittered(144));
	world.set_camera(cam);
	world.set_view_plane(plane);
	world.set_fog(new fog(0.01, 1, color_black));
	world.add_surface(s1);
	world.add_surface(s2);
	world.add_surface(s3);
	world.add_light(l);
	world.add_light(l2);
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
	sampler *sam = new sampler_jittered(10000);
	if (SDL_MUSTLOCK(screen)) {
		if (SDL_LockSurface(screen) < 0) {
			printf("Couldn't lock the screen: %s.\n", SDL_GetError());
			return;
		}
	}
	for (int i = 1; i <= 10000; ++i) {
		sam->next_sampler();
		point2D p = sam->get_sampler_zoomed(sampler_set_anti_aliasing, width);
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

void test4(SDL_Surface *screen) {
	world world;
	camera *cam;
	view_plane *plane;
	surface *s;
	material *m;
	texture *t;
	light *l;
	SDL_Surface *img;

	img = SDL_LoadBMP("C:\\Users\\ForeverBell\\Desktop\\earth.bmp");
	SDL_LockSurface(img);
	cam = new camera_pinhole(point3D(0, 10, 0), point3D(40, 0, 0), vector3D(0, 0, 1), 40);
	// cam = new camera_orthographic(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1));
	plane = new view_plane(-20, 20, 20, -20);

	s = new surface_sphere(point3D(40, 0, 0), 10);
	m = new material_matte;
	t = new texture_image(new image(img->pixels, img->w, img->h, 24), new texture_mapping_sphere());
	s->set_material(m);
	s->set_texture(t);

	l = new light_point(point3D(0, 50, 30), color_white, false);

	world.set_ambient(color_white / 5);
	world.set_camera(cam);
	world.set_view_plane(plane);
	world.add_surface(s);
	world.add_light(l);
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
