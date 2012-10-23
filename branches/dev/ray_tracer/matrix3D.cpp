
#include "matrix3D.hpp"

namespace ray_tracer {

	matrix3D::matrix3D() {
		for (int i = 0; i < 3; i += 1) {
			for (int j = 0; j < 3; j += 1) {
				value[i][j] = 0;
			}
		}
	}

	matrix3D matrix3D::transpose() const {
		matrix3D result;

		for (int i = 0; i < 3; i += 1) {
			for (int j = 0; j < 3; j += 1) {
				result.value[i][j] = value[j][i];
			}
		}
		return result;
	}
}

