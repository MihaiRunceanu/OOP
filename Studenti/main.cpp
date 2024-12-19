#include <QApplication>
#include <QPushButton>
#include "test.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Teste teste;
    teste.TestAll();
    Repository repo{"C:\\Scoala\\POO\\practic-Studenti\\Studenti\\studenti.txt"};
    Service ctr{repo};
    GUI gui{ctr};
    gui.show();

    return QApplication::exec();
}
