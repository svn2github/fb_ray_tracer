#ifndef __WOLRD_HPP__
#define __WOLRD_HPP__

#ifndef __MT_NO_MUTEX
#include <mutex> // C++0x Only
#endif
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
		friend class tracer;
		friend class camera;
	public:
		world();
		~world();
		colorRGB get_background() const;
		void set_ambient(const colorRGB &);
		void set_sampler(const sampler *);
		void add_light(const light *);
		void add_surface(const surface *);
		void set_fog(const fog *);
		void set_camera(const camera *);
		void set_view_plane(const view_plane *);
		bool get_hit(const ray &, hitInfo *) const;
		void render_begin(int, int, void *); // Dimension: pixal
		void render_scene();
	private:
		colorRGB ambient;
		std::vector<const light *> lights;
		std::vector<const surface *> surfaces;
		const fog *fog_ptr;
		const camera *camera_ptr;
		const view_plane *plane_ptr;
		const tracer *tracer_ptr;
		const sampler *sampler_ptr, *sampler_single_ptr;
		int *pixal_buffer_ptr;
		int dest_w, dest_h;
		int current_coordinate_x, current_coordinate_y;
#ifndef __MT_NO_MUTEX
		std::mutex coordinate_mutex;
#endif
	};

	inline colorRGB world::get_background() const {
		return fog_ptr == NULL ? color_black : fog_ptr->fog_color;
	}

	inline void world::set_ambient(const colorRGB &ambient_) {
		ambient = ambient_;
	}

	inline void world::set_sampler(const sampler *sampler_ptr_) {
		sampler_ptr = sampler_ptr_;
	}

	inline void world::add_light(const light *light_ptr_) {
		lights.push_back(light_ptr_);
	}

	inline void world::add_surface(const surface *surface_ptr_) {
		surfaces.push_back(surface_ptr_);
	}

	inline void world::set_fog(const fog *fog_ptr_) {
		fog_ptr = fog_ptr_;
	}

	inline void world::set_camera(const camera *camera_ptr_) {
		camera_ptr = camera_ptr_;
	}

	inline void world::set_view_plane(const view_plane *plane_ptr_) {
		plane_ptr = plane_ptr_;
	}
}

#endif