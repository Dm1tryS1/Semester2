#include "SearchYear.h"

#include <QTextCodec> 
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFile> 
#include <QDataStream> 

SearchYearUser::SearchYearUser(QWidget* Menu) :QWidget(0)
{
	MenuWindow = Menu;

	codec = QTextCodec::codecForName("Windows-1251");

	setWindowTitle(codec->toUnicode("����� �� �������"));
	setWindowIcon(QIcon("Icon.jpg"));
	this->resize(600, 350);

	brush = new QBrush;
	palette = new QPalette;
	brush->setTextureImage(QImage("BackGround.png"));
	palette->setBrush(QPalette::Window, *brush);
	this->setPalette(*palette);

	outputEdit = new QListWidget(this);
	outputEdit->setFixedSize(QSize(400, 350));

	FindButton = new QPushButton(codec->toUnicode("�����"), this);
	FindButton->setFixedSize(90, 30);
	FindButton->setStyleSheet(QString("font-size: %1px").arg(14));

	BackButton = new QPushButton(codec->toUnicode("�����"), this);
	BackButton->setFixedSize(90, 30);
	BackButton->setStyleSheet(QString("font-size: %1px").arg(14));

	YearEdit = new QLineEdit(codec->toUnicode(""), this);
	YearEdit->setStyleSheet(QString("font-size: %1px").arg(14));

	YearLabel = new QLabel(codec->toUnicode("������� ��� �����������:"), this);
	YearLabel->setFixedHeight(25);
	YearLabel->setStyleSheet(QString("font-size: %1px").arg(18));
	
	QVBoxLayout* Layout1 = new QVBoxLayout();
	Layout1->addWidget(YearLabel);
	Layout1->addWidget(YearEdit);

	QHBoxLayout* Layout2 = new QHBoxLayout();
	Layout2->addStretch();
	Layout2->addWidget(FindButton);
	Layout2->addStretch();

	QHBoxLayout* Layout3 = new QHBoxLayout();
	Layout3->addStretch();
	Layout3->addWidget(BackButton);
	Layout3->addStretch();

	QVBoxLayout* Layout4 = new QVBoxLayout();
	Layout4->addLayout(Layout1);
	Layout4->addStretch();
	Layout4->addLayout(Layout2);
	Layout4->addLayout(Layout3);

	QHBoxLayout* Layout = new QHBoxLayout(this);
	Layout->addWidget(outputEdit);
	Layout->addLayout(Layout4);

	Begin();
	connect(FindButton, SIGNAL(clicked(bool)), this, SLOT(Find()));
	connect(BackButton, SIGNAL(clicked(bool)), this, SLOT(Back()));
}

void SearchYearUser::Begin()
{
	YearEdit->clear();
	outputEdit->clear();
	YearEdit->setFocus();
}

void SearchYearUser::Find()
{
	QString year;

	outputEdit->clear();
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

	if (YearEdit->text() != "")
	{
		year = YearEdit->text();
		outputEdit->addItem(codec->toUnicode("������ ���������, ������������������ � ") + year + codec->toUnicode(" ����:"));
		while (!F.atEnd())
		{
			streamF >> z.secondname >> z.firstname >> z.patronymic >> z.phonenumber >> z.balance >> z.year;

			if (year == z.year) 
			{
				i++;
				QString str = QString::number(i);
				outputEdit->addItem(str + codec->toUnicode(") ���: ") + z.secondname +" "+z.firstname+" "+z.patronymic+ codec->toUnicode("; �����: ") + z.phonenumber+ codec->toUnicode(";"));
				check = false;
			}
		}
		if (check)
			outputEdit->addItem(codec->toUnicode("������ �� �������"));
	}
	else
		QMessageBox::warning(this, codec->toUnicode("���� ������"), codec->toUnicode("�� ��� ���� ���������!"));
	YearEdit->clear();
}

void SearchYearUser::Back()
{
	YearEdit->clear();
	outputEdit->clear();
	this->hide();
	MenuWindow->show();
}

