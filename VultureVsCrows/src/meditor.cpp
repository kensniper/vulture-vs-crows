#include "gamestates.h"

gmst_meditor::gmst_meditor(Font* f,Window &app):gamestate(f)
{
    app.Load_Images("module_textures",module_textures);

    selected_texture = 0;
    hovered_texture = -1;
    scroll=0;
    color=sf::Color::White;
    shape=0;
    drawvertices=0;


    area=0;
    center=Vector2d(0,0);
    density=1.0;

    prevmousestate=false;

    b_back.Set(app.ratio -0.01,app.ratio -0.41,-0.89,-0.99,app.GetTex("button"),f,"Go Back");

    s_scroll.Set(app.ratio+0.3,-app.ratio-0.3,0.8,0.77,app.GetTex("slider"),0.0,std::max(module_textures.size()*0.2-2*app.ratio,0.0),scroll);

    double bxm=-app.ratio+0.01,bxM=-app.ratio+0.21;
    double byM=0.75;
    double bheigth=0.06;
    double bspacing=-0.01;

    l_r.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"R");
    s_r.Set(bxM+0.52,bxm+0.22,byM,byM-bheigth,app.GetTex("slider"),0,255,color.r);byM-=bheigth+bspacing;
    l_g.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"G");
    s_g.Set(bxM+0.52,bxm+0.22,byM,byM-bheigth,app.GetTex("slider"),0,255,color.g);byM-=bheigth+bspacing;
    l_b.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"B");
    s_b.Set(bxM+0.52,bxm+0.22,byM,byM-bheigth,app.GetTex("slider"),0,255,color.b);byM-=bheigth+bspacing;

    l_density.Set(bxM=-app.ratio+0.35,-app.ratio+0.01,byM,byM-bheigth,app.GetTex("label"),f,"Density");
    s_density.Set(-app.ratio+0.8,-app.ratio+0.36,byM,byM-bheigth,app.GetTex("slider"),0.1,10,density);byM-=bheigth+bspacing;

    b_shape.Set(-app.ratio+0.46,-app.ratio+0.01,byM,byM-0.1,app.GetTex("button"),f,"Shape: ");
    b_draw.Set(-app.ratio+0.73,-app.ratio+0.48,byM,byM-0.1,app.GetTex("button"),f,"Draw");byM-=0.1+bspacing;

    if(shape==0)
        b_shape.SetText("Shape: Triangle");
    else if(shape==1)
        b_shape.SetText("Shape: Quad");

    bxm=app.ratio-0.61;
    bxM=app.ratio-0.01;
    byM=0.75;
    bheigth=0.06;
    bspacing=-0.01;
    l_area.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"Area/scale: ");byM-=bheigth+bspacing;
    l_mass.Set(bxM,bxm,byM,byM-bheigth,app.GetTex("label"),f,"mass/scale: ");byM-=bheigth+bspacing;
    l_area.SetText("Area/scale: %g",area);
    l_mass.SetText("Mass/scale: %g",density*area);



    AddToList(&b_back);
    AddToList(&s_scroll);
    AddToList(&l_r);
    AddToList(&s_r);
    AddToList(&l_g);
    AddToList(&s_g);
    AddToList(&l_b);
    AddToList(&s_b);
    AddToList(&b_shape);
    AddToList(&b_draw);
    AddToList(&l_area);
    AddToList(&l_density);
    AddToList(&s_density);
    AddToList(&l_mass);
}

gmst_meditor::~gmst_meditor()
{
}

