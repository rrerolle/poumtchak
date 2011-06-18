
#include <QtGui/QApplication>

#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeView>

#include "Drummer.hpp"
#include "TchikiBoum.hpp"
using namespace poumtchak;

void test();

int main(int argc, char** argv)
{
	qDebug("Hello MeeGo !");

	QApplication app(argc, argv);
	app.setApplicationName("Poumtchak");

	QDeclarativeView* view = new QDeclarativeView;

	TchikiBoum boum;

	qDebug("Loading samples...");
	Drummer drummer;

	/*int i = boum.addLoop("samples/DRUMLOOP001_TECH_125_X_SC4.wav");
	boum.setReferenceLoop(i);
	boum.playLoop(i);

	boum.addLoop("samples/SNTHBASS001_TECH_125_A_SC4.wav");
	boum.addLoop("samples/SYNTH025_TECH_125_A_SC4(L).wav");*/

	test();

	// Register our object with the context...
	view->rootContext()->setContextProperty("drummer", &drummer);
	view->rootContext()->setContextProperty("tchikboum", &boum);
	view->setSource(QUrl("main.qml"));

	view->show();

	qDebug("Showtime !");
	return app.exec();
}
