#include "geometry.h"


Triangle::Triangle(Vector2d a_,Vector2d b_,Vector2d c_)
{
    a=a_;
    b=b_;
    c=c_;
    v=Vector2d(0,0);
};

Triangle::~Triangle()
{

};

void Triangle::draw()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2d( a.x, a.y );
        glVertex2d( b.x, b.y );
        glVertex2d( c.x, c.y );
    glEnd();
};

void Triangle::update(double dt)
{
    a+=v*dt;
    b+=v*dt;
    c+=v*dt;

};

bool Triangle::point_in_triangle(Vector2d p)
{
    Vector2d v0 = c - a;
    Vector2d v1 = b - a;
    Vector2d v2 = p - a;

    double dot00 = v0* v0;
    double dot01 = v0* v1;
    double dot02 = v0* v2;
    double dot11 = v1* v1;
    double dot12 = v1* v2;

    double invDenom = 1. / (dot00 * dot11 - dot01 * dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v < 1);
};

Triangle operator+(Triangle t,Vector2d v)
{
    Triangle r(t.a+v,t.b+v,t.c+v);
    return r;
}

void Triangle::rotate(double t)
{
    Vector2d cms = center();
    Vector2d ap,bp,cp;
    ap=a-cms;
    bp=b-cms;
    cp=c-cms;

    ap=ap.rotate(t);
    bp=bp.rotate(t);
    cp=cp.rotate(t);

    a=cms+ap;
    b=cms+bp;
    c=cms+cp;
}

Vector2d Triangle::center()
{
    return (a+b+c)/3.;
}

double Triangle::area()
{
    Vector2d A,B;
    A=b-a;
    B=c-a;

    return 0.5* fabs(A.x*B.y-A.y*B.x);

}

Construct::Construct(Vector2d a,Vector2d b,Vector2d c):t(a,b,c)
{
    parent = 0;
    center = t.center();
    area = t.area();
};

Construct::~Construct()
{
    child.clear();
};

void Construct::add(Construct c)
{
    c.parent=this;
    child.push_back(c);
    center= (center*area+c.center*c.area)/(area+c.area);
    area+=c.area;
};

bool Construct::point_in_construct(Vector2d p)
{

    for(vector<Construct>::iterator it=child.begin();it!=child.end();it++)
        if(it->point_in_construct(p)) return true;
    return t.point_in_triangle(p);
}

