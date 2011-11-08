/**
<VultureVsCrows 2d space shooter: "Boids.h">
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
#ifndef BOIDS_H
#define BOIDS_H

#include "Startup.h"
#include "Vector2d.h"
#include "random.h"
#include "lua_util.h"
#include <algorithm>
#include <list>
#include <vector>

static std::string boid_settings_file="resources/background.lua";

struct Connection
{
    Connection(Vector2d a,Vector2d b,sf::Color ca,sf::Color cb);
    Connection(Vector2d a,Vector2d b,int depth);
    ~Connection();

    Vector2d p1;
    Vector2d p2;
    sf::Color c1;
    sf::Color c2;
};

struct Boid
{
    Boid(double ratio,RND *rnd);
    ~Boid();


    Vector2d position;
    Vector2d velocity;
    Vector2d nv[4];
    int counter;
    sf::Color color;
    int faded;
    vector<Boid>::iterator left;
    vector<Boid>::iterator right;
};

bool compare_boids_x(Boid a,Boid b);
bool compare_boids_y(Boid a,Boid b);

vector<Boid>::iterator Construct_Tree(vector<Boid>::iterator start,vector<Boid>::iterator end,vector<Boid>::iterator null_iterator,vector<Connection>* tree,double xm,double xM, double ym, double yM,int depth);

class Boids
{
    public:
        Boids(Window &App,double screen_ratio,lua_State *L);
        virtual ~Boids();
        void Update(Window &App);
        void Draw();
        void Reset();



        double perception;
        double avoidance;
        double mouse_avoidance;
        double attraction_force;
        double edge_force;
        double avoidance_force;
        double mouse_avoidance_force;
        double velocity_matching_force;
        double limit_speed;
        double limit_min_speed;
        double fading_rate;
        double motionblur;
        int num_boids;
        bool track_connections;
        bool draw_tree;
        bool brute_force;
        bool pause;
        bool use_shaders;


    protected:
    private:


        static bool faded_boid(const Boid& b);
        void search_tree(vector<Boid>::iterator node,vector<Boid>::iterator boid,vector<Boid>::iterator null_iterator,int depth);

        void load_boid_settings();
        void save_boid_settings();

        double distance(Boid a, Boid b);
        Vector2d limit_velocity(Vector2d v);


        std::vector<Boid> boids;
        std::vector<Connection> connections;
        std::vector<Connection> tree;
        GLuint texture;
        GLuint line_texture;

        double linewidth;
        double linelength;
        double boid_size;
        double ratio;
        RND *rnd;
        lua_State *L;
        GLhandleARB backs_prog;
        GLuint fboId;
        GLuint fboTextureId;
        double appratio;
};



#endif // BOIDS_H
