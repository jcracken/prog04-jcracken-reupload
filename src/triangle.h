#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vect.h"
#include <vector>

class triangle {
private:
	std::vector<vect> points;
public:
	triangle();
	vect thirdPoint(vect head, vect tail);
	void populatePoint(vect point);
};
#endif