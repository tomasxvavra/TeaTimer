#include "gui/mainwindow.h"
#include <QApplication>

static constexpr auto APP_NAME = "TeaTimer";
static constexpr auto APP_VER = "0.0.1";

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QApplication::setApplicationName(APP_NAME);
	QApplication::setApplicationVersion(APP_VER);

	MainWindow w;
	w.show();

	return a.exec();
}
