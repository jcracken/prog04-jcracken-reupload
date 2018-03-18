#ifndef OBJ_H
#define OBJ_H

#include "vect.h"
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
public:
	void readData(std::string filename);
	void writeData(std::string filename);
};
#endif