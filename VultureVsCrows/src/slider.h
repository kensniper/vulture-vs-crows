/**
<VultureVsCrows 2d space shooter: "slider.h">
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
