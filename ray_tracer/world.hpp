#ifndef __WOLRD_HPP
#define __WOLRD_HPP

#include <vector>
#include "colorRGB.hpp"
#include "vector3D.hpp"
#include "point3D.hpp"
#include "hitInfo.hpp"
#include "ray.hpp"
#include "light.hpp"
#include "surface.hpp"
#include "view_plane.hpp"
#include "camera.hpp"
#include "tracer.hpp"
#include "sampler_jittered.hpp"
#include "filter.hpp"

namespace ray_tracer {
	const int num_antialiasing_sampler = 25;
	class world {
	public:
		world(bool);
		~world();
		colorRGB get_ambient() const;
		void set_ambient(const colorRGB &);
		colorRGB get_background() const;
		void set_background(const colorRGB &);
		bool is_antialiasing_enabled() const;
		void enable_antialiasing();
		void disable_antialiasing();
		void add_light(light *);
		const std::vector<light *> &get_lights() const;
		void add_surface(surface *);
		const std::vector<surface *> &get_surfaces() const;
		camera *get_camera() const;
		void set_camera(camera *);
		view_plane *get_view_plane() const;
		void set_view_plane(view_plane *);
		tracer *get_tracer() const;
		void set_filter(filter *);
		filter *get_filter() const;
		// void set_ray_tracer(ray_tracer *);
		void fit_window(int, int, void *); // Dimension: pixal
		bool get_hit(ray *, hitInfo *);
		void render_scene();		
	private:
		colorRGB ambient, background;
		bool antialiasing_enabled;
		sampler *sampler_ptr;
		std::vector<light *> lights;
		std::vector<surface *> surfaces;
		camera *camera_ptr;
		view_plane *plane_ptr;
		tracer *tracer_ptr;
		filter *filter_ptr;
		int dest_w, dest_h, *pixal_buffer_ptr;
	};

	inline colorRGB world::get_ambient() const {
		return ambient;
	}

	inline void world::set_ambient(const colorRGB &ambient_) {
		ambient = ambient_;
	}

	inline colorRGB world::get_background() const {
		return background;
	}

	inline void world::set_background(const colorRGB &background_) {
		background = background_;
	}

	inline bool world::is_antialiasing_enabled() const {
		return antialiasing_enabled;
	}

	inline void world::enable_antialiasing() {
		if (antialiasing_enabled == false) {
			antialiasing_enabled = true;
			sampler_ptr = new sampler_jittered();
			sampler_ptr->generate(num_antialiasing_sampler);
		}
	}

	inline void world::disable_antialiasing() {
		if (antialiasing_enabled == true) {
			antialiasing_enabled = false;
			delete sampler_ptr;
		}
	}

	inline void world::add_light(light *light_ptr_) {
		lights.push_back(light_ptr_);
	}

	inline const std::vector<light *> &world::get_lights() const {
		return lights;
	}

	inline void world::add_surface(surface *surface_ptr_) {
		surfaces.push_back(surface_ptr_);
	}

	inline const std::vector<surface *> &world::get_surfaces() const {
		return surfaces;
	}

	inline camera *world::get_camera() const {
		return camera_ptr;
	}

	inline void world::set_camera(camera *camera_ptr_) {
		camera_ptr = camera_ptr_;
	}

	inline view_plane *world::get_view_plane() const {
		return plane_ptr;
	}

	inline void world::set_view_plane(view_plane *plane_ptr_) {
		plane_ptr = plane_ptr_;
	}

	inline tracer *world::get_tracer() const {
		return tracer_ptr;
	}

	inline filter *world::get_filter() const {
		return filter_ptr;
	}

	inline void world::set_filter(filter *filter_ptr_) {
		filter_ptr = filter_ptr_;
	}

	inline void world::fit_window(int w, int h, void *p) {
		dest_w = w;
		dest_h = h;
		pixal_buffer_ptr = (int *)p;
	}
}

#endif