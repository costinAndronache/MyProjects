#include "mainwindow.h"
#include <QApplication>
#include "ApiComunicator.h"

int main(int argc, char *argv[])
{
    ApiComunicator::sharedInstance()->connectToServerAndPort("127.0.0.1", 2277);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
