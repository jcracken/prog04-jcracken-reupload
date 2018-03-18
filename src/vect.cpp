#include "vect.h"

vect::vect() {
	this->arr[0] = 0;
	this->arr[1] = 0;
	this->arr[2] = 0;
}

vect::vect(float a, float b, float c) {
	this->arr[0] = a;
	this->arr[1] = b;
	this->arr[2] = c;
}

void vect::addConst(float num) {
	this->arr[0] = this->arr[0] + num;
	this->arr[1] = this->arr[1] + num;
	this->arr[2] = this->arr[2] + num;
}

void vect::multConst(float num) {
	this->arr[0] = this->arr[0] * num;
	this->arr[1] = this->arr[1] * num;
	this->arr[2] = this->arr[2] * num;
}

float * vect::getArr() {
	return this->arr;
}

float vect::dotProduct(vect * other){
	return this->arr[0] * (other->getArr()[0]) + this->arr[1] * (other->getArr()[1]) + this->arr[2] * (other->getArr()[2]);
}

void vect::add(vect * other){
	this->arr[0] = this->arr[0] + other->getArr()[0];
	this->arr[1] = this->arr[1] + other->getArr()[1];
	this->arr[2] = this->arr[2] + other->getArr()[2];
}

vect vect::crossProduct(vect * other) {
	return vect(this->arr[1] * other->getArr()[2] - other->getArr()[1] * this->arr[2], other->getArr()[0] * this->arr[2] - this->arr[0] * other->getArr()[2], this->arr[0] * other->getArr()[1] - other->getArr()[0] * this->arr[1]);
}
