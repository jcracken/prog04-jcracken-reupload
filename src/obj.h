#ifndef OBJ_H
#define OBJ_H

#include "vect.h"
#include "edge.h"
#include "triangle.h"
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <cstdlib>
#include <iostream>
#include <sstream>

class obj {
private:
	std::vector<vect> points;
	std::vector<vect> faces;
	std::vector<edge> edges;
	std::vector<triangle> triangles;
public:
	void readData(std::string filename);
	void writeData(std::string filename);
	void storeData();
};
#endif