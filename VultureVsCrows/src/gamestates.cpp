/**
<VultureVsCrows 2d space shooter: "gamestates.cpp">
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
#include "gamestates.h"


gamestate::gamestate(Font* f):font(f)
{
}

gamestate::~gamestate()
{
    gui_list.clear();
}

unsigned long gamestate::Process(Window &app)
{
   unsigned long  i=0;
   ProcessInput(app);
   i=Update(app);
   Draw();
   return i;
}

void gamestate::AddToList(GUI* g)
{
    gui_list.push_back(g);
}


void gamestate::ProcessInput(Window &app)
{
    for(list<GUI*>::iterator i=gui_list.begin();i!=gui_list.end();i++)
        (*i)->ProcessInput(app);
}

void gamestate::Draw()
{
    for(list<GUI*>::iterator i=gui_list.begin();i!=gui_list.end();i++)
        (*i)->Draw();
}

///================================================================================================================================

gmst_mainmenu::gmst_mainmenu(Font* f,Window &app):gamestate(f)
{
    double bxm=-0.4,bxM=0.4;
    double byM=0.5;
    double bheigth=0.1;
    double bspacing=0.02;
    b1.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("button"),font,"Play game!");byM-=bheigth+bspacing;
    bmeditor.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("button"),font,"Module Editor");byM-=bheigth+bspacing;
    b_background.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("button"),font,"Fiddle with the background");byM-=bheigth+bspacing;
    b_menu.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("button"),font,"Configure some stuff");byM-=bheigth+bspacing;
    b_exit.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("button"),font,"Kill this thing");byM-=bheigth+bspacing;

    AddToList(&b1);
    AddToList(&bmeditor);
    AddToList(&b_background);
    AddToList(&b_menu);
    AddToList(&b_exit);
}

gmst_mainmenu::~gmst_mainmenu()
{

}

unsigned long gmst_mainmenu::Update(Window &app)
{
    unsigned long state=0;

    if(b_background.pressed)
        state=GMST::toBackgroundMenu;
    if(b_menu.pressed)
        state=GMST::toSettingsMenu;
    if(b_exit.pressed)
        state=GMST::exitGame;
    if(bmeditor.pressed)
        state=GMST::toModuleEditor;


    return state;

}

///================================================================================================================================

gmst_settingsmenu::gmst_settingsmenu(Font* f,Window &app):gamestate(f)
{
    vmi=app.GetVideoModeNum();
    change=false;

    apply.Set (0.4,-0.4,-0.08,-0.18,app.GetTex("button"),f,"Apply");
    back.Set(0.4,-0.4,-0.2,-0.3,app.GetTex("button"),f,"Go Back");
    higher_r.Set(0.75,0.45,0.2,0.1,app.GetTex("button"),f,"Higher");
    lower_r.Set(-0.45,-0.75,0.2,0.1,app.GetTex("button"),f,"Lower");
    resolution_label.Set(0.4,-0.4,0.2,0.1,app.GetTex("label"),f,"Resolution = "+GetVideoModeString(vmi));


    AddToList(&apply);
    AddToList(&back);
    AddToList(&higher_r);
    AddToList(&lower_r);
    AddToList(&resolution_label);
}

gmst_settingsmenu::~gmst_settingsmenu()
{

}

unsigned long gmst_settingsmenu::Update(Window &app)
{
    unsigned long state=0;

    apply.SetEnabled(change);
    if(apply.pressed)
    {
        app.Reset(vmi);
        return 0;
    }

    if(back.pressed)
        state=GMST::toMainMenu;

    if(higher_r.pressed)
    {
        if(vmi!=0)
            vmi-=1;
        resolution_label.SetText("Resolution = "+GetVideoModeString(vmi));
        change=true;
    }

    if(lower_r.pressed)
    {
        if(vmi<sf::VideoMode::GetModesCount()-1)
            vmi+=1;
        resolution_label.SetText("Resolution = "+GetVideoModeString(vmi));
        change=true;
    }

    return state;
}

///================================================================================================================================


gmst_meditor::gmst_meditor(Font* f,Window &app):gamestate(f)
{
    b_back.Set(0.4,-0.4,-0.2,-0.3,app.GetTex("button"),f,"Go Back");

    AddToList(&b_back);
}

gmst_meditor::~gmst_meditor()
{
}

unsigned long gmst_meditor::Update(Window &app)
{
    unsigned long state=0;

    if(b_back.pressed)
        state=GMST::toMainMenu;

    return state;
}


gmst_game::gmst_game(Font* f,Window &app):gamestate(f)
{

}

gmst_game::~gmst_game()
{

}
unsigned long gmst_game::Update(Window &app)
{
    return 0;
}


