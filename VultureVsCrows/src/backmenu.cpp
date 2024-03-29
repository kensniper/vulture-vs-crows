/**
<VultureVsCrows 2d space shooter: "backmenu.cpp">
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

gmst_backmenu::gmst_backmenu(Font* f,Window &app,Boids *b):gamestate(f)
{
    boids=b;
    wasdown=false;
    change=false;
    visible = true;

    double bxm=-app.ratio+0.01,bxM=-app.ratio+0.71;
    double byM=0.99;
    double bheigth=0.06;
    double bspacing=-0.01;



    tooltip.Set(-.72,.72,-0.93,-0.99,app.GetTex("label"),f,"You can play with particles with right mouse button.");
    hide.Set(-app.ratio+0.33,-app.ratio+0.01,-0.94,-0.99,app.GetTex("button"),f,"Hide GUI (H)");




    lnumpart.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"N = ");
    nslider.Set(bxM+0.62,bxm+0.72,byM,byM-bheigth,app.GetTex("slider"),200,4000,boids->num_boids);byM-=bheigth+bspacing;
    plabel.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"perception = ");
    pslider.Set(bxM+0.62,bxm+0.72,byM,byM-bheigth,app.GetTex("slider"),0.05,0.4,boids->perception);byM-=bheigth+bspacing;
    alabel.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"avoidance = ");
    aslider.Set(bxM+0.62,bxm+0.72,byM,byM-bheigth,app.GetTex("slider"),0.01,0.1,boids->avoidance);byM-=bheigth+bspacing;

    lslimit.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"speed limit = ");
    sslimit.Set(bxM+0.62,bxm+0.72,byM,byM-bheigth,app.GetTex("slider"),0.5,1.0,boids->limit_speed);byM-=bheigth+bspacing;
    lmslimit.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"min speed limit = ");
    smslimit.Set(bxM+0.62,bxm+0.72,byM,byM-bheigth,app.GetTex("slider"),0.00,0.5,boids->limit_min_speed);byM-=bheigth+bspacing;

    lma.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"mouse influence = ");
    sma.Set(bxM+0.62,bxm+0.72,byM,byM-bheigth,app.GetTex("slider"),0.05,0.5,boids->mouse_avoidance);byM-=bheigth+bspacing;
    laf.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"atraction force= ");
    saf.Set(bxM+0.62,bxm+0.72,byM,byM-bheigth,app.GetTex("slider"),0.1,5,boids->attraction_force);byM-=bheigth+bspacing;
    lef.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"edge force = ");
    sef.Set(bxM+0.62,bxm+0.72,byM,byM-bheigth,app.GetTex("slider"),0.1,5,boids->edge_force);byM-=bheigth+bspacing;
    lavf.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"avoidance force = ");
    savf.Set(bxM+0.62,bxm+0.72,byM,byM-bheigth,app.GetTex("slider"),1,20,boids->avoidance_force);byM-=bheigth+bspacing;
    lvmf.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"velocity force = ");
    svmf.Set(bxM+0.62,bxm+0.72,byM,byM-bheigth,app.GetTex("slider"),0.1,5,boids->velocity_matching_force);byM-=bheigth+bspacing;
    lmaf.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"mouse force = ");
    smaf.Set(bxM+0.62,bxm+0.72,byM,byM-bheigth,app.GetTex("slider"),1,20,boids->mouse_avoidance_force);byM-=bheigth+bspacing;
    lfr.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"fading rate = ");
    sfr.Set(bxM+0.62,bxm+0.72,byM,byM-bheigth,app.GetTex("slider"),0.0,0.1,boids->fading_rate);byM-=bheigth+bspacing;
    lmblur.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"motion blur = ");
    smblur.Set(bxM+0.62,bxm+0.72,byM,byM-bheigth,app.GetTex("slider"),0.0,1.0,boids->motionblur);byM-=bheigth+bspacing;


    byM-=0.2;
    bheigth=0.1;

    con.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("button"),f,"Show connections");byM-=bheigth+bspacing;
    dtree.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("button"),f,"Show tree");byM-=bheigth+bspacing;
    ushade.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("button"),f,"Shaders: True");byM-=bheigth+bspacing;
    bforce.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("button"),f,"Calc with KD tree");byM-=bheigth+bspacing;
    reset.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("button"),f,"Restart");byM-=bheigth+bspacing;
    pauseb.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("button"),f,"Pause");byM-=bheigth+bspacing;
    back.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("button"),f,"Enough of this");byM-=bheigth+bspacing;



    if(!boids->track_connections)
        con.SetText("Show connections");
    else
        con.SetText("Hide connections");

    if(!boids->draw_tree)
        dtree.SetText("Show tree");
    else
        dtree.SetText("Hide tree");

    if(boids->brute_force)
        bforce.SetText("KD tree calculations");
    else
        bforce.SetText("Brute force calculations");

    if(!boids->pause)
        pauseb.SetText("Pause");
    else
        pauseb.SetText("Unpause");

    if(boids->use_shaders)
        ushade.SetText("Shaders: True");
    else
        ushade.SetText("Shaders: False");

    AddToList(&con);
    AddToList(&dtree);
    AddToList(&bforce);
    AddToList(&ushade);
    AddToList(&reset);
    AddToList(&pauseb);
    AddToList(&back);
    AddToList(&tooltip);
    AddToList(&hide);
    AddToList(&lnumpart);
    AddToList(&nslider);
    AddToList(&plabel);
    AddToList(&pslider);
    AddToList(&alabel);
    AddToList(&aslider);

    AddToList(&lslimit);
    AddToList(&sslimit);
    AddToList(&lmslimit);
    AddToList(&smslimit);
    AddToList(&lmblur);
    AddToList(&smblur);
    AddToList(&lma);
    AddToList(&sma);

    AddToList(&laf);
    AddToList(&saf);
    AddToList(&lef);
    AddToList(&sef);
    AddToList(&lavf);
    AddToList(&savf);
    AddToList(&lvmf);
    AddToList(&svmf);
    AddToList(&lmaf);
    AddToList(&smaf);

    AddToList(&lfr);
    AddToList(&sfr);


}

gmst_backmenu::~gmst_backmenu()
{

};

unsigned long gmst_backmenu::Update(Window &app)
{
    unsigned long state=0;

    if(nslider.active)
        lnumpart.SetText("N: %d(%d)",boids->num_boids,(int)nslider.GetValue());
    else
    {
        boids->num_boids=(int)nslider.GetValue();
        lnumpart.SetText("N: %d",boids->num_boids);
    }

    if(pslider.active)
        plabel.SetText("perception: %.4g(%.4g)",boids->perception,pslider.GetValue());
    else
    {
        boids->perception=pslider.GetValue();
        plabel.SetText("perception: %.4g",boids->perception);
    }

    if(aslider.active)
        alabel.SetText("avoidance: %.3g(%.3g)",boids->avoidance,aslider.GetValue());
    else
    {
        boids->avoidance=aslider.GetValue();
        alabel.SetText("avoidance: %.3g",boids->avoidance);
    }

    if(sslimit.active)
        lslimit.SetText("speed limit: %.3g(%.3g)",boids->limit_speed,sslimit.GetValue());
    else
    {
        boids->limit_speed=sslimit.GetValue();
        lslimit.SetText("speed limit: %.3g",boids->limit_speed);
    }

    if(smslimit.active)
        lmslimit.SetText("min speed limit: %.3g(%.3g)",boids->limit_min_speed,smslimit.GetValue());
    else
    {
        boids->limit_min_speed=smslimit.GetValue();
        lmslimit.SetText("min speed limit: %.3g",boids->limit_min_speed);
    }

    if(smblur.active)
        lmblur.SetText("motion blur: %.3g(%.3g)",boids->motionblur,smblur.GetValue());
    else
    {
        boids->motionblur=smblur.GetValue();
        lmblur.SetText("motion blur: %.3g",boids->motionblur);
    }

    if(sma.active)
        lma.SetText("mouse influence: %.3g(%.3g)",boids->mouse_avoidance,sma.GetValue());
    else
    {
        boids->mouse_avoidance=sma.GetValue();
        lma.SetText("mouse influence: %.3g",boids->mouse_avoidance);
    }

    if(saf.active)
        laf.SetText("atraction force: %.3g(%.3g)",boids->attraction_force,saf.GetValue());
    else
    {
        boids->attraction_force=saf.GetValue();
        laf.SetText("atraction force: %.3g",boids->attraction_force);
    }

    if(sef.active)
        lef.SetText("edge force: %.3g(%.3g)",boids->edge_force,sef.GetValue());
    else
    {
        boids->edge_force=sef.GetValue();
        lef.SetText("edge force: %.3g",boids->edge_force);
    }

    if(savf.active)
        lavf.SetText("avoidance force: %.3g(%.3g)",boids->avoidance_force,savf.GetValue());
    else
    {
        boids->avoidance_force=savf.GetValue();
        lavf.SetText("avoidance force: %.3g",boids->avoidance_force);
    }

    if(svmf.active)
        lvmf.SetText("velocity force: %.3g(%.3g)",boids->velocity_matching_force,svmf.GetValue());
    else
    {
        boids->velocity_matching_force=svmf.GetValue();
        lvmf.SetText("velocity force: %.3g",boids->velocity_matching_force);
    }

    if(smaf.active)
        lmaf.SetText("mouse force: %.3g(%.3g)",boids->mouse_avoidance_force,smaf.GetValue());
    else
    {
        boids->mouse_avoidance_force=smaf.GetValue();
        lmaf.SetText("mouse force: %.3g",boids->mouse_avoidance_force);
    }

    if(sfr.active)
        lfr.SetText("fading rate: %.3g(%.3g)",boids->fading_rate ,sfr.GetValue());
    else
    {
        boids->fading_rate =sfr.GetValue();
        lfr.SetText("fading rate: %.3g",boids->fading_rate );
    }
    //lslimit "speed limit = "
    //sslimit boids->limit_speed
    //lmslimit "min speed limit = "
    //smslimit boids->limit_min_speed
    //lmblur "motion blur = "
    //smblur boids->motionblur
    //lma "mouse influence = "
    //sma boids->mouse_avoidance
    //laf "atraction force= "
    //saf boids->attraction_force
    //lef "edge force = "
    //sef boids->edge_force
    //lavf "avoidance force = "
    //savf boids->avoidance_force
    //lvmf "velocity force = "
    //svmf boids->velocity_matching_force
    //lmaf "mouse force = "
    //smaf boids->mouse_avoidance_force
    //lfr "fading rate = "
    //sfr boids->fading_rate



    if(lnumpart.hovered)
        tooltip.SetText("Number of particles in simulation.");
    else if(plabel.hovered)
        tooltip.SetText("How far particles see.");
    else if(alabel.hovered)
        tooltip.SetText("How far particles repel.");
    else if(con.hovered)
        tooltip.SetText("Not recomended for N > 1000.");
    else if(bforce.hovered)
        tooltip.SetText("Not recomended for N > 1000.");
    else
        tooltip.SetText("You can play with particles with right mouse button.");








    if(con.pressed)
    {
        boids->track_connections=!boids->track_connections;
        if(!boids->track_connections)
            con.SetText("Show connections");
        else
            con.SetText("Hide connections");
    }
    if(dtree.pressed)
    {
        boids->draw_tree=!boids->draw_tree;
        if(!boids->draw_tree)
            dtree.SetText("Show tree");
        else
            dtree.SetText("Hide tree");
    }
    if(bforce.pressed)
    {
        boids->brute_force=!boids->brute_force;
        if(boids->brute_force)
            bforce.SetText("KD tree calculations");
        else
            bforce.SetText("Brute force calculations");
    }

    if(pauseb.pressed)
    {
        boids->pause=!boids->pause;
        if(!boids->pause)
            pauseb.SetText("Pause");
        else
            pauseb.SetText("Unpause");
    }

    if(ushade.pressed)
    {
        boids->use_shaders=!boids->use_shaders;
        if(boids->use_shaders)
            ushade.SetText("Shaders: True");
        else
            ushade.SetText("Shaders: False");
    }


    if(reset.pressed)
        boids->Reset();

    if(back.pressed)
        state=GMST::toMainMenu;

    change=(!wasdown&&app.GetInput().IsKeyDown(sf::Key::H));
    wasdown=app.GetInput().IsKeyDown(sf::Key::H);

    if(hide.pressed||change)
    {
        visible=!visible;

        ushade.SetVisible(visible);
        con.SetVisible(visible);
        dtree.SetVisible(visible);
        bforce.SetVisible(visible);
        pauseb.SetVisible(visible);
        reset.SetVisible(visible);
        back.SetVisible(visible);
        tooltip.SetVisible(visible);
        lnumpart.SetVisible(visible);
        nslider.SetVisible(visible);
        pslider.SetVisible(visible);
        plabel.SetVisible(visible);
        aslider.SetVisible(visible);
        alabel.SetVisible(visible);
        lslimit.SetVisible(visible);
        sslimit.SetVisible(visible);
        lmslimit.SetVisible(visible);
        smslimit.SetVisible(visible);
        lmblur.SetVisible(visible);
        smblur.SetVisible(visible);
        lma.SetVisible(visible);
        sma.SetVisible(visible);
        laf.SetVisible(visible);
        saf.SetVisible(visible);
        lef.SetVisible(visible);
        sef.SetVisible(visible);
        lavf.SetVisible(visible);
        savf.SetVisible(visible);
        lvmf.SetVisible(visible);
        svmf.SetVisible(visible);
        lmaf.SetVisible(visible);
        smaf.SetVisible(visible);
        lfr.SetVisible(visible);
        sfr.SetVisible(visible);
    }

    return state;
}
