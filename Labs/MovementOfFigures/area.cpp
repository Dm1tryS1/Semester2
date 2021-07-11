#include "area.h"
#include <QTimerEvent>

Area::Area(QWidget* parent) :QWidget(parent)
{
    setFixedSize(QSize(500, 300)); // фиксируем размер Холста
    myline = new MyLine(70, 150, 50);  // создаем объект Линия
    myrect = new MyRect(250, 150, 60); // создаем объект Квадрат
    myqube = new MyQube(430,150,30);
    alpha1 = 0;
    alpha2 = 0;
    alpha3 = 0;
    check1 = 1;
    check2 = 1;
    check3 = 1;
}

void Area::showEvent(QShowEvent*)
{
    myTimer = startTimer(70);      // включаем таймер
}

void Area::paintEvent(QPaintEvent*)
{
    QPainter painter(this);    // создаем контент рисования на Холсте
    painter.setPen(QPen(Qt::red, 5));
    myline->move(alpha1, &painter); // рисуем Линию
    painter.setPen(QPen(Qt::yellow, 5));
    myrect->move(alpha2, &painter); // рисуем Прямоугольник
    painter.setPen(QPen(Qt::green, 5));
    myqube->move(alpha3, &painter);  // рисуем Квадрат
}

void Area::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == myTimer) // если наш таймер
    {
        if ((alpha1 < 0.8) && (check1 == 1))
            alpha1 = alpha1 + 0.1;
        else
            check1 = 0;

        if ((alpha1 > -0.8) && (check1 == 0))
            alpha1 = alpha1 - 0.1;
        else
            check1 = 1;

        if ((alpha2 < 0.3) && (check2 == 1))
            alpha2 = alpha2 + 0.1;
        else
            check2 = 0;

        if ((alpha2 > -0.3) && (check2 == 0))
            alpha2 = alpha2 - 0.1;
        else
            check2 = 1;

        if ((alpha3 < 0.5) && (check3 == 1))
            alpha3 = alpha3 + 0.1;
        else
            check3 = 0;

        if ((alpha3 > -0.5) && (check3 == 0))
            alpha3 = alpha3 - 0.1;
        else
            check3 = 1;

        update();        // обновить внешний вид
    }
    else
        QWidget::timerEvent(event);  // иначе передать далее
}

void Area::hideEvent(QHideEvent*)
{
    killTimer(myTimer);  // выключить таймер
}

Area::~Area()
{
    delete myline;
    delete myrect;
    delete myqube;
}