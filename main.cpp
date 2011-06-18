
#include <stdio.h>
#include <QtGui/QApplication>

#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeView>

#include "Drummer.hpp"
using namespace poumtchak;

int main(int argc, char** argv)
{
	printf("Hello MeeGo !\n");

	QApplication app(argc, argv);
	app.setApplicationName("Poumtchak");

	QDeclarativeView* view = new QDeclarativeView;

	printf("Loading samples...");
	Drummer drummer;
	printf("Done !\n");

	// Register our object with the context...
	view->rootContext()->setContextProperty("drummer", &drummer);
	view->setSource(QUrl("main.qml"));

	view->show();

	printf("Showtime !\n");
	return app.exec();
}
