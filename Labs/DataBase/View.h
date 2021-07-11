#ifndef View_h
#define View_h

#include <QWidget>
#include <QPushButton>
#include <QListWidget>

class ViewUsers : public QWidget
{
	Q_OBJECT;

protected:
	QBrush* brush;
	QPalette* palette;

	QTextCodec* codec;

	QListWidget* outputEdit;
	
	QWidget* MenuWindow;

	QPushButton* DeletButton;
	QPushButton* BackButton;

public:
	ViewUsers(QWidget* Menu = 0);

public slots:
	void Begin();
	void Delet1();
	void Delet2();
	void Back();
};


#endif
