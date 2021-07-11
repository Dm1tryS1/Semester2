#include "figura.h"
#include <math.h>

void Figura::move(float Alpha, QPainter* Painter)
{
    dx = halflen * cos(Alpha);
    dy = halflen * sin(Alpha);
    draw(Painter);   // необходим сложный полиморфизм!
}

void MyLine::draw(QPainter* Painter)
{
    Painter->drawLine(x + dx, y + dy, x - dx, y - dy);
}

void MyQube::draw(QPainter* Painter)
{
    Painter->drawLine(x + dx, y + dy, x - dx, y - dy);
    Painter->drawLine(x - dx, y - dy, x - dx- 2 * dy, y - dy + 2 * dx);
    Painter->drawLine(x - dx - 2 * dy, y - dy + 2 * dx, x + dx - 2 * dy, y + dy + 2 * dx);
    Painter->drawLine(x + dx, y + dy, x + dx - 2 * dy, y + dy + 2 * dx);
}


void MyRect::draw(QPainter* Painter)
{
    Painter->drawLine(x + dx, y + dy, x - dx, y - dy);
    Painter->drawLine(x - dx, y - dy, x - dx - dy, y - dy + dx);
    Painter->drawLine(x - dx - dy, y - dy + dx, x + dx - dy, y + dy + dx);
    Painter->drawLine(x + dx, y + dy, x + dx - dy, y + dy + dx);
}