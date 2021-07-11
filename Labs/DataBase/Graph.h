#ifndef Graph_h
#define Graph_h

#include <QWidget> 
#include <QTextCodec> 
#include <QPushButton>

class Area : public QWidget
{
    public:
        Area(QWidget* parent = 0);
    protected:
        void paintEvent(QPaintEvent*);
};

class GraphUser: public QWidget
{
    Q_OBJECT;

    protected:
        QBrush* brush;
        QPalette* palette;

        QTextCodec* codec;

        QWidget* MenuWindow;

        Area* area;         // область отображения рисунка
        QPushButton* BackButton;
        QPushButton* BuildButton;
    public:
        GraphUser(QWidget* Menu = 0);

    public slots:
        void Build();
        void Back();
};

#endif
