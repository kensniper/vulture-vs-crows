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
