#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
	// page 303 of the textbook: pseudo code for hit traversal 
	
	// if ray doesn't even hit bounding box
	if (!ray_intersect_box(ray, this->box, min_t, max_t))
		return false;
	
	double t_l, t_r;
	std::shared_ptr<Object> desc_l, desc_r;
	
	// Test whether cast failed 
	// (points to a primitive - which doesn't set a descendant, which is itself)
	if (!std::dynamic_pointer_cast<AABBTree>(this->left))
		desc_l = this->left; 	
	if (!std::dynamic_pointer_cast<AABBTree>(this->right))
		desc_r = this->right; 

	bool left_hit = this->left->ray_intersect(ray, min_t, max_t, t_l, desc_l);
	bool right_hit = this->right->ray_intersect(ray, min_t, max_t, t_r, desc_r);

	if (left_hit && right_hit) {
		if (t_l < t_r) {
			t = t_l;
			descendant = desc_l;
		}
		else {
			t = t_r;
			descendant = desc_r;
		}
		return true;
	}
	else if (left_hit) {
		t = t_l;
		descendant = desc_l;
		return true;
	}
	else if (right_hit) {
		t = t_r;
		descendant = desc_r;
		return true;
	}
	else
		return false; 
}