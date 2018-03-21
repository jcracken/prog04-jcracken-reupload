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
	unsigned int k = 0;
	unsigned int firstedgeExist, secedgeExist, thirdedgeExist;
	bool firstexist = false;
	bool secexist = false;
	bool thirdexist = false;
	for (i = 0; i < this->faces.size(); i++) {
		this->triangles.push_back(triangle());
		this->triangles.at(k).populatePoint(this->points.at(this->faces.at(i).getArr()[0]));
		this->triangles.at(k).populatePoint(this->points.at(this->faces.at(i).getArr()[1]));
		this->triangles.at(k).populatePoint(this->points.at(this->faces.at(i).getArr()[2]));
		for (j = 0; j < this->edges.size(); j++) {
			//first and second point
			if (this->edges.at(j).isSame(this->points.at(this->faces.at(i).getArr()[0]), this->points.at(this->faces.at(i).getArr()[1]))) {
				firstexist = true;
				firstedgeExist = j;
			}
			//second and third point
			if (this->edges.at(j).isSame(this->points.at(this->faces.at(i).getArr()[1]), this->points.at(this->faces.at(i).getArr()[2]))) {
				secexist = true;
				secedgeExist = j;
			}
			//first and third point
			if (this->edges.at(j).isSame(this->points.at(this->faces.at(i).getArr()[0]), this->points.at(this->faces.at(i).getArr()[2]))) {
				thirdexist = true;
				thirdedgeExist = j;
			}
		}
		if (!firstexist) {
			edge e = edge();
			e.populatePoint(this->points.at(this->faces.at(i).getArr()[0]));
			e.populatePoint(this->points.at(this->faces.at(i).getArr()[1]));
			e.populateTriangle(&this->triangles.at(k));
			this->edges.push_back(e);
		}
		else {
			this->edges.at(firstedgeExist).populateTriangle(&this->triangles.at(k));
		}
		if (!secexist) {
			edge e = edge();
			e.populatePoint(this->points.at(this->faces.at(i).getArr()[1]));
			e.populatePoint(this->points.at(this->faces.at(i).getArr()[2]));
			e.populateTriangle(&this->triangles.at(k));
			this->edges.push_back(e);
		}
		else {
			this->edges.at(secedgeExist).populateTriangle(&this->triangles.at(k));
		}
		if (!thirdexist) {
			edge e = edge();
			e.populatePoint(this->points.at(this->faces.at(i).getArr()[0]));
			e.populatePoint(this->points.at(this->faces.at(i).getArr()[2]));
			e.populateTriangle(&this->triangles.at(k));
			this->edges.push_back(e);
		}
		else {
			this->edges.at(thirdedgeExist).populateTriangle(&this->triangles.at(k));
		}
		firstexist = false;
		secexist = false;
		thirdexist = false;
	}
}
