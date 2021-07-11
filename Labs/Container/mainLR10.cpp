#include <QApplication>
#include "LR10.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Win Win(0);
    Win.show();
    return app.exec();
}
