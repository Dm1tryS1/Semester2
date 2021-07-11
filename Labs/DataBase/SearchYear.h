#ifndef SearchYear_h
#define SearchYear_h

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>

class SearchYearUser : public QWidget
{
		Q_OBJECT;

	protected:
		QBrush* brush;
		QPalette* palette;

		QTextCodec* codec;

		QListWidget* outputEdit;

		QLineEdit* YearEdit;

		QLabel* YearLabel;

		QWidget* MenuWindow;

		QPushButton* FindButton;
		QPushButton* BackButton;

	public:
		SearchYearUser(QWidget* Menu = 0);

	public slots:
		void Begin();
		void Find();
		void Back();
};

#endif
