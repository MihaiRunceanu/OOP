#include <QApplication>

#include "test.h"
#include "gui.h"

int main(int argc, char *argv[]) {
    Tests test;
    test.test_all();

    QApplication a(argc, argv);
    Repository repo("C:\\Scoala\\POO\\practic-Tasks\\Tasks\\tasks.txt");
    Service service(repo);
    GUI gui(service);
    gui.show();

    return QApplication::exec();
}
