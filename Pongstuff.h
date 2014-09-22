#ifndef IOSTREAM
#include <iostream>
using namespace std;
#endif
#include <fstream>

class Vector		//VECTOR CLASS
{
private:
	float x;
	float y;
public:
	Vector();
	Vector(float, float);
	void Set(float ax, float ay)
	{
		x = ax;
		y = ay;
	}
	float GetX()
	{
		return x;
	}
	float GetY()
	{
		return y;
	}
	float Length()
	{
		return sqrt((x * x) + (y * y));
	}
};

Vector::Vector(float ax, float ay)		//VECTOR CONSTRUCTOR
{
	x = ax;
	y = ay;
}

class Point		//POINT CLASS
{
private:
	float x;
	float y;
public:
	Point();
	Point(float, float);
	void Set(float ax, float ay)
	{
		x = ax;
		y = ay;
	}
	float GetX()
	{
		return x;
	}
	float GetY()
	{
		return y;
	}
};

Point::Point(float ax, float ay)		//POINT CONSTRUCTOR
{
	x = ax;
	y = ay;
}

class Line		//LINE CLASS
{
private:
	float X1;
	float Y1;
	float X2;
	float Y2;
public:

	Line();
	Line(Point, Point);
	void Set(float startx, float starty, float endx, float endy)
	{
		X1 = startx;
		Y1 = starty;
		X2 = endx;
		Y2 = endy;
	}
	void Set(Point a_point1, Point a_point2)
	{
		X1 = a_point1.GetX();
		Y1 = a_point1.GetY();
		X2 = a_point2.GetX();
		Y2 = a_point2.GetY();
	}
	float GetLength()
	{
		return (((X2 - X1) * (X2 - X1)) + ((Y2 - Y1) * (Y2 - Y1)));
	}
	float GetLengthX()
	{
		return (X2 - X1);
	}
	float GetLengthY()
	{
		return (Y2 - Y1);
	}
	Vector GetVector()
	{
		Vector v(GetLengthX(), GetLengthY());
		return v;
	}
};

Line::Line(Point a_point1, Point a_point2)		//LINE CONSTRUCTOR
{
	X1 = a_point1.GetX();
	Y1 = a_point1.GetY();
	X2 = a_point2.GetX();
	Y2 = a_point2.GetY();
}


class Box		//BOX CLASS
{
private:
	float X1;
	float Y1;
	float X2;
	float Y2;
public:
	Box(void);
	Box(Point, Point);
	Box(float, float, float, float);
	void Set(Point p1, Point p2)
	{
		X1 = p1.GetX();
		Y1 = p1.GetY();
		X2 = p2.GetX();
		Y2 = p2.GetY();
	}
	Point GetLeftBot()
	{
		Point p(X1, Y1);
		return p;
	}
	Point GetLeftTop()
	{
		Point p(X1, Y2);
		return p;
	}
	Point GetRightBot()
	{
		Point p(X2, Y1);
		return p;
	}
	Point GetRightTop()
	{
		Point p(X2, Y2);
		return p;
	}
	Line GetBotLine()
	{
		Line l(GetLeftBot(), GetRightBot());
		return l;
	}
	Line GetRightLine()
	{
		Line l(GetRightBot(), GetRightTop());
		return l;
	}
	Line GetTopLine()
	{
		Line l(GetRightTop(), GetLeftTop());
		return l;
	}
	Line GetLeftLine()
	{
		Line l(GetLeftTop(), GetLeftBot());
		return l;
	}
};
		//BOX CONSTRUCTORS
Box::Box(Point p1, Point p2)	//SET WITH POINT CLASS
{
	X1 = p1.GetX();
	Y1 = p1.GetY();
	X2 = p2.GetX();
	Y2 = p2.GetY();
}
Box::Box(float ax1, float ay1, float ax2, float ay2)		//SET WITH FLOATS
{
	X1 = ax1;
	Y1 = ay1;
	X2 = ax2;
	Y2 = ay2;
}

float Dot(Vector a, Vector b)		//DOT PRODUCT OF TWO VECTORS
{
	return ((a.GetX() * b.GetX()) + (a.GetY() * b.GetY()));
}

bool CheckPointBox(Point p, Box b)		//POINT-BOX COLLISION
{
	if (p.GetX() > b.GetLeftBot().GetX() && p.GetX() < b.GetRightTop().GetX() && p.GetY() > b.GetLeftBot().GetY() && p.GetY() < b.GetRightTop().GetY())
		return true;
	return false;
}

