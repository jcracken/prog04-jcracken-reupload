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
	unsigned int m = 0;
	unsigned int firstedgeExist = 0, secedgeExist = 0, thirdedgeExist = 0;
	bool firstexist = false;
	bool secexist = false;
	bool thirdexist = false;
	bool pointOne = false;
	bool pointTwo = false;

	this->edges.clear();
	this->triangles.clear();
	this->pointConns.clear();

	for (i = 0; i < this->points.size(); i++) {
		std::vector<int> dummy(1, -1);
		pointConns.push_back(dummy);
	}

	for (i = 0; i < this->faces.size(); i++) {

		for (m = 0; m < this->pointConns.at(this->faces.at(i).getArr()[0]).size(); m++) {
			if (this->pointConns.at(this->faces.at(i).getArr()[0]).at(m) == this->faces.at(i).getArr()[1]) pointOne = true;
			if (this->pointConns.at(this->faces.at(i).getArr()[0]).at(m) == this->faces.at(i).getArr()[2]) pointTwo = true;
		}
		if (!pointOne) this->pointConns.at(this->faces.at(i).getArr()[0]).push_back(this->faces.at(i).getArr()[1]);
		if (!pointTwo) this->pointConns.at(this->faces.at(i).getArr()[0]).push_back(this->faces.at(i).getArr()[2]);
		pointOne = false;
		pointTwo = false;

		for (m = 0; m < this->pointConns.at(this->faces.at(i).getArr()[1]).size(); m++) {
			if (this->pointConns.at(this->faces.at(i).getArr()[1]).at(m) == this->faces.at(i).getArr()[0]) pointOne = true;
			if (this->pointConns.at(this->faces.at(i).getArr()[1]).at(m) == this->faces.at(i).getArr()[2]) pointTwo = true;
		}
		if (!pointOne) this->pointConns.at(this->faces.at(i).getArr()[1]).push_back(this->faces.at(i).getArr()[0]);
		if (!pointTwo) this->pointConns.at(this->faces.at(i).getArr()[1]).push_back(this->faces.at(i).getArr()[2]);
		pointOne = false;
		pointTwo = false;

		for (m = 0; m < this->pointConns.at(this->faces.at(i).getArr()[2]).size(); m++) {
			if (this->pointConns.at(this->faces.at(i).getArr()[2]).at(m) == this->faces.at(i).getArr()[1]) pointOne = true;
			if (this->pointConns.at(this->faces.at(i).getArr()[2]).at(m) == this->faces.at(i).getArr()[0]) pointTwo = true;
		}
		if (!pointOne) this->pointConns.at(this->faces.at(i).getArr()[2]).push_back(this->faces.at(i).getArr()[1]);
		if (!pointTwo) this->pointConns.at(this->faces.at(i).getArr()[2]).push_back(this->faces.at(i).getArr()[0]);
		pointOne = false;
		pointTwo = false;

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
			e.populatePoint(&(this->points.at(this->faces.at(i).getArr()[0])));
			e.populatePoint(&(this->points.at(this->faces.at(i).getArr()[1])));
			e.populateTriangle(&this->triangles.at(k));
			this->edges.push_back(e);
		}
		else {
			this->edges.at(firstedgeExist).populateTriangle(&this->triangles.at(k));
		}
		if (!secexist) {
			edge e = edge();
			e.populatePoint(&(this->points.at(this->faces.at(i).getArr()[1])));
			e.populatePoint(&(this->points.at(this->faces.at(i).getArr()[2])));
			e.populateTriangle(&this->triangles.at(k));
			this->edges.push_back(e);
		}
		else {
			this->edges.at(secedgeExist).populateTriangle(&this->triangles.at(k));
		}
		if (!thirdexist) {
			edge e = edge();
			e.populatePoint(&(this->points.at(this->faces.at(i).getArr()[0])));
			e.populatePoint(&(this->points.at(this->faces.at(i).getArr()[2])));
			e.populateTriangle(&this->triangles.at(k));
			this->edges.push_back(e);
		}
		else {
			this->edges.at(thirdedgeExist).populateTriangle(&this->triangles.at(k));
		}
		firstexist = false;
		secexist = false;
		thirdexist = false; 
		k++;
	}
	for (i = 0; i < pointConns.size(); i++) {
		pointConns.at(i).erase(pointConns.at(i).begin());
	}
}

void obj::subdivide() {
	std::vector<vect> newPoints;
	std::vector<vect> newFaces;

	unsigned int i, j;

	for (i = 0; i < this->points.size(); i++) { //even vertices
		float temp[3] = { 0 };

	}

	for (i = 0; i < this->edges.size(); i++) { //odd vertices
		float* temp = this->edges.at(i).loopHelp();
		newPoints.push_back(vect(temp[0], temp[1], temp[2]));
	}

	//find out how to create the newFaces vector

	this->points.swap(newPoints);
	this->faces.swap(newFaces);
	this->storeData();
}
