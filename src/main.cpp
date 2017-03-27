#include "gui/mainwindow.h"
#include <QApplication>
#include "settings.h"

static constexpr auto ORG_NAME = "tomasxvavra";
static constexpr auto APP_NAME = "TeaTimer";
static constexpr auto APP_VER = "0.0.1";

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QApplication::setOrganizationName(ORG_NAME);
	QApplication::setApplicationName(APP_NAME);
	QApplication::setApplicationVersion(APP_VER);

	Settings s;
	MainWindow w;
	w.show();

	return a.exec();
}
