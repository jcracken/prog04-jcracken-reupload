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
	int odd;
public:
	edge();
	bool isSame(vect head, vect tail);
	void loopHelp(float* ret);
	void populatePoint(vect* point);
	void populateTriangle(triangle* t);
	void setOdd(int odd);
	int getOdd();
	vect* getHead();
	vect* getTail();
	bool isPart(vect point);
};
#endif