//test CImg, eigen compatibility
#include "CImg.h"
#include <vector>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef cimg_imagepath
#define cimg_imagepath "C:/Users/Billy/Documents/cmake_test/framework/"
#endif

void doSmth()
{
	using namespace cimg_library;

	//CImg<uchar> img;
	CImg<uchar> img;
	const char* file_i = cimg_option("-i", cimg_imagepath "moon.jpg", "Input image");
	//img.load("C:\\Users\\Billy\\Documents\\cmake_test\\framework\\cimg_proj\\moon.jpg");
	img.load("moon.jpg");
	img.save("C:\\Users\\Billy\\Documents\\cmake_test\\framework\\cimg_proj\\moon2.png");
	//const char* file_i = cimg_option("-i", cimg_imagepath "parrot.ppm", "Input image");
}

int main()
{
	doSmth();

	return 0;
}


