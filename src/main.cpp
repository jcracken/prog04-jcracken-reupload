#include "obj.h"

int main(int argc, char** argv) {

	obj* object = new obj(); //object used for storage and subdivision
	int i = 0; //for numIterations

	if (argc < 4) {
		std::cout << "usage: prog04 input output numIterations" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (std::stoi(argv[3]) <= 0){ //checking to make sure numIterations is above 0
		std::cout << "invalid number of iterations" << std::endl;
		exit(EXIT_FAILURE);
	}

	object->readData(argv[1]); //read in the data

	object->storeData(); //store it in new data structure

	for (i = 0; i < std::stoi(argv[3]); i++) { //run subdivision for numIterations
		object->subdivide();
	}

	object->writeData(argv[2]); //write the data to output file

	delete object; //free memory

	return 0;
}