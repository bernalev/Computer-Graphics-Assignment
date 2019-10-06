#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
	// intersect a box, based on logic of page 299->302 of our textbook
	Eigen::Vector3d e = ray.origin;
	Eigen::Vector3d d = ray.direction;
	Eigen::Vector3d max = box.max_corner;
	Eigen::Vector3d min = box.min_corner;
	Eigen::Vector3d tmin, tmax; 

	for (int i = 0; i < 3; i++) {
		if (d[i] == 0) {
			// keep the sign
			tmin[i] = (min[i] - e[i]) * std::numeric_limits<double>::infinity();
			tmax[i] = (max[i] - e[i]) * std::numeric_limits<double>::infinity();
		}
		else {
			if (d[i] > 0) {
				tmin[i] = (min[i] - e[i]) / d[i];
				tmax[i] = (max[i] - e[i]) / d[i];
			}
			else {
				tmin[i] = (max[i] - e[i]) / d[i];
				tmax[i] = (min[i] - e[i]) / d[i];
			}
		}
	}

	// ensure all five t ranges overlap
	//	(t's for x, y, z and given by min_t->max_t)
	double abs_tmin = std::max(tmin.x(), tmin.y());
	abs_tmin = std::max(abs_tmin, tmin.z());
	abs_tmin = std::max(abs_tmin, min_t);

	double abs_tmax = std::min(tmax.x(), tmax.y());
	abs_tmax = std::min(abs_tmax, tmax.z());
	abs_tmax = std::min(abs_tmax, max_t);

	// if the largest min t is larger than smallest max t, no overlap
	if (abs_tmin > abs_tmax)
		return false;
	else
		return true;
}