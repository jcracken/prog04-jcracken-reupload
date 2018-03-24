#include "obj.h"

int main(int argc, char** argv) {

	obj* object = new obj();
	int i = 0;

	if (argc < 4) {
		std::cout << "usage: prog04 input output numIterations" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (std::stoi(argv[3]) <= 0){
		std::cout << "invalid number of iterations" << std::endl;
		exit(EXIT_FAILURE);
	}

	object->readData(argv[1]);

	object->storeData();

	for (i = 0; i < std::stoi(argv[3]); i++) {
		object->subdivide();
	}

	object->writeData(argv[2]);

	return 0;
}