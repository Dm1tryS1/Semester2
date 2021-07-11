#include "SearchName.h"

#include <QTextCodec> 
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFile> 
#include <QDataStream> 

QString secondname;
QString firstname;
QString patronymic;

SearchNameUser::SearchNameUser(QWidget* Menu) :QWidget(0)
{
	MenuWindow = Menu;

	codec = QTextCodec::codecForName("Windows-1251");

	setWindowTitle(codec->toUnicode("Поиск по фамилии"));
	setWindowIcon(QIcon("Icon.jpg"));
	this->resize(600, 350);

	brush = new QBrush;
	palette = new QPalette;
	brush->setTextureImage(QImage("BackGround.png"));
	palette->setBrush(QPalette::Window, *brush);
	this->setPalette(*palette);

	outputEdit = new QListWidget(this);
	outputEdit->setFixedSize(QSize(400, 350));

	FindButton = new QPushButton(codec->toUnicode("Найти"), this);
	FindButton->setFixedSize(90, 30);

	DeletButton = new QPushButton(codec->toUnicode("Удалить"), this);
	DeletButton->setFixedSize(90, 30);

	BackButton = new QPushButton(codec->toUnicode("Назад"), this);
	BackButton->setFixedSize(90, 30);

	SecondNameEdit = new QLineEdit(codec->toUnicode(""), this);
	SecondNameEdit->setStyleSheet(QString("font-size: %1px").arg(14));

	FirstNameEdit = new QLineEdit(codec->toUnicode(""), this);
	FirstNameEdit->setStyleSheet(QString("font-size: %1px").arg(14));

	PatronymicEdit = new QLineEdit(codec->toUnicode(""), this);
	PatronymicEdit->setStyleSheet(QString("font-size: %1px").arg(14));

	SecondNameLabel = new QLabel(codec->toUnicode("Введите фамилию абонента:"), this);
	SecondNameLabel->setFixedHeight(25);
	SecondNameLabel->setStyleSheet(QString("font-size: %1px").arg(18));

	FirstNameLabel = new QLabel(codec->toUnicode("Введите имя абонента:"), this);
	FirstNameLabel->setFixedHeight(25);
	FirstNameLabel->setStyleSheet(QString("font-size: %1px").arg(18));

	PatronymicLabel = new QLabel(codec->toUnicode("Введите отчество абонента:"), this);
	PatronymicLabel->setFixedHeight(25);
	PatronymicLabel->setStyleSheet(QString("font-size: %1px").arg(18));

	QVBoxLayout* Layout1 = new QVBoxLayout();
	Layout1->addWidget(SecondNameLabel);
	Layout1->addWidget(SecondNameEdit);
	Layout1->addWidget(FirstNameLabel);
	Layout1->addWidget(FirstNameEdit);
	Layout1->addWidget(PatronymicLabel);
	Layout1->addWidget(PatronymicEdit);

	QHBoxLayout* Layout2 = new QHBoxLayout();
	Layout2->addWidget(FindButton);
	Layout2->addWidget(DeletButton);

	QHBoxLayout* Layout3 = new QHBoxLayout();
	Layout3->addStretch();
	Layout3->addWidget(BackButton);
	Layout3->addStretch();

	QVBoxLayout* Layout4 = new QVBoxLayout();
	Layout4->addLayout(Layout2);
	Layout4->addLayout(Layout3);

	QVBoxLayout* Layout5 = new QVBoxLayout();
	Layout5->addLayout(Layout1);
	Layout5->addLayout(Layout4);


	QHBoxLayout* Layout = new QHBoxLayout(this);
	Layout->addWidget(outputEdit);
	Layout->addLayout(Layout5);

	Begin();
	connect(FindButton, SIGNAL(clicked(bool)), this, SLOT(Find()));
	connect(DeletButton, SIGNAL(clicked(bool)), this, SLOT(Delet()));
	connect(BackButton, SIGNAL(clicked(bool)), this, SLOT(Back()));
}

void SearchNameUser::Begin()
{
	SecondNameEdit->clear();
	FirstNameEdit->clear();
	PatronymicEdit->clear();
	outputEdit->clear();
	SecondNameEdit->setFocus();
	DeletButton->setEnabled(false);
}

void SearchNameUser::Find()
{
	outputEdit->clear();
	DeletButton->setEnabled(false);
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
	bool check = true;
	
	QDataStream streamF(&F);
	streamF.setVersion(QDataStream::Qt_5_3);

	F.open(QIODevice::ReadOnly);

	if ((SecondNameEdit->text() != "") && (FirstNameEdit->text() != "") && (PatronymicEdit->text() != ""))
	{
		secondname = SecondNameEdit->text();
		firstname = FirstNameEdit->text();
		patronymic = PatronymicEdit->text();
		outputEdit->addItem(codec->toUnicode("Номера телефонов абонента: ") + secondname + " " + firstname + " " + patronymic);

		while (!F.atEnd())
		{
			streamF >> z.secondname >> z.firstname >> z.patronymic >> z.phonenumber >> z.balance >> z.year;

			if ((secondname == z.secondname) && (firstname == z.firstname) && (patronymic == z.patronymic))
			{
				i++;
				QString str = QString::number(i);
				outputEdit->addItem(str + codec->toUnicode(") Номер телефона: ") + z.phonenumber + codec->toUnicode("; Баланс: ") + z.balance);
				check = false;
				DeletButton->setEnabled(true);
			}
		}
		if (check)
			outputEdit->addItem(codec->toUnicode("Номера не найдены"));
	}
	else 
		QMessageBox::warning(this, QString(), codec->toUnicode("Не все поля заполнены!"));	
	SecondNameEdit->clear();
	FirstNameEdit->clear();
	PatronymicEdit->clear();
}

void SearchNameUser::Delet()
{
	if (QMessageBox::question(this, codec->toUnicode("База данных"), codec->toUnicode("Удалить абонента?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
	{
		QFile F("DataBase.dat");
		QFile Ftemp("Temp.dat");

		struct zap
		{
			QString secondname;
			QString firstname;
			QString patronymic;
			QString phonenumber;
			QString balance;
			QString year;
		} z;

		QDataStream streamF(&F);
		streamF.setVersion(QDataStream::Qt_5_3);
		QDataStream streamFTemp(&Ftemp);
		streamFTemp.setVersion(QDataStream::Qt_5_3);

		Ftemp.open(QIODevice::WriteOnly);
		F.open(QIODevice::ReadOnly);

		while (!F.atEnd())
		{
			streamF >> z.secondname >> z.firstname >> z.patronymic >> z.phonenumber >> z.balance >> z.year;
			if ((secondname != z.secondname) || (firstname != z.firstname) || (patronymic != z.patronymic))
				streamFTemp << z.secondname << z.firstname << z.patronymic << z.phonenumber << z.balance << z.year;
		}

		Ftemp.close();
		F.close();

		QFile("DataBase.dat").remove();

		Ftemp.open(QIODevice::ReadOnly);
		F.open(QIODevice::WriteOnly);


		while (!Ftemp.atEnd())
		{
			streamFTemp >> z.secondname >> z.firstname >> z.patronymic >> z.phonenumber >> z.balance >> z.year;
			streamF << z.secondname << z.firstname << z.patronymic << z.phonenumber << z.balance << z.year;
		}
		Ftemp.close();
		F.close();
		QFile("Temp.dat").remove();
		Begin();
	}
}

void SearchNameUser::Back()
{
	SecondNameEdit->clear();
	FirstNameEdit->clear();
	PatronymicEdit->clear();
	outputEdit->clear();
	this->hide();
	MenuWindow->show();
}

