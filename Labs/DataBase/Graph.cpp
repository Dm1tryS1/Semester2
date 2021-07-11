#include "Graph.h"
#include <QVBoxLayout>
#include <QPainter>
#include <QFile>

int fun(int x)
{
    struct zap
    {
        QString secondname;
        QString firstname;
        QString patronymic;
        QString phonenumber;
        QString balance;
        QString year;
    } z;

    int y=0;
    bool ok;

    QString str;

    QFile F("DataBase.dat");

    QDataStream streamF(&F);
    streamF.setVersion(QDataStream::Qt_5_3);
    F.open(QIODevice::ReadOnly);

    while (!F.atEnd())
    {
        streamF >> z.secondname >> z.firstname >> z.patronymic >> z.phonenumber >> z.balance >> z.year;
        if (z.year.toInt(&ok, 10) == x)
            y++;
    }
    return y;
}

Area::Area(QWidget* parent) :QWidget(parent)
{
    setFixedSize(QSize(500, 350));
    this->setStyleSheet("background-color: white;");
}

GraphUser::GraphUser(QWidget* Menu) : QWidget(0)
{
    MenuWindow = Menu;

    codec = QTextCodec::codecForName("Windows-1251");

    setWindowTitle(codec->toUnicode("График"));
    setWindowIcon(QIcon("Icon.jpg"));
    this->resize(600, 350);

    brush = new QBrush;
    palette = new QPalette;
    brush->setTextureImage(QImage("BackGround.png"));
    palette->setBrush(QPalette::Window, *brush);
    this->setPalette(*palette);

    codec = QTextCodec::codecForName("Windows-1251");

    area = new Area(this);

    BuildButton = new QPushButton(codec->toUnicode("Построить"), this);
    BuildButton->setFixedSize(90, 30);
    BuildButton->setStyleSheet(QString("font-size: %1px").arg(14));

    BackButton = new QPushButton(codec->toUnicode("Назад"), this);
    BackButton->setFixedSize(90, 30);
    BackButton->setStyleSheet(QString("font-size: %1px").arg(14));

    QVBoxLayout* layout1 = new QVBoxLayout();
    layout1->addStretch();
    layout1->addWidget(BuildButton);
    layout1->addStretch();
    layout1->addWidget(BackButton);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(area);
    layout->addLayout(layout1);

    connect(BuildButton, SIGNAL(clicked(bool)), this, SLOT(Build()));
    connect(BackButton, SIGNAL(clicked(bool)), this, SLOT(Back()));
};

void GraphUser::Build()
{
    area->update();
}

void Area::paintEvent(QPaintEvent*)
{
    struct zap
    {
        QString secondname;
        QString firstname;
        QString patronymic;
        QString phonenumber;
        QString balance;
        QString year;
    } z;

    struct coord
    {
        int x;
        int y;
    };
    coord MyCoord[200];

    int xm = 500, ym = 350;
    float dx = 1;
    float xn = 2100, xk = 1990;
    int n;
    float x, y;
    int xs, ys;
    float mx, my;
    float dx1, dy1;
    float Fmax, Fmin;

    bool ok;

    QString year;
    QString str;

    QFile F("DataBase.dat");

    QPainter painter(this);

    painter.setPen(QPen(Qt::green, 4));
    QPoint pt(0, 0);
    QSize size(500, 350);
    QRect frame(pt, size);
    painter.drawRect(frame); 

    QDataStream streamF(&F);
    streamF.setVersion(QDataStream::Qt_5_3);
    F.open(QIODevice::ReadOnly);  

    while (!F.atEnd())
    {
        streamF >> z.secondname >> z.firstname >> z.patronymic >> z.phonenumber >> z.balance >> z.year;
        if (z.year.toInt(&ok, 10) < xn)
            xn = z.year.toInt(&ok, 10);
        if (z.year.toInt(&ok, 10) > xk)
            xk = z.year.toInt(&ok, 10);
    }

    n = xk - xn;

    x = xn;
    y = fun(x);
    Fmax = y, Fmin = y;
    for (int i = 1; i < n; i++)
    {
        x = x + dx;
        y = fun(x);
        if (y > Fmax) 
            Fmax = y;
        if (y < Fmin) 
            Fmin = y;
    }
    
    painter.setPen(QPen(Qt::red, 3));

    xs = 40;  ys = ym - xs;    
    mx = (xm - xs * 2) / (xk - xn);
    my = (ym - xs * 2) / (Fmax - Fmin);

    x = xn;
    for (int i = 0; i < n+1; i++)
    {
        MyCoord[i].x = ((x - xn) * mx) + xs;
        MyCoord[i].y = ((Fmin - fun(x))* my) + ys;
        x = x + dx;
    }

    for (int i = 0; i < n; i++)
        painter.drawLine(MyCoord[i].x, MyCoord[i].y, MyCoord[i+1].x, MyCoord[i+1].y);

    painter.setPen(QPen(Qt::blue, 1));

    x = xn;
    dx1 = 4;
    do
    {
        QPoint pointx((x - xn)* mx + xs - 13, ys + 5);
        str.setNum(x);
        painter.drawText((x - xn)* mx + xs - 13, ys + 5,30,30, Qt::AlignHCenter | Qt::AlignVCenter,str);
        painter.drawLine((x - xn)* mx + xs, ym - xs, (x - xn)* mx + xs, xs);
        x = x + dx1;
    } while (x < xk + 0.1);

    y = Fmin;
    dy1 = (Fmax - Fmin) / Fmax;
    do
    {
        str.setNum(y);
        painter.drawText(5, (-(y - Fmin) * my) + ys-15, 30, 30, Qt::AlignHCenter | Qt::AlignVCenter, str);
        painter.drawLine(1 + xs, (-(y - Fmin) * my) + ys, xm - xs, (-(y - Fmin) * my) + ys);
        y = y + dy1;
    } while (y < Fmax + 0.1);
}

void GraphUser::Back()
{
    this->hide();
    MenuWindow->show();
}
