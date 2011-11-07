#ifndef GUI_H
#define GUI_H
#include "startup.h"

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
