/**
<VultureVsCrows 2d space shooter: "gamestates.h">
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
#ifndef GAMESTATES
#define GAMESTATES

#include "label.h"
#include "slider.h"
#include "Boids.h"
#include <list>


namespace GMST
{
    enum GMST
    {
        exitGame=1,
        toMainMenu=2,
        toSettingsMenu=4,
        toBackgroundMenu=8,
        toGame=0x10,
        toModuleEditor=0x20
    };
};


class gamestate
{
public:
    gamestate(Font* f);
    virtual ~gamestate();
    unsigned long Process(Window &app);
    virtual unsigned long Update(Window &app)=0;

protected:
    Font* font;

    void AddToList(GUI* g);
private:
    void ProcessInput(Window &app);
    void Draw();
    list<GUI*> gui_list;

};

class gmst_mainmenu:public gamestate
{
public:
    gmst_mainmenu(Font* f,Window &app);
    virtual ~gmst_mainmenu();
    virtual unsigned long Update(Window &app);

private:
    Button b1;
    Button bmeditor;
    Button b_menu;
    Button b_exit;
    Button b_background;
};


class gmst_settingsmenu:public gamestate
{
public:
    gmst_settingsmenu(Font* f,Window &app);
    virtual ~gmst_settingsmenu();
    virtual unsigned long Update(Window &app);

private:
    bool change;
    unsigned int vmi;
    Button back;
    Label resolution_label;
    Button higher_r;
    Button lower_r;
    Button apply;
};

class gmst_backmenu:public gamestate
{
public:
    gmst_backmenu(Font* f,Window &app,Boids *b);
    virtual ~gmst_backmenu();
    virtual unsigned long Update(Window &app);

private:
    Button bforce;
    Button pauseb;
    Button con;
    Button dtree;
    Button reset;
    Button back;
    Button hide;
    Button ushade;
    Label tooltip;
    Label lnumpart;
    bool visible;
    bool wasdown,change;
    Boids *boids;
    Slider nslider;
    Label plabel;
    Slider pslider;
    Label alabel;
    Slider aslider;

    Label lslimit;
    Slider sslimit;
    Label lmslimit;
    Slider smslimit;
    Label lmblur;
    Slider smblur;
    Label lma;
    Slider sma;

    Label laf;
    Slider saf;
    Label lef;
    Slider sef;
    Label lavf;
    Slider savf;
    Label lvmf;
    Slider svmf;
    Label lmaf;
    Slider smaf;

    Label lfr;
    Slider sfr;


};

class gmst_meditor:public gamestate
{
public:
    gmst_meditor(Font* f,Window &app);
    virtual ~gmst_meditor();
    virtual unsigned long Update(Window &app);

private:
    Button b_back;
    Button b_shape;
    Button b_draw;
    Slider s_scroll;
    Label l_r;
    Slider s_r;
    Label l_g;
    Slider s_g;
    Label l_b;
    Slider s_b;
    Label l_area;
    Slider s_density;
    Label l_density;
    Label l_mass;
    map<string,Image> module_textures;
    string selected;
    sf::Color color;
    int selected_texture;
    int hovered_texture;
    int drawvertices;
    unsigned int shape;
    double scroll;
    double density;
    bool prevmousestate;
    vector<Vector2d> vertices;
    double area;
    Vector2d center;
};

#include "geometry.h"

class gmst_game:public gamestate
{
public:
    gmst_game(Font* f,Window &app);
    virtual ~gmst_game();
    virtual unsigned long Update(Window &app);
private:

    vector<Triangle> triangle;
    int state;

    enum EDST {
        EDST_nothing,
        EDST_moving,
        EDST_rotating,
        EDST_drawing,
        EDST_deleting
    };

    int editstate;
    Vector2d editvector;
    bool editbool;
    Vector2d vtx[3];
    int tn;
    vector<Triangle>::iterator ed;
};

#endif
