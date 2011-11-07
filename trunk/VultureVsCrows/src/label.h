/**
<VultureVsCrows 2d space shooter: "Label.h">
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
#ifndef _LABEL_H_
#define _LABEL_H_

#include "Button.h"

class Label:public GUI
{
public:
    Label();
    Label(double xmax,double xmin,double ymax,double ymin,GLuint t,Font* f,string s);
    ~Label();
    void Set(double xmax,double xmin,double ymax,double ymin,GLuint t,Font* f,string s);

    void Draw();
    void ProcessInput(const Window& App);

    void SetText(string s);
    void SetText( const char *fmt, ... );


    bool hovered;
private:

    double translate_x,translate_y,scale_x,scale_y,text_translate_x,text_translate_y;
    Text text;
};


#endif
