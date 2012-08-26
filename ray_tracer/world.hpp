#ifndef __WOLRD_HPP
#define __WOLRD_HPP

#include <vector>
#include "light.hpp"
#include "surface.hpp"
#include "camera.hpp"

namespace ray_tracer {
	class world {
		friend class raster_image;
		friend class ray_tracer;
	public:
		world();
		~world();
		colorRGB get_ambient() const;
		void set_ambient(const colorRGB &);
		void add_light(light *);
		void add_surface(surface *);
		void set_camera(camera *);
		void set_raster_image(raster_image *);
		void fit_window(int, int, void *); // Dimension: pixal
		void render_scene();		
	private:
		colorRGB ambient;
		std::vector<light *> lights;
		std::vector<surface *> surfaces;
		camera *camera_ptr;
		raster_image *image_ptr;
		ray_tracer *tracer_ptr;
		int dest_w, dest_h, *pixal_buffer_ptr;
	};

	inline colorRGB world::get_ambient() const {
		return ambient;
	}

	inline void world::set_ambient(const colorRGB &ambient_) {
		ambient = ambient_;
	}
}

#endif