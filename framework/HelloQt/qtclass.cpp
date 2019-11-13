#include "qtclass.hpp"
#include <iostream>

void RunClass::runThis()
{
	std::cout << "This class is running @" __FUNCTION__<< std::endl;
}
