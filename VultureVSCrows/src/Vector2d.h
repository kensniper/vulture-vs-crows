#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_
#include <iostream>
using namespace std;

class Vector2d{



public:
	Vector2d(double a, double b);
	Vector2d();
	~Vector2d();

	friend Vector2d operator+(Vector2d,Vector2d);
	friend Vector2d operator-(Vector2d,Vector2d);
	friend Vector2d operator-(Vector2d);
	friend Vector2d operator*(Vector2d,double);
	friend Vector2d operator*(double,Vector2d);
	friend Vector2d operator/(Vector2d,double);

	friend double operator*(Vector2d,Vector2d);

	friend bool operator==(Vector2d,Vector2d);
	friend bool operator!=(Vector2d,Vector2d);
	Vector2d& operator+=(const Vector2d&);
	Vector2d& operator-=(const Vector2d&);
	Vector2d& operator*=(const Vector2d&);
	Vector2d& operator/=(const Vector2d&);

	friend ostream& operator<<(ostream&,Vector2d);

	Vector2d Normalize();
	double Lenght();

	void setXY(double _x,double _y){x=_x;y=_y;};
	void setX(double _x){x=_x;};
	void setY(double _y){y=_y;};

	double getX(){return x;};
	double getY(){return y;};

    double x,y;
private:


};

#endif //_Vector2d_H_

