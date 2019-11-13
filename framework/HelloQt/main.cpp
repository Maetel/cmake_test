#include <qcoreapplication.h>
#include "qtclass.hpp"

int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);
	RunClass runThis;
	runThis.runThis();
	return app.exec();
}