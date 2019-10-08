#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
	//find the smallest value for every axis and ensure the box's is smaller
	// repeat for larger
	for (int i = 0; i < 3; i++) {
		double min = std::min(a[i], b[i]);
		min = std::min(min, c[i]);
		min = std::min(min, B.min_corner[i]);
		B.min_corner[i] = min;

		double max = std::max(a[i], b[i]);
		max = std::max(max, c[i]);
		max = std::max(max, B.max_corner[i]);
		B.max_corner[i] = max;
	}
}
