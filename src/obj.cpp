#include "obj.h"

void obj::readData(std::string filename) {
	std::ifstream input(filename, std::ifstream::in);
	std::string parse;
	float a = 0, b = 0, c = 0;
	char type = '\0';
	if (!(input.is_open())) {
		std::cout << "invalid filename" << std::endl;
		exit(EXIT_FAILURE);
	}
	while (!input.eof()) {
		if (getline(input, parse)) {
			std::istringstream iss(parse);
			iss >> type;
			switch (type) {
				case '#':
				break;
				case 'v':
					iss >> a >> b >> c;
					this->points.push_back(vect(a, b, c));
				break;
				case 'f':
					iss >> a >> b >> c;
					this->faces.push_back(vect(a - 1, b - 1, c - 1));
				break;
				default:
					//white space
				break;
			}
		}
	}
	input.close();
}

void obj::writeData(std::string filename) {
	std::ofstream out(filename, std::ofstream::out);
	int i;
	for (i = 0; i < (signed)this->points.size(); i++) {
		out << "v " << this->points.at(i).getArr()[0] << " " << this->points.at(i).getArr()[1] << " " << this->points.at(i).getArr()[2] << std::endl;
	}
	out << std::endl;
	for (i = 0; i < (signed)this->faces.size(); i++) {
		out << "f " << (int)(this->faces.at(i).getArr()[0] + 1) << " " << (int)(this->faces.at(i).getArr()[1] + 1) << " " << (int)(this->faces.at(i).getArr()[2] + 1) << std::endl;
	}
	out.close();
}

void obj::storeData(){
	unsigned int i = 0;
	unsigned int j = 0;
	for (i = 0; i < this->faces.size(); i++) {
		//populate list of edges
		//populate list of triangles
		//have the two point to each other
	}
}
