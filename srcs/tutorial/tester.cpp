//this is only for CMake tutorial

#include <iostream>
#include "testheader1.h"
#include "testheader2.hpp"

int main(){

    std::cout<< "Hello CMake!"<<std::endl;

	std::cout << "Does this change the source only?" << std::endl;

	//third level?

	std::cout << hi_from_header1() << std::endl;
	std::cout << hi_from_header2() << std::endl;


	std::cout << "Program finished" << std::endl;

    return 0;
}