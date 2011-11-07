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

Vector2d Vector2d::Normalize(){
	Vector2d c(x,y);
	return c/sqrt(x*x+y*y);

}


