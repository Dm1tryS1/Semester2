#ifndef Menu_h
#define Menu_h
#include "Add.h"
#include "View.h"
#include "SearchName.h"
#include "SearchYear.h"
#include "Graph.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class Menu : public QWidget
{
	Q_OBJECT;

	protected:
		QBrush* brush;
		QPalette* palette;

		QTextCodec* codec;

		AddPerson* AddPersonWindow;
		ViewUsers* ViewUsersWindow;
		SearchNameUser* SearchNameWindow;
		SearchYearUser* SearchYearWindow;
		GraphUser* GraphWindow;

		QLabel* inputLabel;
		QPushButton* AddButton;
		QPushButton* SearchNameButton;
		QPushButton* SearchYearButton;
		QPushButton* CheckBalanceButton;
		QPushButton* GraphButton;
		QPushButton* ViewButton;
		QPushButton* ClearButton;
		QPushButton* ExitButton;

	public:
		Menu(QWidget* parent = 0);

	public slots:
		void Add();
		void SearchName();
		void SearchYear();
		void CheckBalance();
		void Graph();
		void View();
		void Clear();
		void Exit();
};

#endif