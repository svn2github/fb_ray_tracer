
#include <iostream>
#include <thread>
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
#include "surface_quadratic.hpp"
#include "texture.hpp"
#include "texture_checker.hpp"
#include "texture_image.hpp"
#include "texture_solid_color.hpp"
#include "texture_mapping.hpp"
#include "texture_mapping_sphere.hpp"
#include "fog.hpp"
#include "world.hpp"
#include "light.hpp"
#include "light_point.hpp"
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

const int width = 500, height = 500;

void test1(SDL_Surface *screen) {
	world world;
	camera *cam;
	surface_quadratic *s1;
	surface *s2, *s3;
	// material_matte *m1;
	material_mirror *m1;
	material_mirror *m2;
	material_matte *m3;
	texture *t1, *t2, *t3;
	light *l, *l2;

	// cam = new camera_fisheye(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), pi / 2);
	// cam = new camera_thinlens(point3D(-10, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), atan(2.0), atan(2.0), 35, 3.5, true);
	// cam = new camera_orthographic(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), 40, 40);
	cam = new camera_pinhole(point3D(-10, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), atan(2.0), atan(2.0), true);
	// cam->rotate(pi / 4);

	s1 = new surface_quadratic; //surface_sphere(point3D(15, -7, 0), 9);
	// m1 = new material_matte;
	m1 = new material_mirror(colorRGB(0.2, 0.6, 0.8));
	t1 = new texture_solid_color(colorRGB(0.2, 0.6, 0.8));
	s1->set_material(m1);
	s1->set_texture(t1);
	s2 = new surface_sphere(point3D(30, 9, 0), 11);
	// m2 = new material_phong;
	// m2->set_specular_shininess(50);
	m2 = new material_mirror(colorRGB(0.8, 0.2, 0.8));
	t2 = new texture_solid_color(colorRGB(0.8, 0.2, 0.8));

	s2->set_material(m2);
	s2->set_texture(t2);

	s3 = new surface_plane(point3D(0, 0, -10), vector3D(0, 0, 1));
	m3 = new material_matte;
	s3->set_material(m3);
	t3 = new texture_checker;
	s3->set_texture(t3);

	// l = new light_point(point3D(0, 0, 0), color_white);
	l = new light_point(point3D(-10, 0, 0), color_white);
	l->set_spot(vector3D(30, 9, -30), pi / 3, 5);
	l->set_attenuation(1, 0.001, 0.0005);
	l2 = new light_point(point3D(-10, 0, 30), color_white);
	l2->set_attenuation(1, 0.001, 0.0005);

	world.set_ambient(color_white / 5);
	world.set_sampler(new sampler_jittered(25));
	world.set_camera(cam);
	world.set_fog(new fog(0.01, 1, color_black));
	world.add_surface(s1);
	world.add_surface(s2);
	world.add_surface(s3);
	world.add_light(l);
	world.add_light(l2);

	if (SDL_MUSTLOCK(screen)) {
		if (SDL_LockSurface(screen) < 0) {
			printf("Couldn't lock the screen: %s.\n", SDL_GetError());
			return;
		}
	}
	world.render_begin(width, height, screen->pixels);
	std::thread thr[4];
	for (int i = 0; i < 4; i += 1) {
		thr[i] = std::thread([&]{ world.render_scene(); });
	}
	for (int i = 0; i < 4; i += 1) {
		thr[i].join();
	}
	if (SDL_MUSTLOCK(screen)) {
		SDL_UnlockSurface(screen);
	}
	SDL_UpdateRect(screen, 0, 0, width, height);
	SDL_SaveBMP(screen, "C:\\Users\\ForeverBell\\Desktop\\a.bmp");
}

void test2(SDL_Surface *screen) {
	world world;
	camera *cam;
	surface *s;
	material *m;
	texture *t;
	light *l;
	SDL_Surface *img;

	img = SDL_LoadBMP("C:\\Users\\ForeverBell\\Desktop\\moon.bmp");
	SDL_LockSurface(img);
	cam = new camera_pinhole(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), atan(2), atan(2), true);
	// cam = new camera_orthographic(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), 40, 40);

	s = new surface_sphere(point3D(25, 0, 0), 10);
	m = new material_matte(colorRGB(1.4, 1.4, 0.5));
	t = new texture_image(new image(img->pixels, img->w, img->h, 24), new texture_mapping_sphere());
	s->set_material(m);
	s->set_texture(t);

	l = new light_point(point3D(0, -30, 30), color_white);
	l->set_shadow(false);

	world.set_ambient(color_black);
	world.set_sampler(new sampler_jittered(25));
	world.set_camera(cam);
	world.add_surface(s);
	world.add_light(l);

	if (SDL_MUSTLOCK(screen)) {
		if (SDL_LockSurface(screen) < 0) {
			printf("Couldn't lock the screen: %s.\n", SDL_GetError());
			return;
		}
	}
	world.render_begin(width, height, screen->pixels);
	world.render_scene();
	if (SDL_MUSTLOCK(screen)) {
		SDL_UnlockSurface(screen);
	}
	SDL_UpdateRect(screen, 0, 0, width, height);
	SDL_SaveBMP(screen, "C:\\Users\\ForeverBell\\Desktop\\a.bmp");
}


void test3(SDL_Surface *screen) {
	world world;
	camera *cam;
	surface *s;
	material_phong *m;
	texture *t;
	light *l;

	cam = new camera_pinhole(point3D(-20, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), atan(2), atan(2), true);
	// cam = new camera_orthographic(point3D(0, 0, 0), point3D(1, 0, 0), vector3D(0, 0, 1), 40, 40);

	s = new surface_quadratic;
	m = new material_phong;
	m->set_specular_shininess(10);
	t = new texture_checker(color_white, colorRGB(0.2, 0.2, 0.2));
	s->set_material(m);
	s->set_texture(t);

	l = new light_point(point3D(-20, 0, 0), color_white);
	l->set_shadow(false);

	world.set_ambient(color_white / 5);
	// world.set_sampler(new sampler_jittered(25));
	world.set_camera(cam);
	world.add_surface(s);
	world.add_light(l);

	if (SDL_MUSTLOCK(screen)) {
		if (SDL_LockSurface(screen) < 0) {
			printf("Couldn't lock the screen: %s.\n", SDL_GetError());
			return;
		}
	}
	world.render_begin(width, height, screen->pixels);
	world.render_scene();
	if (SDL_MUSTLOCK(screen)) {
		SDL_UnlockSurface(screen);
	}
	SDL_UpdateRect(screen, 0, 0, width, height);
	SDL_SaveBMP(screen, "C:\\Users\\ForeverBell\\Desktop\\a.bmp");
}

int main() {
	// algebra_quadratic a;
	// a.xx = 2, a.yy = 1, a.z = 1, a.c = -3;
	// printf("%.6lf\n", a.find_root(point3D(0, 0, 0), vector3D(1, 1, 1).normalized()));
	if (SDL_Init(SDL_INIT_VIDEO) == -1) { 
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		return 0;
	}

	SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
	if (screen == NULL) {
		printf("Couldn't set destination video mode: %s.\n", SDL_GetError());
		return 0;
	}

	DWORD old_time = GetTickCount();
	test1(screen);
	std::cout << "Total time used: " << GetTickCount() - old_time << std::endl;

	SDL_Event event;
	while (SDL_WaitEvent(&event));
	SDL_Quit();
	return 0;
}
