#include "Object.h"
#include <iostream>
namespace UxDeepEye {
	Object::Object() {
		std::cout << "Object::Object()" << std::endl;
	}
	
	Object::~Object() {
		std::cout << "Object::~Object()" << std::endl;
	}
}