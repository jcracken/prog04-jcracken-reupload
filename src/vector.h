#ifndef VECTOR_H
#define VECTOR_H

class vector {
private:
	float arr[3];
public:
	vector();
	vector(float a, float b, float c);
	void addConst(float num);
	void multConst(float num);
	float* getArr();
	float dotProduct(vector* other);
	void add(vector* other);
	vector crossProduct(vector* other);
};
#endif