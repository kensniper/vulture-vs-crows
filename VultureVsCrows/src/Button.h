/**
<VultureVsCrows 2d space shooter: "Button.h">
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
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "GUI.h"
#include "Font.h"

class Button:public GUI
{
public:
    Button();
    Button(double xmax,double xmin,double ymax,double ymin,GLuint t,Font* f,string s);
    ~Button();
    void Set(double xmax,double xmin,double ymax,double ymin,GLuint t,Font* f,string s);

    void Draw();
    void ProcessInput(const Window& App);

    void SetText(string s);
    void SetText( const char *fmt, ... );
    void SetEnabled(bool b);

    bool pressed;
    bool hovered;

private:
    enum Button_state
    {
        B_UP=0,
        B_HOWER=1,
        B_DOWN=2,
        B_DISABLED=3
    };
    double translate_x,translate_y,scale_x,scale_y,text_translate_x,text_translate_y;
    GLuint texlist;
    Button_state state;
    Text text;
};

#endif
