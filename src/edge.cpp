#include "edge.h"

edge::edge(){
	//constructor
	this->head = NULL;
	this->tail = NULL;
}

bool edge::isSame(vect head, vect tail){
	if (this->head->comp(&head) && this->tail->comp(&tail) || this->head->comp(&tail) && this->tail->comp(&head)) return true;
	else return false;
}

float* edge::loopHelp(){
	float ret[3] = { 0 };
	if (triang.size() == 2) { //check to see if it's a boundary
		float* temp1 = triang.at(0).thirdPoint(*head, *tail).getArr();
		float* temp2 = triang.at(1).thirdPoint(*head, *tail).getArr();
		ret[0] = (1.0 / 8.0) * (temp1[0] + temp2[0]);
		ret[1] = (1.0 / 8.0) * (temp1[1] + temp2[1]);
		ret[2] = (1.0 / 8.0) * (temp1[2] + temp2[2]);
	}
	return ret;
}

void edge::populatePoint(vect point){
	if (this->head == NULL) this->head == &point;
	else this->tail == &point;
}

void edge::populateTriangle(triangle t) {
	this->triang.push_back(t);
}
