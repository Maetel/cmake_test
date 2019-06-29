//this is only for CMake tutorial

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <iostream>

__global__ void cuda_hello() {
	printf("Hello World from GPU!\n");
	//std::cout << "what" << std::endl;	//nvcc compile error!
}

int main() {
    cuda_hello << <1, 1 >> > ();
	//printf("hi");

	std::cout << "what" << std::endl;

	return 0;
}