#include <QApplication>
#include "Menu.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Menu Menu(0);
    Menu.show();

    return app.exec();
}