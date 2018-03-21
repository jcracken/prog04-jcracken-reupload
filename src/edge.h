#ifndef EDGE_H
#define EDGE_H

#include "vect.h"
#include "triangle.h"
#include <vector>

class edge {
private:
	vect* head;
	vect* tail;
	std::vector<triangle*> triang;
public:
	edge();
	bool isSame(vect head, vect tail);
	float* loopHelp();
	void populatePoint(vect point);
	void populateTriangle(triangle* t);
};
#endif