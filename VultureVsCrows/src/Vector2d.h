/**
<VultureVsCrows 2d space shooter: "Vector2d.h">
Copyright (C) 2011  Janez Podhostnik

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
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

    static double cross(Vector2d,Vector2d);

    Vector2d rotate(double);
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

