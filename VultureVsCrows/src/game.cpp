#include "gamestates.h"

gmst_game::gmst_game(Font* f,Window &app):gamestate(f)
{
    triangle.push_back(Triangle(Vector2d(-0.1,0),Vector2d(0.0,0),Vector2d(0,0.1) ));
    triangle.push_back(Triangle(Vector2d(-0.2,1),Vector2d(-0.3,0.9),Vector2d(-0.4,0.95) ));
    editstate=EDST_nothing;

}

gmst_game::~gmst_game()
{

}
unsigned long gmst_game::Update(Window &app)
{
    state=0;
    sf::Event Event;
    while (app.GetEvent(Event))
    {
        if ((Event.Type == sf::Event::KeyPressed)&&(Event.Key.Code == sf::Key::Escape))
        {
            state=GMST::toMainMenu;
            return state;
        }

    }

    const sf::Input* input=&app.GetInput();
    double x=input->GetMouseX();
    double y=input->GetMouseY();
    x=x*1.0/app.GetHeight()*2.-app.ratio;
    y=-(y*1.0/app.GetHeight()*2.-1.);


    if(!input->IsMouseButtonDown(sf::Mouse::Left))
        editstate=EDST_nothing;
    else if(editstate==EDST_moving&&input->IsMouseButtonDown(sf::Mouse::Left))
    {
        *ed=*ed+(Vector2d(x,y)-editvector);
        editvector=Vector2d(x,y);
    }
    else if(editstate==EDST_rotating&&input->IsMouseButtonDown(sf::Mouse::Left))
    {
        Vector2d c=ed->center();
        ed->rotate(atan2(Vector2d::cross(editvector-c,Vector2d(x,y)-c),(editvector-c)*(Vector2d(x,y)-c)));
        editvector=Vector2d(x,y);
    }



    for(vector<Triangle>::iterator it=triangle.begin();it!=triangle.end();it++)
    {
        if(it->point_in_triangle(Vector2d(x,y)))
        {
            glColor3f(0.0,0.4,0.8);

            if(editstate==EDST_nothing&&input->IsMouseButtonDown(sf::Mouse::Left))
            {
                ed=it;
                if(input->IsKeyDown(sf::Key::LControl))
                    editstate=EDST_rotating;
                else
                    editstate=EDST_moving;
                editvector=Vector2d(x,y);
            }

            if(editstate==EDST_nothing&&input->IsMouseButtonDown(sf::Mouse::Left))
            {
                ed=it;
                editstate=EDST_moving;
                editvector=Vector2d(x,y);
            }


        }
        else
            glColor3f(0.0,0.2,1.0);

        it->draw();

    };




    return state;
}
