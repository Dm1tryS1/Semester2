#include "View.h"

#include <QTextCodec> 
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFile> 
#include <QDataStream> 
int ind;

ViewUsers::ViewUsers(QWidget* Menu) :QWidget(0)
{
	MenuWindow = Menu;

	codec = QTextCodec::codecForName("Windows-1251");

	setWindowTitle(codec->toUnicode("Просмотр данных"));
	setWindowIcon(QIcon("Icon.jpg"));
	this->resize(600, 350);

	brush = new QBrush;
	palette = new QPalette;
	brush->setTextureImage(QImage("BackGround.png"));
	palette->setBrush(QPalette::Window, *brush);
	this->setPalette(*palette);

	outputEdit = new QListWidget(this);
	
	DeletButton = new QPushButton(codec->toUnicode("Удалить"), this);
	DeletButton->setFixedSize(150, 40);

	BackButton = new QPushButton(codec->toUnicode("Назад"), this);
	BackButton->setFixedSize(150, 40);

	QHBoxLayout* Layout1 = new QHBoxLayout();
	Layout1->addStretch();
	Layout1->addWidget(DeletButton);
	Layout1->addStretch();
	Layout1->addStretch();
	Layout1->addWidget(BackButton);
	Layout1->addStretch();

	QVBoxLayout* Layout = new QVBoxLayout(this);
	Layout->addWidget(outputEdit);
	Layout->addLayout(Layout1);

	Begin();
	connect(outputEdit, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(Delet1()));
	connect(DeletButton, SIGNAL(clicked(bool)), this, SLOT(Delet2()));
	connect(BackButton, SIGNAL(clicked(bool)), this, SLOT(Back()));
}

void ViewUsers::Begin()
{
	DeletButton->setVisible(false);

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

	F.open(QIODevice::ReadOnly);

	int i = 0;

	outputEdit->clear();

	QDataStream stream(&F);
	stream.setVersion(QDataStream::Qt_5_3);

	while (!F.atEnd())
	{
		stream >> z.secondname >> z.firstname >> z.patronymic >> z.phonenumber >> z.balance >> z.year;
		i++;
		QString str = QString::number(i);
		outputEdit->addItem(str + codec->toUnicode(") ") + (z.secondname) + " " + z.firstname + " " + z.patronymic + codec->toUnicode("; Номер: ") + z.phonenumber + codec->toUnicode(": Баланс: ") + z.balance + codec->toUnicode("; Год: ") + z.year);
	}
	F.close();
}

void ViewUsers::Delet1()
{
	DeletButton->setVisible(true);
	ind = outputEdit->currentRow();
}

void ViewUsers::Delet2()
{
	if (QMessageBox::question(this, codec->toUnicode("База данных"), codec->toUnicode("Удалить запись?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
	{
		DeletButton->setVisible(false);

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

		int i = -1;

		QDataStream streamF(&F);
		streamF.setVersion(QDataStream::Qt_5_3);
		QDataStream streamFTemp(&Ftemp);
		streamFTemp.setVersion(QDataStream::Qt_5_3);

		Ftemp.open(QIODevice::WriteOnly);
		F.open(QIODevice::ReadOnly);

		while (!F.atEnd())
		{
			i++;
			streamF >> z.secondname >> z.firstname >> z.patronymic >> z.phonenumber >> z.balance >> z.year;
			if (i != ind)
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

void ViewUsers::Back()
{	
	outputEdit->clear();
	this->hide();
	MenuWindow->show();

}