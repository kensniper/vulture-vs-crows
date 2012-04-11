#include "gamestates.h"

gmst_game::gmst_game(Font* f,Window &app):gamestate(f)
{
    editstate=EDST_nothing;
    tn=0;
    editbool=false;
}

gmst_game::~gmst_game()
{

}
unsigned long gmst_game::Update(Window &app)
{
    state=0;

    const sf::Input* input=&app.GetInput();

    double x=input->GetMouseX();
    double y=input->GetMouseY();
    x=x*1.0/app.GetHeight()*2.-app.ratio;
    y=-(y*1.0/app.GetHeight()*2.-1.);

    double dt=std::min(app.GetFrameTime(),0.1f);

    if(input->IsKeyDown(sf::Key::Escape))
        return GMST::toMainMenu;



    if(!input->IsMouseButtonDown(sf::Mouse::Left)&&!input->IsMouseButtonDown(sf::Mouse::Right)) //no mouse button
    {
        if(!(editstate==EDST_drawing))
            editstate=EDST_nothing;


        else if(editbool)
        {
            vtx[tn]=Vector2d(x,y);
            tn++;
            if(tn==3)
            {
                triangle.push_back(Triangle(Vector2d(vtx[0]),Vector2d(vtx[1]),Vector2d(vtx[2])));
                editstate=EDST_nothing;
            }
            editbool=false;
        }
    }
    else if(input->IsMouseButtonDown(sf::Mouse::Left))// left
    {
        if(editstate==EDST_moving)
        {
           *ed=*ed+(Vector2d(x,y)-editvector);
            editvector=Vector2d(x,y);
        }
        else if(editstate==EDST_rotating)
        {
            Vector2d c=ed->center();
            ed->rotate(atan2(Vector2d::cross(editvector-c,Vector2d(x,y)-c),(editvector-c)*(Vector2d(x,y)-c)));
            editvector=Vector2d(x,y);
        }
        else if(editstate==EDST_nothing&&input->IsKeyDown(sf::Key::LShift))
        {
            editstate=EDST_drawing;
            tn=0;
            editbool=true;
        }

    }
    else
    {
        if(editstate==EDST_velocity)
        {
            ed->v=ed->v+(Vector2d(x,y)-editvector);
            editvector=Vector2d(x,y);
        }
    }



    for(vector<Triangle>::iterator it=triangle.begin();it!=triangle.end();it++)
    {
        if(it->point_in_triangle(Vector2d(x,y)))
        {
            glColor3f(0.0,0.4,0.8);

            if(editstate==EDST_nothing)
            {
                if(input->IsMouseButtonDown(sf::Mouse::Left))
                {
                    ed=it;
                    if(input->IsKeyDown(sf::Key::LControl))
                        editstate=EDST_rotating;
                    else
                        editstate=EDST_moving;
                    editvector=Vector2d(x,y);

                }
                else if(input->IsKeyDown(sf::Key::Delete))
                {
                    editstate=EDST_deleting;
                    ed=it;
                }
                else if(input->IsMouseButtonDown(sf::Mouse::Right))
                {
                    editstate=EDST_velocity;
                    ed=it;
                    ed->v=Vector2d(0,0);
                    editvector=Vector2d(x,y);
                }
            }


        }
        else
            glColor3f(0.0,0.2,1.0);

        if(editstate==EDST_nothing)
        {
           it->update(dt);
        }

        it->draw();

        glColor3d(0.8,0.1,0.0);
        glBegin(GL_LINES);
            glVertex2d( it->center().x, it->center().y );
            glVertex2d( it->center().x+it->v.x, it->center().y+it->v.y );
        glEnd();

    };



    if(editstate==EDST_drawing&&tn>0)
    {
        if(input->IsMouseButtonDown(sf::Mouse::Left))
        {
            editbool=true;
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        glColor3f(0.0,0.6,0);
        if(tn==1)
        {
            glBegin(GL_LINE_STRIP);
                glVertex2d( vtx[0].x, vtx[0].y );
                glVertex2d( x, y );
            glEnd();
        }
        else if(tn==2)
        {
            glBegin(GL_LINE_LOOP);
                glVertex2d( vtx[0].x, vtx[0].y );
                glVertex2d( vtx[1].x, vtx[1].y );
                glVertex2d( x, y );
            glEnd();
        }

    }

    if(editstate==EDST_deleting)
        triangle.erase(ed);


    return state;
}