bool CheckLineLine(Line l1, Line l2)				//NOT DONE YET BECAUSE I STOOPUD
{
	return false;
}

bool CheckBoxBox(Box b1, Box b2)		//BOX-BOX COLLISION - ONLY CHECKS POINTS NOT LINES
{
	if (CheckPointBox(b1.GetLeftBot(), b2) || CheckPointBox(b1.GetRightBot(), b2) || CheckPointBox(b1.GetRightTop(), b2) || CheckPointBox(b1.GetLeftTop(), b2))
		return true;
	return false;
}

class PLAYERBAR
{
private:
	float x, y, speed, height, width, leftbound, rightbound;
	unsigned int sprite, moveLeft, moveRight;
public:
	void SetBound(float al, float ar)
	{
		leftbound = al;
		rightbound = ar;
	}
	void SetKeys(unsigned int aleft, unsigned int aright)
	{
		moveLeft = aleft;
		moveRight = aright;
	}
	float GetWidth()
	{
		return width;
	}
	float GetHeight()
	{
		return height;
	}
	void SetSize(float awidth, float aheight)
	{
		height = aheight;
		width = awidth;
	}
	void SetSprite(unsigned int asprite)
	{
		sprite = asprite;
	}
	unsigned int GetSprite()
	{
		return sprite;
	}
	float GetX()
	{
		return x;
	}
	float GetY()
	{
		return y;
	}
	void SetLoc(float ax, float ay)
	{
		x = ax;
		y = ay;
	}
	void SetSpeed(float a)
	{
		speed = a;
	}
	void Move(float aTime)
	{
		if (IsKeyDown(moveLeft) && x > leftbound)
			x -= (speed * aTime);
		if (IsKeyDown(moveRight) && x < rightbound)
			x += (speed * aTime);
	}
	Box GetBox()
	{
		Box b(x - (.5f * width), y - (.5f * height), x + (.5f * width), y + (.5f * height));
		return b;
	}
};

class BALL
{
private:
	float x, y, height, width, speedx, speedy, leftbound, rightbound;
	unsigned int sprite;
public:
	float GetWidth()
	{
		return width;
	}
	float GetHeight()
	{
		return height;
	}
	void SetSize(float awidth, float aheight)
	{
		height = aheight;
		width = awidth;
	}
	void SetSprite(unsigned int asprite)
	{
		sprite = asprite;
	}
	unsigned int GetSprite()
	{
		return sprite;
	}
	void SetBound(float al, float ar)
	{
		leftbound = al;
		rightbound = ar;
	}
	float GetX()
	{
		return x;
	}
	float GetY()
	{
		return y;
	}
	void SetLoc(float ax, float ay)
	{
		x = ax;
		y = ay;
	}
	void SetSpeed(float ax, float ay)
	{
		speedx = ax;
		speedy = ay;
	}
	Vector GetSpeed()
	{
		Vector va(speedx, speedy);
		return va;
	}
	void Reverse()
	{
		speedy *= -1.05;
		speedx *= 1.05;
	}
	float GetSpeedY()
	{
		return speedy;
	}
	float LengthSpeed()
	{
		return sqrt((speedx * speedx) + (speedy * speedy));
	}
	Box GetBox()
	{
		Box b(x - (.5f * width), y - (.5f * height), x + (.5f * width), y + (.5f * height));
		return b;
	}
	void Move(float atime)
	{

		x += (speedx * atime);
		y += (speedy * atime);
		if ((x + (speedx * atime)) <= leftbound || (x + (speedx * atime)) >= rightbound)
		{
			speedx *= -1;
		}
	}
};

void Write(char writeme)
{
	fstream fscores;
	fscores.open("fscores.txt", ios_base::out);
	fscores << writeme << " " << endl;
	fscores.close();
}

void Write(char *writeme)
{
	fstream fscores;
	fscores.open("fscores.txt", ios_base::out);
	fscores << writeme << " " << endl;
	fscores.close();
}
void WriteOld(float writeme)
{
	fstream fscores;
	fscores.open("foldscores.txt", ios_base::out);
	fscores << writeme << " " << endl;
	fscores.close();
}

char *Read()
{
	char ca[6];
	fstream fscores;
	fscores.open("fscores.txt", ios_base::in);
	fscores.getline(ca, 6);
	fscores.close();
	return ca;
}

float ReadAsFloat()
{
	char ca[6];
	float fa;
	fstream fscores;
	fscores.open("fscores.txt", ios_base::in);
	fscores.getline(ca,6);
	fscores.close();
	fa = atoi(ca);
	return fa;
}