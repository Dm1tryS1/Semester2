#ifndef LR10_h
#define LR10_h

#include <QWidget>
#include <QLabel> //метка
#include <QLineEdit> //ввод
#include <QListWidget>//вывод
#include <QPushButton> //кнопка
#include <QFrame>//рамка

class Win : public QWidget
{
    Q_OBJECT

    protected:
        QTextCodec* codec;

        QLabel* inputLabel;
        QLabel* outputLabel;

        QLineEdit* inputEdit;
        QListWidget* outputEdit;

        QPushButton* AddButton;
        QPushButton* ViewButton;
        QPushButton* DeletButton;
        QPushButton* MaxButton;
        QPushButton* CheckButton;
        QPushButton* ExitButton;

        QFrame* frame;

    public:
        Win(QWidget* parent = 0);

    public slots:
        void Begin();
        void Add();
        void Delet1();
        void Delet2();
        void Check();
        void Max();
        void View();
        void Exit();
};

/***************************************************************************************/

class TElement
{
public:
    TElement* pre, * sec;
    TElement() { pre = sec = NULL; }
    virtual ~TElement() {}
    virtual QString Print() = 0;
};

class TSpisok
{
    public:
        TElement* first, * last, * element;
    public:
        TSpisok() { first = last = element = NULL; }
        ~TSpisok();

        void AddEl(TElement* e);
        void DeletEl(int ind);
        bool CheckEl(QString str);

        TElement* Delet();
        TElement* First() { return element = first; }
        TElement* Next() { return element = element->sec; }
        TElement* Last() { return element = last; }
        TElement* Previous() { return element = element->pre; }
};

class TMySpisok : public TSpisok
{
    public:
        int maxel();
};

class TNum :public TElement
{
    public:
        int num;
        TNum(int n) :TElement(), num(n) {}
        ~TNum() {}
        QString Print() { QString str = QString::number(num); return str; }
};


class TChar :public TElement
{
    public: QString ch;
        TChar(QString c) :TElement(), ch(c) {}
        ~TChar() {}
        QString Print() { QString str = ch; return str; }
};

#endif