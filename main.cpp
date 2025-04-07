#include "mainwindow.h"
#include "communicationmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    CommunicationManager manager(w);
    w.show();
    return a.exec();
}
