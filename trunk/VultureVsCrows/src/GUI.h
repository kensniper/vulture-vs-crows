/**
<VultureVsCrows 2d space shooter: "GUI.h">
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

#ifndef GUI_H
#define GUI_H
#include "Startup.h"

class GUI
{
public:
    GUI();
    GUI(GLuint t);
    virtual ~GUI();

    virtual void Draw()=0;
    virtual void ProcessInput(const Window& App)=0;

    void SetVisible(bool b);
    bool IsVisible();

protected:
    GLuint texture;
private:
    bool visible;
};

#endif // GUI_H
