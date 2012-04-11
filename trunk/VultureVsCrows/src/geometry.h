#ifndef _GEOMETRY_
#define _GEOMETRY_


#include <vector>
#include "Vector2d.h"
#include "Startup.h"


class Triangle
{
public:

    Triangle(Vector2d a_,Vector2d b_,Vector2d c_);
    ~Triangle();

    void draw();
    void update(double dt);
    bool point_in_triangle(Vector2d p);
    friend Triangle operator+(Triangle t,Vector2d v);
    void rotate(double t);
    Vector2d center();
    double area();

    Vector2d v;

private:

    Vector2d a;
    Vector2d b;
    Vector2d c;
};


class Construct
{
public:

    Construct(Vector2d a_,Vector2d b_,Vector2d c_);
    ~Construct();


    void add(Construct c);
    bool point_in_construct(Vector2d p);

    void draw();


    Vector2d center;
    double area;

private:

    Triangle t;
    Construct* parent;
    vector<Construct> child;
};




#endif
