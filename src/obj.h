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
	std::vector<vect> points; //list of points read in from file
	std::vector<vect> faces; //list of faces read in from file
	std::vector<edge> edges; //list of edges generated from above
	std::vector<triangle> triangles; //list of triangles generated from above
	std::vector<std::vector<int>> pointConns; //kind of a jerry rig; 2D vector that stores all point connections
public:
	obj(); //constructor
	void readData(std::string filename); //read in data from file and store it in points and faces
	void writeData(std::string filename); //write data from points and faces
	void storeData(); //store data from points and faces in edges, triangles and pointconns
	void subdivide(); //loop subdivision
	void subdivide_ug(float lambda);
};
#endif