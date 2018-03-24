#ifndef TRIANGLE_H
#define TRIANGLE_H

class edge; //forward declaration, think of this as an edge.h include
#include "vect.h"
#include <vector>

class triangle {
private:
	std::vector<vect*> points;
	std::vector<edge*> edges;
public:
	triangle();
	vect thirdPoint(vect head, vect tail);
	void populatePoint(vect* point);
	void populateEdge(edge* e);
	vect getPoint(int num);
	edge* getEdge(int num);
};
#endif