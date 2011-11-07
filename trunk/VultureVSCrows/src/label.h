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
