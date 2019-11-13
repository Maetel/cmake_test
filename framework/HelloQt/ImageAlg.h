#ifndef HELLOQT_IMAGEALG_H
#define HELLOQT_IMAGEALG_H

//#include <qimage.h>

class QImage;

class ImageAlg
{
public:
	//Normalize Cross Correlation
	double NCC(QImage const* input1, QImage const* input2) const;

	//Zero Normalized Cross Correlation
	double ZNCC(QImage const* input1, QImage const* input2) const;
};


#endif //!HELLOQT_IMAGEALG_H