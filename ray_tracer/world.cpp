
#include "world.hpp"
#include "ray.hpp"
#include "vector3D.hpp"
#include "light.hpp"
#include "surface.hpp"
#include "raster_image.hpp"
#include "ray_tracer.hpp"

namespace ray_tracer {

	world::world() {
		tracer_ptr = new ray_tracer;
	}

	world::~world() {
		delete tracer_ptr;
	}

	void world::add_light(light *light_ptr_) {
		lights_ptr.push_back(light_ptr_);
	}

	void world::add_surface(surface *surface_ptr_) {
		surfaces_ptr.push_back(surface_ptr_);
	}

	void world::set_camera(camera *camera_ptr_) {
		camera_ptr = camera_ptr_;
	}

	void world::set_raster_image(raster_image *image_ptr_) {
		image_ptr = image_ptr_;
	}

	void world::render_scene() {
		image_ptr->render_scene(this, tracer_ptr, camera_ptr);
	}
}