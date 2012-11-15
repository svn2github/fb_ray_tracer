
#include <algorithm>
#include "convexhull.hpp"
#include "misc.hpp"

namespace ray_tracer {

	convexhull::convexhull(std::vector<point3D> &points_) : points(points_) { }

	bool convexhull::remove_hidden_face(int p, int b, int a) {
		int f = belong[std::make_pair(b, a)];

		if (faces[f].second) {
			double volume = ((points[std::get<0>(faces[f].first)] - points[p]) ^ (points[std::get<1>(faces[f].first)] - points[p])) * (points[std::get<2>(faces[f].first)] - points[p]);
			if (dblcmp(volume) > 0) {
				return true;
			} else {
				belong[std::make_pair(a, b)] = belong[std::make_pair(b, p)] = belong[std::make_pair(p, a)] = faces.size();
				faces.push_back(std::make_pair(std::make_tuple(a, b, p), true));
			}
		}
		return false;
	}

	void convexhull::walk_hidden_face(int p, int f) {
		faces[f].second = false;
		if (remove_hidden_face(p, std::get<1>(faces[f].first), std::get<0>(faces[f].first))) {
			walk_hidden_face(p, belong[std::make_pair(std::get<1>(faces[f].first), std::get<0>(faces[f].first))]);
		} 
		if (remove_hidden_face(p, std::get<2>(faces[f].first), std::get<1>(faces[f].first))) {
			walk_hidden_face(p, belong[std::make_pair(std::get<2>(faces[f].first), std::get<1>(faces[f].first))]);
		}
		if (remove_hidden_face(p, std::get<0>(faces[f].first), std::get<2>(faces[f].first))) {
			walk_hidden_face(p, belong[std::make_pair(std::get<0>(faces[f].first), std::get<2>(faces[f].first))]);
		}
	}

	/* Complexity: O(N^2). */
	std::pair<std::vector<face_t>, std::vector<edge_t> > convexhull::construct_hull() {
		int n = points.size(), flag = 0;
		std::vector<face_t> ret_faces;
		std::vector<edge_t> ret_edges;
		face_t f;
		double volume;

		/* Ensure the first four vertices which don't share the same face. */
		for (int i = 1; i < n; ++i) {
			if (dblcmp((points[i] - points[0]).length()) > 0) {
				std::swap(points[i], points[1]);
				flag |= 1;
				break;
			}
		}
		for (int i = 2; i < n; ++i) {
			if (dblcmp(fabs((points[1] - points[0]) * (points[i] - points[0]))) > 0) {
				std::swap(points[i], points[2]);
				flag |= 2;
				break;
			}
		}
		for (int i = 3; i < n; ++i) {
			if (dblcmp(fabs(((points[1] - points[0]) ^ (points[2] - points[0])) * (points[i] - points[0]))) > 0) {
				std::swap(points[i], points[3]);
				flag |= 4;
				break;
			}
		}
		if (flag != 7) return std::make_pair(ret_faces, ret_edges);
		/* Init the first face. */
		for (int i = 0; i < 4; ++i) {
			std::get<0>(f) = (i + 1) % 4, std::get<1>(f) = (i + 2) % 4, std::get<2>(f) = (i + 3) % 4;
			volume = ((points[std::get<0>(f)] - points[i]) ^ (points[std::get<1>(f)] - points[i])) * (points[std::get<2>(f)] - points[i]);
			if (dblcmp(volume) > 0) std::swap(std::get<0>(f), std::get<1>(f));
			belong[std::make_pair(std::get<0>(f), std::get<1>(f))] = belong[std::make_pair(std::get<1>(f), std::get<2>(f))] = belong[std::make_pair(std::get<2>(f), std::get<0>(f))] = faces.size();
			faces.push_back(std::make_pair(f, true));
		}
		/* Construct the 3D hull. */
		std::random_shuffle(points.begin() + 4, points.end());
		for (int i = 4; i < n; ++i) {
			for (unsigned int j = 0; j < faces.size(); ++j) {
				if (faces[j].second) {
					f = faces[j].first;
					volume = ((points[std::get<0>(f)] - points[i]) ^ (points[std::get<1>(f)] - points[i])) * (points[std::get<2>(f)] - points[i]);
					if (dblcmp(volume) > 0) walk_hidden_face(i, j);
				}
			}
		}
		/* Remove hidden face from face array. */
		for (std::vector<std::pair<face_t, bool> >::iterator it = faces.begin(); it != faces.end(); ++it) {
			if (it->second) ret_faces.push_back(it->first);
		}
		for (std::map<std::pair<int, int>, int>::iterator it = belong.begin(); it != belong.end(); ++it) {
			if (faces[it->second].second && it->first.first < it->first.second) ret_edges.push_back(it->first);
		}
		return std::make_pair(ret_faces, ret_edges);
	}
}
