#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Repository repo("C:\\Scoala\\POO\\practic-Tractoare\\Tractoare\\tractoare.txt");
    Service serv(repo);
    MainWindow main_window(serv);

    main_window.show();

    return QApplication::exec();
}
