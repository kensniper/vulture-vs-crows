#ifndef _FONT_
#define _FONT_

#include "startup.h"

class Font{
    public:
        Font(Window& App,std::string font);
        ~Font();

        GLuint texture;
        GLuint base;
        double scale;
    private:

};


class Text{
    public:
        Text();
        Text(Font *_font,double _x,double _y,string _text,sf::Color _color);
        ~Text();
        void Set(Font *_font,double _x,double _y,string _text,sf::Color _color);

        void setText( const char *fmt, ... );
        void Draw();
        double GetWidth();
        double GetHeight();


        std::string text;
        bool floating;//if floating do push and pop modelview

    private:
        Font *font;
        sf::Color color;
        double x;
        double y;
        double scale;

};


#endif
