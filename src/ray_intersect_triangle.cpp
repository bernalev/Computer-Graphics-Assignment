#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
	// based on e+td = a +B(b-a)+Y(c-a)
	// page 93 of our textbook
	// intersection occurs in the triangle if B>0, Y>0 and B+Y<1
	// verticies of traingle are A, B, C

	Eigen::Vector3d r_d = ray.direction;
	Eigen::Vector3d r_e = ray.origin;

	double a = A.x() - B.x();
	double b = A.y() - B.y();
	double c = A.z() - B.z();
	double d = A.x() - C.x();
	double e = A.y() - C.y();
	double f = A.z() - C.z();
	double g = r_d.x();
	double h = r_d.y();
	double i = r_d.z();
	double j = A.x() - r_e.x();
	double k = A.y() - r_e.y();
	double l = A.z() - r_e.z();

	double M = a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);

	if (M == 0.0)
		return false;

	t = -(f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c)) / M;
	if (t < min_t || t > max_t)
		return false;

	double Y = (i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c)) / M;
	if (Y < 0 || Y >1)
		return false;

	double B_ = (j * (e * i - h * f) + k * (g * f - d * i) + l * (d * h - e * g)) / M;
	if (B_ < 0 || B_>1 - Y)
		return false;

	return true;
}

