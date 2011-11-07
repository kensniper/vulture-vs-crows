/**
<VultureVsCrows 2d space shooter: "slider.cpp">
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
#include "slider.h"

Slider::Slider():GUI()
{

}

Slider::Slider(double xmax,double xmin,double ymax,double ymin,GLuint t,double minvalue,double maxvalue,double value):GUI()
{
    Set(xmax,xmin,ymax,ymin,t,minvalue,maxvalue,value);
}

Slider::~Slider()
{

}

void Slider::Set(double xmax,double xmin,double ymax,double ymin,GLuint t,double minvalue,double maxvalue,double value)
{
    translate_x=xmin;
    translate_y=ymin;
    scale_x=xmax-xmin;
    scale_y=ymax-ymin;
    texture=t;

    mv=minvalue;
    Mv=maxvalue;
    v=value;
    v=std::max(v,mv);
    v=std::min(v,Mv);

    slider_translate_x=((v-mv)*0.394+(v-Mv)*0.408)/(Mv-mv);

    active=false;

}

void Slider::Draw()
{
    if(!IsVisible())
        return;
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix( );
    glLoadIdentity( );

    glColor3f(1.,1.,1.);
    glBindTexture( GL_TEXTURE_2D, texture );


    glTranslated( translate_x, translate_y, 0 );
    glScaled(scale_x,scale_y,1.);

    glBegin( GL_QUADS );
        glTexCoord2f( 1.0,0.5);glVertex2d( 1, 1 );
        glTexCoord2f( 1.0, 0);glVertex2d( 1, 0 );
        glTexCoord2f( 0., 0);glVertex2d( 0, 0 );
        glTexCoord2f( 0., 0.5); glVertex2d( 0, 1 );
    glEnd( );



    glTranslated(slider_translate_x,0,0);

    glBegin( GL_QUADS );
        glTexCoord2f( 1.0,1.0);glVertex2d( 1, 1 );
        glTexCoord2f( 1.0, 0.5);glVertex2d( 1, 0 );
        glTexCoord2f( 0., 0.5);glVertex2d( 0, 0 );
        glTexCoord2f( 0., 1.0); glVertex2d( 0, 1 );
    glEnd( );


    glPopMatrix( );
}

void Slider::ProcessInput(const Window& App)
{
    if(!IsVisible())
        return;

    const sf::Input& Input = App.GetInput();

    double x=(Input.GetMouseX()*1.0/App.GetHeight()*2.-App.ratio-translate_x)/scale_x;

    double y=(-(Input.GetMouseY()*1.0/App.GetHeight()*2.-1.)-translate_y)/scale_y;

    bool mouseover=x>0.475+slider_translate_x&&x<0.545+slider_translate_x&&y>0.15&&y<0.85;  /// dependent on texture


    if(mouseover&&!active&&Input.IsMouseButtonDown(sf::Mouse::Left))
    {
        active=true;
        ox=x;
        return;
    }
    if(active&&!Input.IsMouseButtonDown(sf::Mouse::Left))
    {
        active=false;
        ///end of value changing
        return;
    }
    if(active&&Input.IsMouseButtonDown(sf::Mouse::Left))
    {

        slider_translate_x=((v-mv)*0.394+(v-Mv)*0.408)/(Mv-mv)-(ox-x);
        ox=x;
        v=((slider_translate_x+0.408)*Mv-(slider_translate_x-0.394)*mv)/(0.394+0.408);

        v=std::max(v,mv);
        v=std::min(v,Mv);

        slider_translate_x=((v-mv)*0.394+(v-Mv)*0.408)/(Mv-mv);
    }

}

 double Slider::GetValue()
 {
     return v;
 }
