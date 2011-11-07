/**
<VultureVsCrows 2d space shooter: "font.h">
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
