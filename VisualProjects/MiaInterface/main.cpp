#include "MiaInterface.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MiaInterface w;
	w.show();

	return a.exec();
}
