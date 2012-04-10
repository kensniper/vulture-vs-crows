/**
<VultureVsCrows 2d space shooter: "Vector2d.cpp">
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
#include "Vector2d.h"
#include <cstdlib>
#include <math.h>

;using namespace std;

Vector2d::Vector2d(double a,double b){
	x=a;
	y=b;
}

Vector2d::Vector2d(){
}

Vector2d::~Vector2d(){
}

Vector2d operator+(Vector2d a,Vector2d b){
    Vector2d c(a.x+b.x,a.y+b.y);

	return c;
}

Vector2d operator-(Vector2d a,Vector2d b){
       Vector2d c(a.x-b.x,a.y-b.y);
	   return c;
}
Vector2d operator-(Vector2d a){
        Vector2d c(-a.x,-a.y);
		return c;
}
Vector2d operator*(Vector2d a,double b){
       Vector2d c(a.x*b,a.y*b);
	   return c;

}
Vector2d operator*(double b,Vector2d a){
        Vector2d c(a.x*b,a.y*b);
		return c;

}

Vector2d operator/(Vector2d a,double b){
	Vector2d c(a.x/b,a.y/b);
	return c;
}

Vector2d& Vector2d::operator+=(const Vector2d& a){
    this->x += a.x;
    this->y += a.y;
    return *this;


}

Vector2d& Vector2d::operator-=(const Vector2d& a){
    this->x -= a.x;
    this->y -= a.y;
    return *this;


}

Vector2d& Vector2d::operator*=(const Vector2d& a){
    this->x *= a.x;
    this->y *= a.y;
    return *this;


}

Vector2d& Vector2d::operator/=(const Vector2d& a){
    this->x /= a.x;
    this->y /= a.y;
    return *this;


}

double operator*(Vector2d a,Vector2d b){
       return a.x*b.x+a.y*b.y;
}


bool operator==(Vector2d a,Vector2d b){
       if(a.x==b.x&&a.y==b.y) return true;
       return false;

}

bool operator!=(Vector2d a,Vector2d b){
       if(a.x!=b.x||a.y!=b.y) return true;
       return false;
}

ostream& operator<<(ostream& stream ,Vector2d a){
       stream<<a.x<<"\t"<<a.y;
       return stream;
}

double Vector2d::Lenght(){
	return sqrt(x*x+y*y);

}

Vector2d Vector2d::rotate(double t)
{
    double xp,yp,c,s;
    c=cos(t);
    s=sin(t);
    xp=x * c - y * s;
    yp=x * s + y * c;
    return Vector2d(xp,yp);
};

double Vector2d::cross(Vector2d a,Vector2d b)
{
    return a.x*b.y-a.y*b.x;
};

Vector2d Vector2d::Normalize(){
	Vector2d c(x,y);
	return c/sqrt(x*x+y*y);

}


