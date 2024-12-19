#include "mainwindow.h"

#include "gui.h"
#include "tests.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    OfertaRepository repo;
    WishList wishlist;
    OfertaService service{repo, wishlist};

    tests t;
    t.all_tests();

    GUI gui{service};
    gui.show();

    return a.exec();
}
