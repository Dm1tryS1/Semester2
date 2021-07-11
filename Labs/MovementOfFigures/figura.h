#ifndef figura_h
#define figura_h
#include <QPainter>

class Figura
{
	protected:
		int x, y;
		int halflen;
		int dx, dy;
		virtual void draw(QPainter* Painter) = 0;
	public:
		Figura(int X, int Y, int Halflen):x(X),y(Y),halflen(Halflen){}
		void move(float Alpha, QPainter* Painter);
		virtual ~Figura(){};
};

class MyLine : public Figura
{
	protected:
		void draw(QPainter* Painter);
	public:
		MyLine(int x, int y, int halflen) :Figura(x, y, halflen) {}
};

class MyRect :public Figura
{
	protected:
		void draw(QPainter* Painter);
	public:
		MyRect(int x, int y, int halflen) :Figura(x, y, halflen) {}
};

class MyQube :public Figura
{
	protected:
		void draw(QPainter* Painter);
	public:
		MyQube(int x, int y, int halflen) : Figura (x, y, halflen) {}
};

#endif