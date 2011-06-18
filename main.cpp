#include <stdio.h>
#include <QtGui/QApplication>

#include <QtCore/QVariant>

#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeView>

#include "Drummer.hpp"
using namespace poumtchak;

int main(int argc, char *argv[])
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
    view->rootContext()->setContextProperty("screenWidth", 400);
    view->rootContext()->setContextProperty("screenHeight", 100);
    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    view->setSource(QUrl("qrc:/main.qml"));

    view->showFullScreen();

    printf("width %d, height %d\n", view->width(), view->height());

    printf("Showtime !\n");
    return app.exec();
}
