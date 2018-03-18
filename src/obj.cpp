#include "obj.h"

void obj::readData(std::string filename) {
	std::ifstream input(filename, std::ifstream::in);
	std::string parse;
	float temp[3];
	char type = '\0';
	if (!(input.is_open())) {
		std::cout << "invalid filename" << std::endl;
		exit(EXIT_FAILURE);
	}
	while (!input.eof()) {
		if (getline(input, parse)) {
			type = parse.at(0);
			std::istringstream iss(parse);
			switch (type) {
				case '#':
				break;
				case 'v':
					iss >> temp[0];
					iss >> temp[1];
					iss >> temp[2];
					this->points.push_back(vect(temp[0], temp[1], temp[2]));
				break;
				case 'f':
					iss >> temp[0];
					iss >> temp[1];
					iss >> temp[2];
					this->faces.push_back(vect(temp[0] - 1, temp[1] - 1, temp[2] - 1));
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
	for (i = 0; i < this->points.size(); i++) {
		out << "v " << this->points.at(i).getArr[0] << " " << this->points.at(i).getArr[1] << " " << this->points.at(i).getArr[2] << std::endl;
	}
	out << std::endl;
	for (i = 0; i < this->faces.size(); i++) {
		out << "f " << (int)(this->faces.at(i).getArr[0] + 1) << " " << (int)(this->faces.at(i).getArr[1] + 1) << " " << (int)(this->faces.at(i).getArr[2] + 1) << std::endl;
	}
	out.close();
}
