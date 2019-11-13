#include "includes.h"

//using Qt
//PATH=%PATH%;C:\Qt\5.12.5\msvc2017_64\bin

int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);
	
	//prepare two images
	QString dirPath("c:/work/playground/");
	QImage image_l(QString("%1%2").arg(dirPath).arg("testImage1.jpg"));
	QImage image_r(QString("%1%2").arg(dirPath).arg("testImage2.jpg"));
	image_l = image_l.convertToFormat(QImage::Format_Grayscale8);
	image_r = image_r.convertToFormat(QImage::Format_Grayscale8);

	//debug
	if(0){
		image_r.save(QString("%1%2").arg(dirPath).arg("testImage.jpg"));
	}

	ImageAlg alg;

	double NCCval = -1.f;
	{
		_TIMER("NCC : ");
		NCCval = alg.NCC(&image_l, &image_r);
	}
	
	double ZNCCval = -1.f;
	{
		_TIMER("ZNCC : ");
		ZNCCval = alg.ZNCC(&image_l, &image_r);
	}
	

	{
		using namespace std;
		cout << "NCC val : " << NCCval << endl;
		cout << "ZNCC val : " << ZNCCval << endl;
	}
	

	return app.exec();
}