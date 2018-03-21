#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vect.h"
#include "edge.h"
#include <vector>

class triangle {
private:
	std::vector<vect> points;
	std::vector<edge> edges;
public:
	triangle();
	vect thirdPoint(vect head, vect tail);
	void populatePoint(vect point);
	void populateEdge(edge n);
};
#endif