#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
	// pseudo code for algo in the README for assignment 4

	// a min heap
	std::priority_queue<std::pair<double, std::shared_ptr<Object>>, 
		std::vector<std::pair<double, std::shared_ptr<Object>>>,
		std::greater<std::pair<double, std::shared_ptr<Object>>> > q;

	// distance to root's box 
	double d_r = point_box_squared_distance(query, root->box);
	q.push(make_pair(d_r, root));

	double d = std::numeric_limits<double>::infinity();
	std::shared_ptr<Object> desc;
	std::pair<double, std::shared_ptr<Object>> popped;

	while (!q.empty()) {
		popped = q.top();
		q.pop();

		// this isn't great because d stays infinite until the leaves are reached 
		// on a balanced tree, which it has been approx. designed to be, would reach about all of the nodes
		if (popped.first < d) {
			std::shared_ptr<AABBTree> aabb = std::dynamic_pointer_cast<AABBTree>(popped.second);
			if (!aabb) {//subtree is a leaf
				popped.second->point_squared_distance(query, min_sqrd, max_sqrd, sqrd, desc);
				if (sqrd < d && sqrd >= min_sqrd && sqrd <= max_sqrd) {
					d = sqrd;// distance from query to leaf object
					descendant = popped.second;
				}
			}
			else {
				double d_l = point_box_squared_distance(query, aabb->left->box);
				q.push(make_pair(d_l, aabb->left));
				double d_r = point_box_squared_distance(query, aabb->right->box);
				q.push(make_pair(d_r, aabb->right));
			}
		}
	}

	sqrd = d;
	return true;
}