#ifndef VECT_H
#define VECT_H

class vect {
private:
	float arr[3];
public:
	vect();
	vect(float a, float b, float c);
	void addConst(float num);
	void multConst(float num);
	float* getArr();
	float dotProduct(vect* other);
	void add(vect* other);
	vect crossProduct(vect* other);
};
#endif