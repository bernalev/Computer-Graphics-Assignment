#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
	double d, lowest_d = std::numeric_limits<double>::infinity();
	
	for (int i = 0; i < points.rows(); i++) {
		d = (points.row(i) - query).squaredNorm();
		if (d < lowest_d) {
			lowest_d = d;
			I = i;
		}
	}

	sqrD = lowest_d;
}