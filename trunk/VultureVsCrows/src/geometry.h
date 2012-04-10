#ifndef _GEOMETRY_
#define _GEOMETRY_


#include <vector>
#include "Vector2d.h"



class Triangle
{
public:

    Triangle(Vector2d a_,Vector2d b_,Vector2d c_)
    {

        a=a_;
        b=b_;
        c=c_;

    };
    ~Triangle()
    {
    };

    void draw()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2d( a.x, a.y );
            glVertex2d( b.x, b.y );
            glVertex2d( c.x, c.y );
        glEnd();
    };

    bool point_in_triangle(Vector2d p)
    {
        Vector2d v0 = c - a;
        Vector2d v1 = b - a;
        Vector2d v2 = p - a;

        // Compute dot products
        double dot00 = v0* v0;
        double dot01 = v0* v1;
        double dot02 = v0* v2;
        double dot11 = v1* v1;
        double dot12 = v1* v2;

        // Compute barycentric coordinates
        double invDenom = 1. / (dot00 * dot11 - dot01 * dot01);
        double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
        double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

        // Check if point is in triangle
        return (u >= 0) && (v >= 0) && (u + v < 1);
    };

    friend Triangle operator+(Triangle t,Vector2d v)
    {
        Triangle r(t.a+v,t.b+v,t.c+v);
        return r;
    }

    void rotate(double t)
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

    Vector2d center()
    {
        return (a+b+c)/3.;
    }

private:



    Vector2d a;
    Vector2d b;
    Vector2d c;

};





#endif
