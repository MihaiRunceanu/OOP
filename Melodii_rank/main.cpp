#include "test.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    Test tests;
    tests.testAll();

    QApplication app(argc, argv);
    Repository repo{"C:\\Scoala\\POO\\practic-Melodii_rank\\Melodii_rank\\songs.txt"};
    Service service{repo};

    MainWindow gui(service);
    gui.show();

    return QApplication::exec();
}
