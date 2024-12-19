#include <QtWidgets/QApplication>
#include "test.h"
#include "service.h"
#include "gui.h"

int main(int argc, char *argv[])
{
    Test t;
    t.runTests();

    Valid v;
    Repo r{ "C:\\Scoala\\POO\\practic-X0\\X0\\jocuri.txt" };
    Service s{ r, v };

    QApplication a(argc, argv);

    JocGUI gui{ s };
    gui.show();

    return a.exec();
}
