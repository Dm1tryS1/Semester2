#ifndef SearchName_h
#define SearchName_h

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>

class SearchNameUser : public QWidget
{
	Q_OBJECT;

	protected:
		QBrush* brush;
		QPalette* palette;

		QTextCodec* codec;

		QListWidget* outputEdit;

		QLineEdit* SecondNameEdit;
		QLineEdit* FirstNameEdit;
		QLineEdit* PatronymicEdit;

		QLabel* SecondNameLabel;
		QLabel* FirstNameLabel;
		QLabel* PatronymicLabel;

		QWidget* MenuWindow;

		QPushButton* FindButton;
		QPushButton* DeletButton;
		QPushButton* BackButton;

	public:
		SearchNameUser(QWidget* Menu = 0);

	public slots:
		void Begin();
		void Find();
		void Delet();
		void Back();
};

#endif
