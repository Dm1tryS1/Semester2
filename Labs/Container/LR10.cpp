#include "LR10.h"
#include <QTextCodec> 
#include <QVBoxLayout>
#include <QMessageBox>
TMySpisok N;
int ind;

Win::Win(QWidget* parent) :QWidget(parent)
{
	codec = QTextCodec::codecForName("Windows-1251");

	setWindowTitle(codec->toUnicode("Контейнер"));

	inputLabel = new QLabel(codec->toUnicode("Введите элемент:"), this);
	inputEdit = new QLineEdit(codec->toUnicode(""), this);

	outputLabel = new QLabel(codec->toUnicode("Элементы списка:"), this);
	outputEdit = new QListWidget(this);

	AddButton = new QPushButton(codec->toUnicode("Добавить"), this);
	DeletButton = new QPushButton(codec->toUnicode("Удалить"), this);
	MaxButton = new QPushButton(codec->toUnicode("Максимальное число"), this);
	ViewButton = new QPushButton(codec->toUnicode("Просмотр"), this);
	CheckButton = new QPushButton (codec->toUnicode("Проверить"), this);
	ExitButton = new QPushButton(codec->toUnicode("Выход"), this);

	frame = new QFrame(this);
	frame->setFrameShadow(QFrame::Raised);
	frame->setFrameShape(QFrame::Panel);

	QVBoxLayout* vLayout1 = new QVBoxLayout(frame);
	vLayout1->addWidget(inputLabel);
	vLayout1->addWidget(inputEdit);
	vLayout1->addWidget(AddButton);
	vLayout1->addWidget(CheckButton);
	vLayout1->addStretch();
	vLayout1->addWidget(ExitButton);

	QHBoxLayout* vLayout2 = new QHBoxLayout();
	vLayout2->addWidget(ViewButton);
	vLayout2->addWidget(MaxButton);
	vLayout2->addWidget(DeletButton);

	QVBoxLayout* vLayout3 = new QVBoxLayout();
	vLayout3->addWidget(outputLabel);
	vLayout3->addWidget(outputEdit);
	vLayout3->addLayout(vLayout2);

	QHBoxLayout* vLayout = new QHBoxLayout(this);
	vLayout->addLayout(vLayout3);
	vLayout->addWidget(frame);

	Begin();
	connect(AddButton, SIGNAL(clicked(bool)), this, SLOT(Add()));
	connect(DeletButton, SIGNAL(clicked(bool)), this, SLOT(Delet1()));
	connect(outputEdit, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(Delet2()));
	connect(MaxButton, SIGNAL(clicked(bool)), this, SLOT(Max()));
	connect(ViewButton, SIGNAL(clicked(bool)), this, SLOT(View()));
	connect(CheckButton, SIGNAL(clicked(bool)), this, SLOT(Check()));
	connect(ExitButton, SIGNAL(clicked(bool)), this, SLOT(close()));
	connect(ExitButton, SIGNAL(clicked(bool)), this, SLOT(Exit()));
}

void Win::Begin()
{
	inputEdit->clear();
	outputEdit->clear();
	inputEdit->setFocus();
	DeletButton->setEnabled(false);
}

void Win::Add()
{
	QString str = inputEdit->text();
	TElement* p;	
	bool ok;
	int k;

	k = str.toInt(&ok, 10);
	if (ok)
	{
		p = new TNum(k);
		N.AddEl(p);
	}
	else
	{
		if (str.length() == 1)
		{
			p = new TChar(str);
			N.AddEl(p);
		}
		else
			QMessageBox::warning(this, QString(), codec->toUnicode("Неверный ввод"));
	}
	inputEdit->clear();
	View();
}

void Win::Delet1()
{
	DeletButton->setEnabled(false);
	N.DeletEl(ind);
	View();
}

void Win::Delet2()
{
	DeletButton->setEnabled(true);
	ind = outputEdit->currentRow();
}

void Win::Check()
{
	QString str = inputEdit->text();
	if (str.length()!=0)
		if (N.CheckEl(str))
			QMessageBox::warning(this, QString(), codec->toUnicode("Элемент входит во множество"));
		else
			QMessageBox::warning(this, QString(), codec->toUnicode("Элемент не входит во множество"));
	else 
		QMessageBox::warning(this, QString(), codec->toUnicode("Неверный ввод"));
}

void Win::Max()
{
	QString str = QString::number(N.maxel());
	QMessageBox::warning(this, QString(), codec->toUnicode("Максимальное число: ") + str);
}

void Win::View()
{
	outputEdit->clear();
	TElement* temp = N.Last();
	while (temp != NULL)
	{
		outputEdit->addItem(temp->Print());
		temp = N.Previous();
	}
}

void Win::Exit()
{
	N.~TMySpisok();
}



void TSpisok::AddEl(TElement* e)
{
	if (first == NULL)
		first = last = e;
	else
	{
		e->sec = first;
		first->pre = e;
		first = e;
	}
}

TSpisok::~TSpisok()
{
	while ((element = Delet()) != NULL)
	{
		delete(element);
	}
}

TElement* TSpisok::Delet(void)
{
	TElement* temp = last;
	if (last != NULL)
	{
		last = last->pre;
		if (last != NULL)
			last->sec = NULL;
	}
	if (last == NULL)
		first = NULL;
	return temp;
}

void TSpisok::DeletEl(int ind)
{
	TElement* temp = N.Last();
	TElement* temp1;
	for (int i = 1; i < ind+1; i++)
	{
		temp = N.Previous();
	}
	if ((temp != N.Last()) & (temp != N.First()))
	{
		temp1 = temp->pre;
		temp->pre->sec = temp->sec;
		temp->sec->pre = temp1;
		delete (temp);
	}
	else
		if ((temp == N.Last()) & (temp == N.First()))
		{
			first = NULL;
			last = NULL;
			delete temp;
		}
		else
			if (temp == last)
			{
				last = temp->pre;
				last->sec = NULL;
				delete (temp);
			}
			else
				if (temp == first)
				{
					first = temp->sec;
					first->pre = NULL;
					delete(temp);
				}
}

bool TSpisok::CheckEl(QString str)
{
	bool ok;
	int k;
	bool result = false;

	k = str.toInt(&ok, 10);
	if (ok)
	{
		TElement* temp = N.First();
		while (temp != NULL)
		{
			if (TNum* q = dynamic_cast<TNum*>(temp))
				if (q->num == k)
					result = true;
			temp = temp -> sec;
		}
	}
	else
	{
		if (str.length() == 1)
		{
			TElement* temp = N.First();
			while (temp != NULL)
			{
				if (TChar* q = dynamic_cast<TChar*>(temp))
					if (str == q->ch)
						result = true;
				temp = temp->sec;
			}
			
		}
	}
	return result;
}


int TMySpisok::maxel()
{
	int max = -999999;
	TElement* temp = N.First();
	while (temp != NULL)
	{
		if (TNum* q = dynamic_cast<TNum*>(temp))
			if (q->num > max)
				max = q->num;
		temp = N.Next();
	}
	return max;
}
