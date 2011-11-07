/**
<VultureVsCrows 2d space shooter: "main.cpp">
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




int main()
{
    Window App;
    Font f(App,"font");



    Label FPS_label(App.ratio-0.01,App.ratio-0.27,0.99,0.94,App.GetTex("label"),&f,"BLA");
    Boids boids(App,App.ratio,App.L);

    int state=0;
    gmst_mainmenu mainmenu(&f,App);
    gmst_settingsmenu settingsmenu(&f,App);
    gmst_backmenu backmenu(&f,App,&boids);
    gamestate *curstate;
    curstate = &mainmenu;

    sf::Event Event;
    bool Running = true;
    while (Running)
    {
        state=0;
        while (App.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                Running = false;
        }

        boids.Update(App);
        boids.Draw();

        state = curstate->Process(App);
        if(state==GMST::exitGame)
            Running = false;
        else if(state==GMST::toSettingsMenu)
            curstate = &settingsmenu;
        else if(state==GMST::toMainMenu)
            curstate = &mainmenu;
        else if(state==GMST::toBackgroundMenu)
            curstate = &backmenu;

        FPS_label.SetText( "FPS: %i",(int)(1./App.GetFrameTime()));
        FPS_label.Draw();

        App.Display();

    }

    return EXIT_SUCCESS;
}
