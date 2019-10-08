#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
	// to get around type qualifiers not compatible with member function
	BoundingBox box_ = box;
	Eigen::Vector3d delta, center = box_.center();

	// when looking at i = 0 (x's), finding closest x value on the surface of the box
	//	 closest x value is found by determining if x is within minx and maxx (then closest x is the current one)
	//		if not, then by finding the delta x where a line that goes straight to the center intersects the surface
	// repeat for y and z
	for (int i = 0; i <3 ; i++)
		// a negative value would mean that e.g. for delta y that the point lies between
		//		the top and bottom planes of the box => shortest line would have delta.y=0
		delta[i] = std::max(std::abs(query[i]-center[i]) - (box.max_corner[i] - box.min_corner[i])/2, 0.0);

	return delta.squaredNorm();
}
