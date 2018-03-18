#include "obj.h"

int main(int argc, char** argv) {

	obj* object = new obj();

	if (argc < 4) {
		std::cout << "usage: prog04 input output numIterations" << std::endl;
		exit(EXIT_FAILURE);
	}

	object->readData(argv[1]);

	object->writeData(argv[2]);
	return 0;
}