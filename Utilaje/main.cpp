#include "mainwindow.h"
#include "test.h"
#include "repository.h"
#include "service.h"
#include "gui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Teste t;
    t.testAll();
    Repo r("C:\\Scoala\\POO\\practic-Utilaje\\Utilaje\\utilaje.txt");
    Service s(r);
    GUI g(s);
    g.show();
    return a.exec();
}
