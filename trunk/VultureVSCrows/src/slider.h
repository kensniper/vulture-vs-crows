#ifndef SLIDER_H
#define SLIDER_H

#include "GUI.h"


class Slider:public GUI
{
    public:
        Slider();
        Slider(double xmax,double xmin,double ymax,double ymin,GLuint t,double minvalue,double maxvalue,double value);
        virtual ~Slider();
        void Set(double xmax,double xmin,double ymax,double ymin,GLuint t,double minvalue,double maxvalue,double value);


        virtual void Draw();
        virtual void ProcessInput(const Window& App);

        double GetValue();

        bool active;

    protected:
    private:
        double translate_x,translate_y,scale_x,scale_y,slider_translate_x;
        double mv,Mv,v;
        double ox;
};

#endif // SLIDER_H
