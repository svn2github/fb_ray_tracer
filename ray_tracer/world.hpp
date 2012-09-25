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
#include "fog.hpp"
#include "camera.hpp"
#include "tracer.hpp"
#include "sampler.hpp"

namespace ray_tracer {
	class world {
	public:
		world();
		~world();

		/* access functions */
		colorRGB get_ambient() const;
		void set_ambient(const colorRGB &);
		colorRGB get_background() const;
		void set_sampler(sampler *);
		void add_light(light *);
		const std::vector<light *> &get_lights() const;
		void add_surface(surface *);
		const std::vector<surface *> &get_surfaces() const;
		fog *get_fog() const;
		void set_fog(fog *);
		camera *get_camera() const;
		void set_camera(camera *);
		view_plane *get_view_plane() const;
		void set_view_plane(view_plane *);
		tracer *get_tracer() const;

		/* help functions */
		void fit_window(int, int, void *); // Dimension: pixal
		bool get_hit(const ray &, hitInfo *);

		/* render functions */
		void render_begin();
		void render_scene();
	private:
		colorRGB ambient;
		sampler *sampler_ptr, *sampler_single_ptr;
		std::vector<light *> lights;
		std::vector<surface *> surfaces;
		fog *fog_ptr;
		camera *camera_ptr;
		view_plane *plane_ptr;
		tracer *tracer_ptr;
		int dest_w, dest_h, *pixal_buffer_ptr;
		int curr_rendering_x, curr_rendering_y, rendering_mutex;
	};

	inline colorRGB world::get_ambient() const {
		return ambient;
	}

	inline void world::set_ambient(const colorRGB &ambient_) {
		ambient = ambient_;
	}

	inline colorRGB world::get_background() const {
		return fog_ptr == NULL ? color_black : fog_ptr->get_fog_color();
	}

	inline void world::set_sampler(sampler *sampler_ptr_) {
		sampler_ptr = sampler_ptr_;
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

	inline fog *world::get_fog() const {
		return fog_ptr;
	}

	inline void world::set_fog(fog *fog_ptr_) {
		fog_ptr = fog_ptr_;
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
}

#endif