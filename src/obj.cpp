#include "obj.h"

obj::obj() {
	//constructor
	triangles.reserve(1000);
	points.reserve(1000);
	faces.reserve(1000);
	edges.reserve(1000);
}

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
		this->triangles.at(k).populatePoint(&this->points.at(this->faces.at(i).getArr()[0]));
		this->triangles.at(k).populatePoint(&this->points.at(this->faces.at(i).getArr()[1]));
		this->triangles.at(k).populatePoint(&this->points.at(this->faces.at(i).getArr()[2]));
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
			e.populateTriangle(&(this->triangles.at(k)));
			this->edges.push_back(e);
			this->triangles.at(k).populateEdge(&(this->edges.at(this->edges.size() - 1)));
		}
		else {
			this->edges.at(firstedgeExist).populateTriangle(&(this->triangles.at(k)));
			this->triangles.at(k).populateEdge(&(this->edges.at(firstedgeExist)));
		}
		if (!secexist) {
			edge e = edge();
			e.populatePoint(&(this->points.at(this->faces.at(i).getArr()[1])));
			e.populatePoint(&(this->points.at(this->faces.at(i).getArr()[2])));
			e.populateTriangle(&(this->triangles.at(k)));
			this->edges.push_back(e);
			this->triangles.at(k).populateEdge(&(this->edges.at(this->edges.size() - 1)));
		}
		else {
			this->edges.at(secedgeExist).populateTriangle(&(this->triangles.at(k)));
			this->triangles.at(k).populateEdge(&(this->edges.at(secedgeExist)));
		}
		if (!thirdexist) {
			edge e = edge();
			e.populatePoint(&(this->points.at(this->faces.at(i).getArr()[0])));
			e.populatePoint(&(this->points.at(this->faces.at(i).getArr()[2])));
			e.populateTriangle(&(this->triangles.at(k)));
			this->edges.push_back(e);
			this->triangles.at(k).populateEdge(&(this->edges.at(this->edges.size() - 1)));
		}
		else {
			this->edges.at(thirdedgeExist).populateTriangle(&(this->triangles.at(k)));
			this->triangles.at(k).populateEdge(&(this->edges.at(thirdedgeExist)));
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
	float weight = 0.0;

	for (i = 0; i < this->points.size(); i++) { //even vertices
		float temp[3] = { 0 };
		if (this->pointConns.at(i).size() == 2) {
			temp[0] = (1.0 / 8.0) * (this->points.at(this->pointConns.at(i).at(0)).getArr()[0] + this->points.at(this->pointConns.at(i).at(1)).getArr()[0]) + (3.0 / 4.0) * this->points.at(i).getArr()[0];
			temp[1] = (1.0 / 8.0) * (this->points.at(this->pointConns.at(i).at(0)).getArr()[1] + this->points.at(this->pointConns.at(i).at(1)).getArr()[1]) + (3.0 / 4.0) * this->points.at(i).getArr()[1];
			temp[2] = (1.0 / 8.0) * (this->points.at(this->pointConns.at(i).at(0)).getArr()[2] + this->points.at(this->pointConns.at(i).at(1)).getArr()[2]) + (3.0 / 4.0) * this->points.at(i).getArr()[2];
		} else if (this->pointConns.at(i).size() == 3) {
			weight = (3.0 / 16.0);
			temp[0] = this->points.at(i).getArr()[0] * (1.0 - 3.0 * weight);
			temp[1] = this->points.at(i).getArr()[1] * (1.0 - 3.0 * weight);
			temp[2] = this->points.at(i).getArr()[2] * (1.0 - 3.0 * weight);
			for (j = 0; j < this->pointConns.at(i).size(); j++) {
				temp[0] = temp[0] + (this->points.at(this->pointConns.at(i).at(j)).getArr()[0]) * weight;
				temp[1] = temp[1] + (this->points.at(this->pointConns.at(i).at(j)).getArr()[1]) * weight;
				temp[2] = temp[2] + (this->points.at(this->pointConns.at(i).at(j)).getArr()[2]) * weight;
			}
		} else {
			weight = (3.0 / (8.0 * this->pointConns.at(i).size()));
			temp[0] = this->points.at(i).getArr()[0] * (1.0 - this->pointConns.at(i).size() * weight);
			temp[1] = this->points.at(i).getArr()[1] * (1.0 - this->pointConns.at(i).size() * weight);
			temp[2] = this->points.at(i).getArr()[2] * (1.0 - this->pointConns.at(i).size() * weight);
			for (j = 0; j < this->pointConns.at(i).size(); j++) {
				temp[0] = temp[0] + (this->points.at(this->pointConns.at(i).at(j)).getArr()[0]) * weight;
				temp[1] = temp[1] + (this->points.at(this->pointConns.at(i).at(j)).getArr()[1]) * weight;
				temp[2] = temp[2] + (this->points.at(this->pointConns.at(i).at(j)).getArr()[2]) * weight;
			}
		}
		newPoints.push_back(vect(temp[0], temp[1], temp[2]));
	}

	for (i = 0; i < this->edges.size(); i++) { //odd vertices
		float temp[3];
		this->edges.at(i).loopHelp(temp);
		newPoints.push_back(vect(temp[0], temp[1], temp[2]));
		this->edges.at(i).setOdd(newPoints.size() - 1);
	}

	//find out how to create the newFaces vector
	for (i = 0; i < this->triangles.size(); i++) {
		int pointA, pointB, pointC;
		for (j = 0; j < this->points.size(); j++) {
			if (this->points.at(j).comp((this->triangles.at(i).getPoint(0)))) {
				pointA = j;
			}
			else if (this->points.at(j).comp((this->triangles.at(i).getPoint(1)))) {
				pointB = j;
			}
			else if (this->points.at(j).comp((this->triangles.at(i).getPoint(2)))) {
				pointC = j;
			}
		}

		//pointA
		if (this->triangles.at(i).getEdge(0)->isPart(newPoints.at(pointA)) && this->triangles.at(i).getEdge(1)->isPart(newPoints.at(pointA))) {
			newFaces.push_back(vect(this->triangles.at(i).getEdge(0)->getOdd(), this->triangles.at(i).getEdge(1)->getOdd(), pointA));
		} else if (this->triangles.at(i).getEdge(0)->isPart(newPoints.at(pointA)) && this->triangles.at(i).getEdge(2)->isPart(newPoints.at(pointA))) {
			newFaces.push_back(vect(this->triangles.at(i).getEdge(0)->getOdd(), this->triangles.at(i).getEdge(2)->getOdd(), pointA));
		} else if (this->triangles.at(i).getEdge(1)->isPart(newPoints.at(pointA)) && this->triangles.at(i).getEdge(2)->isPart(newPoints.at(pointA))) {
			newFaces.push_back(vect(this->triangles.at(i).getEdge(1)->getOdd(), this->triangles.at(i).getEdge(2)->getOdd(), pointA));
		}

		//pointB
		if (this->triangles.at(i).getEdge(0)->isPart(newPoints.at(pointB)) && this->triangles.at(i).getEdge(1)->isPart(newPoints.at(pointB))) {
			newFaces.push_back(vect(this->triangles.at(i).getEdge(0)->getOdd(), this->triangles.at(i).getEdge(1)->getOdd(), pointB));
		}
		else if (this->triangles.at(i).getEdge(0)->isPart(newPoints.at(pointB)) && this->triangles.at(i).getEdge(2)->isPart(newPoints.at(pointB))) {
			newFaces.push_back(vect(this->triangles.at(i).getEdge(0)->getOdd(), this->triangles.at(i).getEdge(2)->getOdd(), pointB));
		}
		else if (this->triangles.at(i).getEdge(1)->isPart(newPoints.at(pointB)) && this->triangles.at(i).getEdge(2)->isPart(newPoints.at(pointB))) {
			newFaces.push_back(vect(this->triangles.at(i).getEdge(1)->getOdd(), this->triangles.at(i).getEdge(2)->getOdd(), pointB));
		}

		//pointC
		if (this->triangles.at(i).getEdge(0)->isPart(newPoints.at(pointC)) && this->triangles.at(i).getEdge(1)->isPart(newPoints.at(pointC))) {
			newFaces.push_back(vect(this->triangles.at(i).getEdge(0)->getOdd(), this->triangles.at(i).getEdge(1)->getOdd(), pointC));
		}
		else if (this->triangles.at(i).getEdge(0)->isPart(newPoints.at(pointC)) && this->triangles.at(i).getEdge(2)->isPart(newPoints.at(pointC))) {
			newFaces.push_back(vect(this->triangles.at(i).getEdge(0)->getOdd(), this->triangles.at(i).getEdge(2)->getOdd(), pointC));
		}
		else if (this->triangles.at(i).getEdge(1)->isPart(newPoints.at(pointC)) && this->triangles.at(i).getEdge(2)->isPart(newPoints.at(pointC))) {
			newFaces.push_back(vect(this->triangles.at(i).getEdge(1)->getOdd(), this->triangles.at(i).getEdge(2)->getOdd(), pointC));
		}

		newFaces.push_back(vect(this->triangles.at(i).getEdge(0)->getOdd(), this->triangles.at(i).getEdge(1)->getOdd(), this->triangles.at(i).getEdge(2)->getOdd()));
	}

	this->points.swap(newPoints);
	this->faces.swap(newFaces);
	this->storeData();
}
