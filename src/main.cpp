#include <stdio.h>
#include <QtGui/QApplication>

#include <QtCore/QVariant>

#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeView>

#include "Mixer.hpp"
using namespace poumtchak;

int main(int argc, char *argv[])
{
    printf("Hello MeeGo !\n");

    QApplication app(argc, argv);
    app.setApplicationName("Poumtchak");

    QDeclarativeView* view = new QDeclarativeView;

    printf("Loading samples...\n");
    Mixer mixer;
    mixer.initialize();
    mixer.load_samples();
    mixer.start();
    printf("Done !\n");

    view->rootContext()->setContextProperty("mixer", &mixer);
    view->rootContext()->setContextProperty("screenWidth", 800);
    view->rootContext()->setContextProperty("screenHeight", 600);
    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    view->setSource(QUrl("qrc:/qml/screen.qml"));

//    view->showFullScreen();
    view->show();

    printf("Showtime !\n");
    return app.exec();
}
