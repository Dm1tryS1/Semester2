#ifndef AREA_H 
#define AREA_H

#include "figura.h"
#include <QWidget> 
#include <QTimer>

class Area : public QWidget
{
    int myTimer; // идентификатор таймера
    float alpha1; // угол поворота
    float alpha2;
    float alpha3;
    int check1;
    int check2;
    int check3;

    public:
        Area(QWidget* parent = 0);
        ~Area();
        MyLine* myline;
        MyRect* myrect;
        MyQube* myqube;
    protected:
        //	обработчики событий
        void paintEvent(QPaintEvent* event);
        void timerEvent(QTimerEvent* event);
        void showEvent(QShowEvent* event);
        void hideEvent(QHideEvent* event);
};

#endif
