#include "obj.h"

void obj::readData(std::string filename) {

}

void obj::writeData(std::string filename) {
	std::ofstream out(filename, std::ofstream::out);
	int i;
	for (i = 0; i < this->points.size(); i++) {
		out << "v " << this->points.at(i).getArr[0] << " " << this->points.at(i).getArr[1] << " " << this->points.at(i).getArr[2] << std::endl;
	}
	out << std::endl;
	for (i = 0; i < this->faces.size(); i++) {
		out << "f " << (int)(this->faces.at(i).getArr[0] + 1) << " " << (int)(this->faces.at(i).getArr[1] + 1) << " " << (int)(this->faces.at(i).getArr[2] + 1) << std::endl;
	}
	out.close();
}
