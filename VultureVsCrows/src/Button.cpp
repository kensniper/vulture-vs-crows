/**
<VultureVsCrows 2d space shooter: "Button.cpp">
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
#include "Button.h"

Button::Button():GUI()
{
    texlist=NULL;
}

Button::Button(double xmax,double xmin,double ymax,double ymin,GLuint t,Font* f,string s):GUI()
{
    texlist=NULL;
    Set(xmax,xmin,ymax,ymin,t,f,s);
}

Button::~Button()
{
    glDeleteLists(texlist, 4);
}

void Button::Set(double xmax,double xmin,double ymax,double ymin,GLuint t,Font* f,string s)
{

    translate_x=xmin;
    translate_y=ymin;
    scale_x=xmax-xmin;
    scale_y=ymax-ymin;
    texture=t;
    pressed=false;
    state=B_UP;

    text.Set(f,0,0,s,sf::Color(255,255,255));
    text.floating=false;

    text_translate_x=(scale_x)/2 - text.GetWidth()/2;
    text_translate_y=(scale_y)/2 - text.GetHeight()/2;

    if(texlist!=0)
    {
        glDeleteLists(texlist, 4);
        texlist=0;
    }


    texlist  = glGenLists( 4 );
    glBindTexture( GL_TEXTURE_2D, texture );

    double cy;
    for ( int i = 0; i < 4; i++ )
    {
        cy = 1-( float )( i % 4 ) / 4.0f;
        glNewList( texlist + ( 3 - i ), GL_COMPILE );
        glBegin( GL_QUADS );
            glTexCoord2f( 1.0,cy - 0.25);glVertex2d( 1, 1 );
            glTexCoord2f( 1.0, cy);glVertex2d( 1, 0 );
            glTexCoord2f( 0., cy);glVertex2d( 0, 0 );
            glTexCoord2f( 0., cy - 0.25); glVertex2d( 0, 1 );
        glEnd( );
        glEndList( );
    };
}


void Button::Draw()
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

    glListBase(texlist);
    int tmp =state;
    glCallLists( 1, GL_INT, &tmp );

    glScaled(1/scale_x,1/scale_y,1.);
    glTranslated( text_translate_x, text_translate_y, 0 );
    text.Draw();

    glPopMatrix( );


}

void Button::SetText(string s)
{
    text.text = s;
    text_translate_x=(scale_x)/2 - text.GetWidth()/2;
}

void Button::SetText( const char *fmt, ... )
{

    char t[512];
    va_list ap;


    if ( fmt == NULL )
        return;

    va_start( ap, fmt );
    vsprintf( t, fmt, ap );
    va_end( ap );
    text.text=t;
    text_translate_x=(scale_x)/2 - text.GetWidth()/2;
}

void Button::SetEnabled(bool b)
{
    if(state==B_DISABLED&&b)
        state=B_UP;
    if(state!=B_DISABLED&&!b)
        state=B_DISABLED;
}

void Button::ProcessInput(const Window& App)
{
    //cerr<<txt->text;
    pressed=false;
    hovered=false;
    if(state==B_DISABLED||!IsVisible())
        return;

    const sf::Input& Input = App.GetInput();
    double x=Input.GetMouseX()*1.0/App.GetHeight()*2.-App.ratio;
    double y=-(Input.GetMouseY()*1.0/App.GetHeight()*2.-1.);

    bool mouseover=x>translate_x&&x<translate_x+scale_x&&y>translate_y&&y<translate_y+scale_y;

    if(state==B_DOWN&&!Input.IsMouseButtonDown(sf::Mouse::Left))
    {
        if(mouseover)
            pressed=true;
    }

    if(mouseover)
    {

        state=B_HOWER;
        if(Input.IsMouseButtonDown(sf::Mouse::Left))
            state=B_DOWN;
    }
    else
        state=B_UP;

    hovered=(state==B_HOWER);
}

