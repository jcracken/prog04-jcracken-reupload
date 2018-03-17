#include "vector.h"

vector::vector() {
	this->arr[0] = 0;
	this->arr[1] = 0;
	this->arr[2] = 0;
}

vector::vector(float a, float b, float c) {
	this->arr[0] = a;
	this->arr[1] = b;
	this->arr[2] = c;
}

void vector::addConst(float num) {
	this->arr[0] = this->arr[0] + num;
	this->arr[1] = this->arr[1] + num;
	this->arr[2] = this->arr[2] + num;
}

void vector::multConst(float num) {
	this->arr[0] = this->arr[0] * num;
	this->arr[1] = this->arr[1] * num;
	this->arr[2] = this->arr[2] * num;
}

float * vector::getArr() {
	return this->arr;
}

void vector::add(vector * other){
	this->arr[0] = this->arr[0] + other->getArr()[0];
	this->arr[1] = this->arr[1] + other->getArr()[1];
	this->arr[2] = this->arr[2] + other->getArr()[2];
}
