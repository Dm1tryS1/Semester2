#ifndef win_h
#define win_h
#include "area.h" 
#include <QWidget> 
#include <QTextCodec> 
#include <QPushButton>

class Window : public QWidget
{
protected:
    QTextCodec* codec;
    Area* area;         // ������� ����������� �������
    QPushButton* btn;
public:
    Window();
};
#endif

