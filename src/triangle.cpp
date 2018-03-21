#include "triangle.h"

triangle::triangle(){
	//constructor
}

vect triangle::thirdPoint(vect head, vect tail){
	unsigned int i = 0;
	for (i = 0; i < this->points.size(); i++) {
		if (!(head.comp(&this->points.at(i))) && !(tail.comp(&this->points.at(i)))) return this->points.at(i);
	}
	return vect(0, 0, 0); //should never happen
}

void triangle::populatePoint(vect point){
	this->points.push_back(point);
}