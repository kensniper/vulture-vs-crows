#ifndef _CHECKBOX_H_
#define _CHECKBOX_H_

#include "GUI.h"
#include "font.h"

class CheckBox:public GUI
{
public:
    CheckBox();
    CheckBox(double xmax,double xmin,double ymax,double ymin,GLuint t);
    ~CheckBox();
    void Set(double xmax,double xmin,double ymax,double ymin,GLuint t);

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

