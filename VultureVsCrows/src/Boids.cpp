/**
<VultureVsCrows 2d space shooter: "Boids.cpp">
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
#include "Boids.h"

bool compare_boids_x(Boid a,Boid b)
{
    return a.position.x<b.position.x;
}

bool compare_boids_y(Boid a,Boid b)
{
    return a.position.y<b.position.y;
}

vector<Boid>::iterator Construct_Tree(vector<Boid>::iterator start,vector<Boid>::iterator end,vector<Boid>::iterator null_iterator,vector<Connection>* tree=NULL,double xm=0,double xM=0, double ym=0, double yM=0,int depth=0)
{
    // If empty, return
    if (end-start<=0) return null_iterator;

    // Get axis to split along
    if(depth % 2)
        sort(start,end,compare_boids_x);
    else
        sort(start,end,compare_boids_y);



    int mid = (end-start) / 2;

    vector<Boid>::iterator b=(start+mid);


    if(tree!=NULL)
    {
        if(depth % 2)
            tree->push_back(Connection(Vector2d(b->position.x,ym),Vector2d(b->position.x,yM),depth));
        else
            tree->push_back(Connection(Vector2d(xm,b->position.y),Vector2d(xM,b->position.y),depth));
    }

    ///get iterator to mid

    double midd=(depth % 2)?b->position.x:b->position.y;

    if(depth % 2)
    {
        b->left   = Construct_Tree(start,      start+mid,null_iterator,tree,xm,midd,ym,yM, depth + 1);
        b->right  = Construct_Tree(start+mid+1,  end,null_iterator,tree,midd,xM,ym,yM, depth + 1);
    }
    else
    {
        b->left   = Construct_Tree(start,      start+mid,null_iterator,tree,xm,xM,ym,midd, depth + 1);
        b->right  = Construct_Tree(start+mid+1,  end,null_iterator,tree,xm,xM,midd,yM, depth + 1);
    }

    return b;
}

Boid::Boid(double ratio,RND *rnd)
{
    double speed=1;



    double pos=rnd->sign();

    position.x=rnd->real1()*ratio+pos*2*ratio;
    position.y=(pos==1)?-rnd->real():rnd->real();
    velocity.x=rnd->real1()*speed;
    velocity.y=rnd->real1()*speed;
    color=sf::Color(rnd->real()*200,rnd->real()*200,255);

    nv[0]=Vector2d(0,0);
    nv[1]=Vector2d(0,0);
    nv[2]=Vector2d(0,0);
    nv[3]=Vector2d(0,0);
    counter=0;
    faded=255;


}

Boid::~Boid()
{

}

Connection::Connection(Vector2d a,Vector2d b,sf::Color ca,sf::Color cb)
{
    p1=a;
    p2=b;
    c1=ca;
    c2=cb;
}
Connection::Connection(Vector2d a,Vector2d b,int depth)
{
    p1=a;
    p2=b;
    c1=sf::Color(0,100,255,20+1./(depth+1)*235);
    c2=sf::Color(0,100,255,20+1./(depth+1)*235);
}

Connection::~Connection()
{

}


Boids::Boids(Window &App,double screen_ratio,lua_State *l):ratio(screen_ratio),L(l)
{

    texture=App.GetTex("boid");
    line_texture=App.GetTex("line");

    rnd=RND::Instance();

    load_boid_settings();

    for(int i=0;i<num_boids;i++)
        boids.push_back(Boid(ratio,rnd));

    backs_prog=App.backs_prog;
    fboId=App.fboId;
    fboTextureId=App.fboTextureId;
    appratio=App.ratio;
}

Boids::~Boids()
{
    save_boid_settings();
}

void Boids::search_tree(vector<Boid>::iterator node,vector<Boid>::iterator boid,vector<Boid>::iterator null_iterator,int depth=0)
{
    double wn,wb;
    if(depth % 2)
    {
        wn=node->position.x;
        wb=boid->position.x;
    }
    else
    {
        wn=node->position.y;
        wb=boid->position.y;
    }


    if(perception-fabs(wb-wn)<=0)
    {
        if(wb<wn&&node->left!=null_iterator)
            search_tree(node->left,boid,null_iterator,depth+1);
        else if(wb>wn&&node->right!=null_iterator)
            search_tree(node->right,boid,null_iterator,depth+1);

        return;
    }
    else
    {
        Vector2d r=node->position-boid->position;
        double r1=r.Lenght();
        if(boid<node&&r1<perception)
        {
            double fadei,fadej;

            if(track_connections)
                connections.push_back(Connection(boid->position,node->position,boid->color,node->color));


            boid->nv[0]+=node->position;
            node->nv[0]+=boid->position;
            boid->nv[3]+=node->velocity;
            node->nv[3]+=boid->velocity;
            boid->counter++;
            node->counter++;
            if(r1<avoidance)
            {
                fadei=boid->faded/255.0;
                fadej=node->faded/255.0;
                boid->nv[2]-=r*avoidance_force*avoidance/r1*fadej;
                node->nv[2]+=r*avoidance_force*avoidance/r1*fadei;
            }
        }
        if(node->left!=null_iterator)search_tree(node->left,boid,null_iterator,depth+1);
        if(node->right!=null_iterator)search_tree(node->right,boid,null_iterator,depth+1);

    }
}


void Boids::Update(Window &App)
{
    glUseProgramObjectARB(backs_prog);
    float mousecoords[2]={(App.GetInput().GetMouseX()*1.0/App.GetHeight()*2.-App.ratio)/2,-(App.GetInput().GetMouseY()*1.0/App.GetHeight()*2.-1.)};
    glUniform2fv(glGetUniformLocation(backs_prog,  "mousepos"), 1, mousecoords);
    glUseProgramObjectARB(0);

    if(pause)
        return;

    double dt=std::min(App.GetFrameTime(),0.1f);

    unsigned int change_num=num_boids-boids.size();

    if(change_num>0)
        for(unsigned int i=0;i<change_num;i++)
            boids.push_back(Boid(ratio,rnd));

    if(track_connections)
        connections.clear();
    if(draw_tree)
        tree.clear();

    ///construct tree
    vector<Boid>::iterator tree_first=Construct_Tree(boids.begin(),boids.end(),boids.end(),((draw_tree)?&tree:NULL),-App.ratio,App.ratio,-1, 1);

    Vector2d r;
    double r1;
    double fadei,fadej;


    for(vector<Boid>::iterator i=boids.begin();i!=boids.end();i++)
    {
        i->position+=i->velocity*dt;

        if(App.GetInput().IsMouseButtonDown(sf::Mouse::Right))
        {
            r=Vector2d(App.GetInput().GetMouseX(),App.GetInput().GetMouseY());
            r.x=r.x*1.0/App.GetHeight()*2.-App.ratio;
            r.y=-(r.y*1.0/App.GetHeight()*2.-1.);


            r=r-i->position;
            r1=r.Lenght();
            if(r1<mouse_avoidance)
            {
                i->nv[2]-=r*mouse_avoidance_force*mouse_avoidance/r1*i->faded/255.0;
                //cerr<<r1<<endl;
            }

        }

        if(!brute_force)
            search_tree(tree_first,i,boids.end());
        else
        {
            for(vector<Boid>::iterator j=i;j!=boids.end();j++)
            {
                if(j==i)
                    continue;


                r=j->position-i->position;
                r1=r.Lenght();
                if(r1<perception)///search tree
                {
                    if(track_connections)
                        connections.push_back(Connection(i->position,j->position,i->color,j->color));


                    i->nv[0]+=j->position;
                    j->nv[0]+=i->position;
                    i->nv[3]+=j->velocity;
                    j->nv[3]+=i->velocity;
                    i->counter++;
                    j->counter++;
                    if(r1<avoidance)///search subtree
                    {
                        fadei=i->faded/255.0;
                        fadej=j->faded/255.0;
                        i->nv[2]-=r*avoidance_force*avoidance/r1*fadej;
                        j->nv[2]+=r*avoidance_force*avoidance/r1*fadei;
                    }
                }

            }
        }


        if(i->counter!=0)
        {
            r=i->nv[0]/i->counter-i->position;
            r1=r.Lenght();
            i->nv[0]=(r)*attraction_force*perception/r1;
            i->nv[3]=(i->nv[3]/i->counter-i->velocity)*velocity_matching_force;
        }

		if(i->position.x < -ratio)
			i->nv[1].x = edge_force;
		else if(i->position.x > ratio)
			i->nv[1].x = -edge_force;
		if(i->position.y < -1.)
			i->nv[1].y = edge_force;
		else if(i->position.y > 1.)
			i->nv[1].y = -edge_force;


        i->velocity+=(i->nv[0]+i->nv[1]+i->nv[2]+i->nv[3])*dt;
        i->velocity=limit_velocity(i->velocity);

        i->nv[0]=Vector2d(0,0);//velocity matching
        i->nv[1]=Vector2d(0,0);//atraction
        i->nv[2]=Vector2d(0,0);//edge
        i->nv[3]=Vector2d(0,0);//avoidance
        i->counter=0;

        if(i->faded!=255)
            i->faded-=1;
        else if(rnd->real()<fading_rate*dt)
            i->faded-=1;
    }

    ///clean tree

    boids.erase(remove_if(boids.begin(),boids.end(),faded_boid), boids.end());

}

void Boids::Draw()
{
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);
    //glClear(GL_COLOR_BUFFER_BIT );
     glBindTexture(GL_TEXTURE_2D, 0);

    glColor4f(0.0,0.0,0.0,1.-motionblur);
    glBegin( GL_QUADS );
        glTexCoord2f( 0., 1.0); glVertex2d( -appratio, 1 );
        glTexCoord2f( 1.0,1.0);glVertex2d( appratio, 1 );
        glTexCoord2f( 1.0, 0);glVertex2d( appratio, -1 );
        glTexCoord2f( 0., 0);glVertex2d( -appratio, -1 );
    glEnd( );




    if(draw_tree)
    {
        Vector2d v;
        double sc;

        glBindTexture( GL_TEXTURE_2D, line_texture);

        for(vector<Connection>::iterator l=tree.begin();l!=tree.end();l++)
        {
            glPushMatrix();

            v=(l->p1+l->p2)/2;
            glTranslated( v.x, v.y, 0 );
            v=(l->p1-l->p2);
            sc=v.Lenght()/2;
            glRotated(atan2(v.x,-v.y)*180/M_PI,0.0,0.0,1.0);
            glScaled(0.005,sc,1.);



            glBegin( GL_QUADS );
                glColorsf(l->c2);
                glTexCoord2f( 0., 1.0); glVertex2d( -1, 1 );
                glTexCoord2f( 1.0,1.0);glVertex2d( 1, 1 );
                glColorsf(l->c1);
                glTexCoord2f( 1.0, 0);glVertex2d( 1, -1 );
                glTexCoord2f( 0., 0);glVertex2d( -1, -1 );

            glEnd( );

            glPopMatrix();
        }

    }
    glUseProgramObjectARB(backs_prog);

    glMatrixMode( GL_MODELVIEW );


    glBindTexture( GL_TEXTURE_2D, texture );
    for(vector<Boid>::iterator it=boids.begin();it!=boids.end();it++)
    {
        it->color.a = max(it->faded,0);
        glColorsf(it->color);

        glPushMatrix();

        glTranslated( it->position.x, it->position.y, 0 );
        glRotated(atan2(it->velocity.x,-it->velocity.y)*180/M_PI,0.0,0.0,1.0);



        glBegin( GL_QUADS );
            glTexCoord2f( 1.0,1.0);glVertex2d( boid_size/2, boid_size/2 );
            glTexCoord2f( 1.0, 0);glVertex2d( boid_size/2, -boid_size/2 );
            glTexCoord2f( 0., 0);glVertex2d( -boid_size/2, -boid_size/2 );
            glTexCoord2f( 0., 1.0); glVertex2d( -boid_size/2, boid_size/2 );
        glEnd( );

        glPopMatrix();
    }



    if(track_connections)
    {
        Vector2d v;
        double sc;

        glBindTexture( GL_TEXTURE_2D, line_texture);

        for(vector<Connection>::iterator l=connections.begin();l!=connections.end();l++)
        {
            glPushMatrix();

            v=(l->p1+l->p2)/2;
            glTranslated( v.x, v.y, 0 );
            v=(l->p1-l->p2);
            sc=v.Lenght()/2;
            glRotated(atan2(v.x,-v.y)*180/M_PI,0.0,0.0,1.0);
            glScaled(sc*linewidth,sc*linelength,1.);



            glBegin( GL_QUADS );
                glColorsf(l->c2);
                glTexCoord2f( 0., 1.0); glVertex2d( -1, 1 );
                glTexCoord2f( 1.0,1.0);glVertex2d( 1, 1 );
                glColorsf(l->c1);
                glTexCoord2f( 1.0, 0);glVertex2d( 1, -1 );
                glTexCoord2f( 0., 0);glVertex2d( -1, -1 );

            glEnd( );

            glPopMatrix();
        }

    }
    glUseProgramObjectARB(0);

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    glBindTexture(GL_TEXTURE_2D, fboTextureId);

    glColor4f(1.0,1.0,1.0,1.0);
    glBegin( GL_QUADS );
        glTexCoord2f( 0., 1.0); glVertex2d( -appratio, 1 );
        glTexCoord2f( 1.0,1.0);glVertex2d( appratio, 1 );
        glTexCoord2f( 1.0, 0);glVertex2d( appratio, -1 );
        glTexCoord2f( 0., 0);glVertex2d( -appratio, -1 );
    glEnd( );

    glBindTexture(GL_TEXTURE_2D, 0);





}

void Boids::Reset()
{
    connections.clear();
    boids.clear();

    for(int i=0;i<num_boids;i++)
        boids.push_back(Boid(ratio,rnd));
}

double Boids::distance(Boid a, Boid b)
{
    Vector2d v=a.position-b.position;
    return v.Lenght();

}

Vector2d Boids::limit_velocity(Vector2d v)
{
    if(v.Lenght()>limit_speed)
        v=v.Normalize()*limit_speed;
    if(v.Lenght()<limit_min_speed)
        v=v.Normalize()*limit_min_speed;
    return v;
}

bool Boids::faded_boid(const Boid& b)
{
    return b.faded<=0;
}

void Boids::load_boid_settings()
{
    bool take_default=false;

    if (luaL_dofile(L,boid_settings_file.c_str()))
    {
        take_default=true;
        cerr<< "taking default background settings";
    }



    boid_size               =Lget_double_or_default(L,"boid_size",0.02,take_default);
    limit_speed             =Lget_double_or_default(L,"limit_speed",.8 ,take_default);
    limit_min_speed         =Lget_double_or_default(L,"limit_min_speed",0.3,take_default);
    perception              =Lget_double_or_default(L,"perception",0.15,take_default);
    avoidance               =Lget_double_or_default(L,"avoidance",0.05,take_default);
    mouse_avoidance         =Lget_double_or_default(L,"mouse_avoidance",0.2,take_default);
    attraction_force        =Lget_double_or_default(L,"attraction_force",2,take_default);
    edge_force              =Lget_double_or_default(L,"edge_force",0.6,take_default);
    avoidance_force         =Lget_double_or_default(L,"avoidance_force",10,take_default);
    mouse_avoidance_force   =Lget_double_or_default(L,"mouse_avoidance_force",10,take_default);
    velocity_matching_force =Lget_double_or_default(L,"velocity_matching_force",1,take_default);
    fading_rate             =Lget_double_or_default(L,"fading_rate",0.03,take_default);
    num_boids               =Lget_double_or_default(L,"num_boids",300,take_default);
    linewidth               =Lget_double_or_default(L,"linewidth",0.067,take_default);
    linelength              =Lget_double_or_default(L,"linelength",0.6,take_default);
    motionblur              =Lget_double_or_default(L,"motionblur",0.4,take_default);
    track_connections       =Lget_bool_or_default(L,"track_connections",false,take_default);
    draw_tree               =Lget_bool_or_default(L,"draw_tree",true,take_default);
    brute_force             =Lget_bool_or_default(L,"brute_force",false,take_default);
    pause                   =Lget_bool_or_default(L,"pause",false,take_default);



}
void Boids::save_boid_settings()
{
    ofstream sfile(boid_settings_file.c_str());
    if (sfile.is_open())
    {
        sfile << "boid_size"                <<" = "<<boid_size                      <<endl;
        sfile << "limit_speed"              <<" = "<<limit_speed                    <<endl;
        sfile << "limit_min_speed"          <<" = "<<limit_min_speed                <<endl;
        sfile << "perception"               <<" = "<<perception                     <<endl;
        sfile << "avoidance"                <<" = "<<avoidance                      <<endl;
        sfile << "mouse_avoidance"          <<" = "<<mouse_avoidance                <<endl;
        sfile << "attraction_force"         <<" = "<<attraction_force               <<endl;
        sfile << "edge_force"               <<" = "<<edge_force                     <<endl;
        sfile << "avoidance_force"          <<" = "<<avoidance_force                <<endl;
        sfile << "mouse_avoidance_force"    <<" = "<<mouse_avoidance_force          <<endl;
        sfile << "velocity_matching_force"  <<" = "<<velocity_matching_force        <<endl;
        sfile << "fading_rate"              <<" = "<<fading_rate                    <<endl;
        sfile << "num_boids"                <<" = "<<num_boids                      <<endl;
        sfile << "linewidth"                <<" = "<<linewidth                      <<endl;
        sfile << "linelength"               <<" = "<<linelength                     <<endl;
        sfile << "motionblur"               <<" = "<<motionblur                     <<endl;
        sfile << "track_connections"        <<" = "<<(track_connections?"true":"false")<<endl;
        sfile << "draw_tree"                <<" = "<<(draw_tree?"true":"false")     <<endl;
        sfile << "brute_force"              <<" = "<<(brute_force?"true":"false")   <<endl;
        sfile << "pause"                    <<" = "<<(pause?"true":"false")         <<endl;


        sfile.close();
    }
}
/**
        *sfile << "limit_speed"              <<" = "<<limit_speed                    <<endl;
        *sfile << "limit_min_speed"          <<" = "<<limit_min_speed                <<endl;
        *sfile << "motionblur"               <<" = "<<motionblur                     <<endl;
        *sfile << "mouse_avoidance"          <<" = "<<mouse_avoidance                <<endl;
        *sfile << "attraction_force"         <<" = "<<attraction_force               <<endl;
        *sfile << "edge_force"               <<" = "<<edge_force                     <<endl;
        *sfile << "avoidance_force"          <<" = "<<avoidance_force                <<endl;
        *sfile << "mouse_avoidance_force"    <<" = "<<mouse_avoidance_force          <<endl;
        *sfile << "velocity_matching_force"  <<" = "<<velocity_matching_force        <<endl;
        sfile << "fading_rate"              <<" = "<<fading_rate                    <<endl;
        *sfile << "perception"               <<" = "<<perception                     <<endl;
        *sfile << "avoidance"                <<" = "<<avoidance                      <<endl;
        *sfile << "num_boids"                <<" = "<<num_boids                      <<endl;
        *sfile << "track_connections"        <<" = "<<(track_connections?"true":"false")<<endl;
        *sfile << "draw_tree"                <<" = "<<(draw_tree?"true":"false")     <<endl;
        *sfile << "brute_force"              <<" = "<<(brute_force?"true":"false")   <<endl;
        *sfile << "pause"                    <<" = "<<(pause?"true":"false")         <<endl;

*/
