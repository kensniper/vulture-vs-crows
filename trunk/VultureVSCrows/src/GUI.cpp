#include "GUI.h"

GUI::GUI():visible(true)
{

}

GUI::GUI(GLuint t):texture(t)
{

}

GUI::~GUI()
{
}

void GUI::SetVisible(bool b)
{
    visible=b;
}

bool GUI::IsVisible()
{
    return visible;
}
