#ifndef __CONVEX_HPP__
#define __CONVEX_HPP__

#include <utility>
#include <tuple>
#include <map>
#include <vector>
#include "point3D.hpp"

namespace ray_tracer {

	typedef std::tuple<int, int, int> face_t;

	class convexhull {
	public:
		convexhull(std::vector<point3D> &);
		std::vector<face_t> construct_hull();
	private:
		bool remove_hidden_face(int, int, int);
		void walk_hidden_face(int, int);
	private:
		std::vector<std::pair<face_t, bool> > faces;
		std::vector<point3D> &points;
		std::map<std::pair<int, int>, int> belong;
	};
}

#endif