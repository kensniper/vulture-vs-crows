#include "font.h"

Font::Font(Window& App,std::string font){

    scale=2.0/App.GetHeight()*1.0;///2.0/
    texture = App.GetTex(font);///!!!!

    GLuint loop;
    float cx;
    float cy;
    base  = glGenLists( 256 );

    glBindTexture( GL_TEXTURE_2D, texture );

    for ( loop = 0; loop < 256; loop++ )
    {


        cx = 1-( float )( loop % 16 ) / 16.0f;
        cy = 1-( float )( loop / 16 ) / 16.0f;

        glNewList( base + ( 255 - loop ), GL_COMPILE );
        glBegin( GL_QUADS );
            glTexCoord2f( cx - 0.0625f, cy);glVertex2i( 0, 0 );
            glTexCoord2f( cx, cy); glVertex2i( 16, 0 );
            glTexCoord2f( cx, cy- 0.0625f  );glVertex2i( 16, 16 );
            glTexCoord2f( cx - 0.0625f, cy- 0.0625f);glVertex2i( 0, 16 );
        glEnd( );
        glTranslated( 13, 0, 0 );
        glEndList( );
    };

}

Font::~Font(){
     glDeleteLists(base, 256);
}

Text::Text()
{

}

Text::Text(Font *_font,double _x,double _y,string _text,sf::Color _color)
{
    Set(_font,_x,_y,_text,_color);
}

Text::~Text()
{

}

void Text::Set(Font *_font,double _x,double _y,string _text,sf::Color _color)
{
    text=_text;
    font=_font;
    color=_color;
    x=_x;
    y=_y;
    scale=1;
    floating=true;
}

void Text::setText( const char *fmt, ... ){
    char t[512];
    va_list ap;


    if ( fmt == NULL )
        return;

    va_start( ap, fmt );
    vsprintf( t, fmt, ap );
    va_end( ap );
    text=t;
}


void Text::Draw()
{
	glColorsf(color);

    glBindTexture( GL_TEXTURE_2D, font->texture );
    glMatrixMode( GL_MODELVIEW );
    if(floating)
    {
        glPushMatrix( );
        glLoadIdentity( );
    }
    glTranslated( x, y, 0 );

    glScaled(font->scale*scale,font->scale*scale,font->scale*scale);

    glListBase( font->base - 32 + ( 128 * 0 ) );

    if(text.find("\n")==string::npos)
        glCallLists( text.length(), GL_BYTE, text.c_str() );
    else
    {
        int i=1;
        int pos=0;
        unsigned int post;
        string str=text;
        while(1)
        {
            if(str.length()==0)
                break;
            post=str.find("\n");

            if(post==string::npos)
            {
                glCallLists( str.length(), GL_BYTE, str.c_str() );
                break;
            }
            else
            {

                if(post!=0)
                {
                    str=str.substr(0,post);
                    glCallLists( str.length(), GL_BYTE, str.c_str() );
                }
                if(post==0&&str.length()==1)
                    break;

                pos+=post+1;
                str=text.substr(pos);
                glLoadIdentity( );

                i++;
                glScaled(font->scale,font->scale,font->scale);
            }
        }
    }

    if(floating)
    {
        glPopMatrix( );
    }

}

double Text::GetWidth()
{
    return (text.length())*13*font->scale*scale;
}
double Text::GetHeight()
{
    return 16*font->scale*scale;
}