unsigned long gmst_meditor::Update(Window &app)
{
    unsigned long state=0;

    if(b_back.pressed)
        state=GMST::toMainMenu;

    const sf::Input* input=&app.GetInput();
    double x=input->GetMouseX();
    double y=input->GetMouseY();
    x=x*1.0/app.GetHeight()*2.-app.ratio;
    y=-(y*1.0/app.GetHeight()*2.-1.);


    density=s_density.GetValue();
    l_mass.SetText("Mass/scale: %g",density*area);
    l_density.SetText("Rho = %.3g",density);

    ///===========texture selection and edit========


    scroll=s_scroll.GetValue();
    color=sf::Color(s_r.GetValue(),s_g.GetValue(),s_b.GetValue());


    if(y>0.8)
    {
        hovered_texture=(x+app.ratio+scroll)/0.2;///add scroll here
        if(input->IsMouseButtonDown(sf::Mouse::Left))
        {
            selected_texture=hovered_texture;
        }
    }
    else
        hovered_texture=-1;


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslated(-app.ratio-scroll,0.8,0);///add scroll here
    int i=0;
    for(map<string,Image>::iterator it=module_textures.begin();it!=module_textures.end();it++)
    {
        if(i==selected_texture)
        {
            selected=it->first;

            glBindTexture(GL_TEXTURE_2D, 0);
            glColor4f(0.0,0.0,1.0,0.2);
            glBegin(GL_QUADS);
                glVertex2d( 0.2, 0.0 );
                glVertex2d( 0.0, 0.0 );
                glVertex2d( 0.0, 0.2 );
                glVertex2d( 0.2, 0.2 );
            glEnd();
        }
        if(i==hovered_texture)
        {
            glBindTexture(GL_TEXTURE_2D, 0);
            glColor4f(0.0,1.0,0.0,0.2);
            glBegin(GL_QUADS);
                glVertex2d( 0.2, 0.0 );
                glVertex2d( 0.0, 0.0 );
                glVertex2d( 0.0, 0.2 );
                glVertex2d( 0.2, 0.2 );
            glEnd();
        }

        glBindTexture(GL_TEXTURE_2D, it->second);

        glColorsf(color);
        glBegin(GL_QUADS);
            glTexCoord2f( 1.0, 1.0);glVertex2d( 0.175, 0.025 );
            glTexCoord2f( 0., 1.0);glVertex2d( 0.025, 0.025 );
            glTexCoord2f( 0., 0.0); glVertex2d( 0.025, 0.175 );
            glTexCoord2f( 1.0,0.0);glVertex2d( 0.175, 0.175 );
        glEnd();

        glTranslated(0.2,0.0,0);
        i++;
    }
    glLoadIdentity();
    glColor3f(0.0,0.0,1.0);
    glBindTexture(GL_TEXTURE_2D, app.GetTex("line"));

    for(i=0;i<4;i++)
    {
        glRotated(90.0,0.0,0.0,1.0);
        glBegin(GL_QUADS);
            glTexCoord2f( 1.0, 1.0);glVertex2d( -0.765,0.77 );
            glTexCoord2f( 0., 1.0);glVertex2d( -0.765,0.75 );
            glTexCoord2f( 0., 0.0); glVertex2d( 0.765,0.75 );
            glTexCoord2f( 1.0,0.0);glVertex2d( 0.765,0.77 );
        glEnd();
    }
    glLoadIdentity();
    glColorsf(color);
    glBindTexture(GL_TEXTURE_2D, module_textures[selected]);
    glBegin(GL_QUADS);
        glTexCoord2f( 1.0, 1.0);glVertex2d( 0.76,0.76 );
        glTexCoord2f( 0., 1.0);glVertex2d( -0.76,0.76 );
        glTexCoord2f( 0., 0.0); glVertex2d( -0.76,-0.76 );
        glTexCoord2f( 1.0,0.0);glVertex2d( 0.76,-0.76 );
    glEnd();




    ///==========making vertices=====



    if(drawvertices>0)
    {
        bool change=false;
        if(x>0.76)
        {
            x=0.76;
            change=true;
        }
        if(y>0.76)
        {
            y=0.76;
            change=true;
        }
        if(x<-0.76)
        {
            x=-0.76;
            change=true;
        }
        if(y<-0.76)
        {
            y=-0.76;
            change=true;
        }
        if(change)app.SetCursorPosition((x+app.ratio)/2.*app.GetHeight(), (-y+1)/2.*app.GetHeight());

        if(prevmousestate&&!input->IsMouseButtonDown(sf::Mouse::Left))
        {
            vertices.push_back(Vector2d(x/0.76,y/0.76));
            drawvertices--;
        }

        if(drawvertices==0)
        {
            center=Vector2d(0,0);
            for(vector<Vector2d>::iterator it=vertices.begin();it!=vertices.end();it++)
                center+=*it;
            if(shape==0)
                center=center/3;
            if(shape==1)
                center=center/4;

            Vector2d r;
            double a,b,c,d,e,f,s;

            r=vertices[0]-vertices[1];
            a=r.Lenght();
            r=vertices[1]-vertices[2];
            b=r.Lenght();

            if(shape==0)
            {
                r=vertices[2]-vertices[0];
                c=r.Lenght();
                s=(a+b+c)/2;
                area=sqrt(s*(s-a)*(s-b)*(s-c));
            }

            if(shape==1)
            {
                r=vertices[2]-vertices[3];
                c=r.Lenght();
                r=vertices[3]-vertices[0];
                d=r.Lenght();
                r=vertices[1]-vertices[3];
                e=r.Lenght();
                r=vertices[2]-vertices[0];
                f=r.Lenght();

                area=0.25*sqrt(4*e*e*f*f-pow(a*a+c*c-b*b-d*d,2));
            }


            l_area.SetText("Area/scale: %g",area);

        }

    }

    glColor3f(0.0,0.0,1.0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable( GL_TEXTURE_2D );
    glScaled(0.76,0.76,0);
    glBegin(GL_POINTS);
        for(vector<Vector2d>::iterator it=vertices.begin();it!=vertices.end();it++)
            glVertex2d( it->x,it->y );

        glColor3f(1.0,0.0,0.0);
        glVertex2d( center.x,center.y );
    glEnd();
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
        for(vector<Vector2d>::iterator it=vertices.begin();it!=vertices.end();it++)
            glVertex2d( it->x,it->y );
    glEnd();
    glEnable( GL_TEXTURE_2D );

    if(b_shape.pressed)
    {
        shape=(shape+1)%2;
        if(shape==0)
            b_shape.SetText("Shape: Triangle");
        else if(shape==1)
            b_shape.SetText("Shape: Quad");
    }

    if(b_draw.pressed)
    {
        vertices.clear();
        if(shape==0)
            drawvertices=3;
        if(shape==1)
            drawvertices=4;

    }

    ///====================================

    prevmousestate=input->IsMouseButtonDown(sf::Mouse::Left);
    glPopMatrix();
    return state;
}
