
#include "test.h"

#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto repo = Repository{"C:\\Scoala\\POO\\practic-Produse\\Produse\\produse.txt"};
    auto serv = Service{repo};
    auto gui = GUI{serv};

    Test test;

    gui.show();
    return a.exec();
}

