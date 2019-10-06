#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
	double lowest_t = std::numeric_limits<double>::infinity();
	bool is_hit;

	for (int i = 0; i < F.rows(); i++) {
		Eigen::RowVector3d A = V.row(F(i, 0));
		Eigen::RowVector3d B = V.row(F(i, 1));
		Eigen::RowVector3d C = V.row(F(i, 2));
		if (ray_intersect_triangle(ray, A, B, C, min_t, max_t, hit_t)) {
			if (hit_t < lowest_t) {
				lowest_t = hit_t;
				hit_f = i;
				is_hit = true;
			}
		}
	}
    
    hit_t = lowest_t;

    return is_hit;
}
