#include "Menu.h"

#include <QTextCodec> 
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDataStream>
#include <QFile>

Menu::Menu(QWidget* parent) :QWidget(parent)
{
	codec = QTextCodec::codecForName("Windows-1251");

	setWindowTitle(codec->toUnicode("База данных оператора мобильной связи"));
	setWindowIcon(QIcon("Icon.jpg"));
	this->resize(600, 350);
	
	brush = new QBrush;
	palette = new QPalette;
	brush->setTextureImage(QImage("BackGround.png"));
	palette->setBrush(QPalette::Window, *brush);
	this->setPalette(*palette);

	inputLabel = new QLabel(codec->toUnicode("База данных"), this);
	inputLabel->setFixedHeight(30);
	inputLabel->setStyleSheet(QString("font-size: %1px").arg(26));
	
	AddButton = new QPushButton(codec->toUnicode("Добавить"), this);
	AddButton->setFixedSize(200, 40);
	AddButton->setStyleSheet(QString("font-size: %1px").arg(14));

	SearchNameButton = new QPushButton(codec->toUnicode("Поиск по фамилии"), this);
	SearchNameButton->setFixedSize(200, 40);
	SearchNameButton->setStyleSheet(QString("font-size: %1px").arg(14));

	SearchYearButton = new QPushButton(codec->toUnicode("Поиск по году"), this);
	SearchYearButton->setFixedSize(200, 40);
	SearchYearButton->setStyleSheet(QString("font-size: %1px").arg(14));

	CheckBalanceButton = new QPushButton(codec->toUnicode("Проверка"), this);
	CheckBalanceButton->setFixedSize(150, 30);
	CheckBalanceButton->setStyleSheet(QString("font-size: %1px").arg(12));

	GraphButton = new QPushButton(codec->toUnicode("График"), this);
	GraphButton->setFixedSize(150, 30);
	GraphButton->setStyleSheet(QString("font-size: %1px").arg(12));

	ViewButton = new QPushButton(codec->toUnicode("Просмотр"), this);
	ViewButton->setFixedSize(155, 30);
	ViewButton->setStyleSheet(QString("font-size: %1px").arg(12));

	ClearButton = new QPushButton(codec->toUnicode("Очистить базу"), this);
	ClearButton->setFixedSize(150, 30);
	ClearButton->setStyleSheet(QString("font-size: %1px").arg(12));

	ExitButton = new QPushButton(codec->toUnicode("Завершение работы"), this);
	ExitButton->setFixedSize(150, 30);
	ExitButton->setStyleSheet(QString("font-size: %1px").arg(12));

	AddPersonWindow = new AddPerson(this);

	ViewUsersWindow = new ViewUsers(this);

	SearchNameWindow = new SearchNameUser(this);

	SearchYearWindow = new SearchYearUser(this);

	GraphWindow = new GraphUser(this);

	QVBoxLayout* Layout1 = new QVBoxLayout();
	Layout1->addStretch();
	Layout1->addWidget(AddButton);
	Layout1->addWidget(SearchNameButton);
	Layout1->addWidget(SearchYearButton);
	Layout1->addStretch();

	QHBoxLayout* Layout2 = new QHBoxLayout();
	Layout2->addWidget(CheckBalanceButton);
	Layout2->addWidget(GraphButton);
	Layout2->addWidget(ClearButton);
	Layout2->addWidget(ExitButton);

	QVBoxLayout* Layout3 = new QVBoxLayout();
	Layout3->addStretch();
	Layout3->addWidget(inputLabel);
	Layout3->addWidget(ViewButton);
	Layout3->addStretch();

	QHBoxLayout* Layout4 = new QHBoxLayout();
	Layout4->addStretch();
	Layout4->addLayout(Layout3);
	Layout4->addStretch();
	Layout4->addLayout(Layout1);

	QVBoxLayout* vLayout = new QVBoxLayout(this);
	vLayout->addLayout(Layout4);
	vLayout->addLayout(Layout2);

	connect(AddButton, SIGNAL(clicked(bool)), this, SLOT(Add()));
	connect(SearchNameButton, SIGNAL(clicked(bool)), this, SLOT(SearchName()));
	connect(SearchYearButton, SIGNAL(clicked(bool)), this, SLOT(SearchYear()));
	connect(CheckBalanceButton, SIGNAL(clicked(bool)), this, SLOT(CheckBalance()));
	connect(GraphButton, SIGNAL(clicked(bool)), this, SLOT(Graph()));
	connect(ViewButton, SIGNAL(clicked(bool)), this, SLOT(View()));
	connect(ClearButton, SIGNAL(clicked(bool)), this, SLOT(Clear()));
	connect(ExitButton, SIGNAL(clicked(bool)), this, SLOT(Exit()));
}

void Menu::Add()
{
	this->hide();
	AddPersonWindow->show();
	AddPersonWindow->Begin();
}

void Menu::SearchName()
{
	this->hide();
	SearchNameWindow->show();
	SearchNameWindow->Begin();
}

void Menu::SearchYear()
{
	this->hide();
	SearchYearWindow->show();
	SearchYearWindow->Begin();
}

void Menu:: CheckBalance()
{
	QString str;
	
	QFile F("DataBase.dat");

	struct zap
	{
		QString secondname;
		QString firstname;
		QString patronymic;
		QString phonenumber;
		QString balance;
		QString year;
	} z;

	int i = 0;
	bool ok;

	QDataStream streamF(&F);
	streamF.setVersion(QDataStream::Qt_5_3);

	F.open(QIODevice::ReadOnly);	

	while (!F.atEnd())
	{
		streamF >> z.secondname >> z.firstname >> z.patronymic >> z.phonenumber >> z.balance >> z.year;
		if (z.balance.toInt(&ok,10)<0)
			i++;
	}
	str = QString::number(i);
	QMessageBox::warning(this, codec->toUnicode("База данных"), codec->toUnicode("Количество абонентов с отрицательным балансом: ") + str);
}

void Menu::Graph()
{
	this->hide();
	GraphWindow->show();
}

void Menu::View()
{
	this->hide();
	ViewUsersWindow->show();
	ViewUsersWindow->Begin();
}

void Menu::Clear()
{
	if (QMessageBox::question(this, codec->toUnicode("База данных"), codec->toUnicode("Очистить базу данных?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
	{
		QFile F("DataBase.dat");
		QFile("DataBase.dat").remove();
	}
}

void Menu::Exit()
{
	if (QMessageBox::question(this, codec->toUnicode("База данных"), codec->toUnicode("Завершить работу?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
		close();
}
