#include <QApplication>

#include "test.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    Test tests;
    tests.testAll();

    QApplication a(argc, argv);

    Repository repo("C:\\Scoala\\POO\\practic-Melodii_tipuri\\Melodii-tipuri\\melodii.txt");
    Service service(repo);
    MainWindow gui(service);

    gui.show();

    return QApplication::exec();
}
