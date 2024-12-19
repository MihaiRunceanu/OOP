#include "gui.h"
#include "test.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vector<student>stud;
    teste t;
    t.run();
    repo rep{"C:\\Scoala\\POO\\practic-Studenti2\\Studenti2\\studenti.txt"};
    service serv{ rep };
    gui w{ serv };
    w.show();
    return a.exec();
}
