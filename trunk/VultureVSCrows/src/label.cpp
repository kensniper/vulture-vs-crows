#include "Label.h"

Label::Label():GUI()
{
}

Label::Label(double xmax,double xmin,double ymax,double ymin,GLuint t,Font* f,string s):GUI()
{
    Set(xmax,xmin,ymax,ymin,t,f,s);
}

Label::~Label()
{

}

void Label::Set(double xmax,double xmin,double ymax,double ymin,GLuint t,Font* f,string s)
{
    translate_x=xmin;
    translate_y=ymin;
    scale_x=xmax-xmin;
    scale_y=ymax-ymin;
    texture=t;

    text.Set(f,0,0,s,sf::Color(255,255,255));
    text.floating=false;

    text_translate_x=(scale_x)/2 - text.GetWidth()/2;
    text_translate_y=(scale_y)/2 - text.GetHeight()/2;
}

void Label::Draw()
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
        glTexCoord2f( 1.0,1.0);glVertex2d( 1, 1 );
        glTexCoord2f( 1.0, 0);glVertex2d( 1, 0 );
        glTexCoord2f( 0., 0);glVertex2d( 0, 0 );
        glTexCoord2f( 0., 1.0); glVertex2d( 0, 1 );
    glEnd( );



    glScaled(1/scale_x,1/scale_y,1.);
    glTranslated( text_translate_x, text_translate_y, 0 );
    text.Draw();

    glPopMatrix( );
}

void Label::ProcessInput(const Window& App)
{

    if(!IsVisible())
    {
        hovered=false;
        return;
    }

    const sf::Input& Input = App.GetInput();
    double x=Input.GetMouseX()*1.0/App.GetHeight()*2.-App.ratio;
    double y=-(Input.GetMouseY()*1.0/App.GetHeight()*2.-1.);

    bool mouseover=x>translate_x&&x<translate_x+scale_x&&y>translate_y&&y<translate_y+scale_y;

    if(mouseover)
        hovered = true;
    else
        hovered = false;
}

void Label::SetText(string s)
{
    text.text = s;
    text_translate_x=(scale_x)/2 - text.GetWidth()/2;
}

void Label::SetText( const char *fmt, ... )
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


