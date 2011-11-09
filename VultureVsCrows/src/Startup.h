/**
<VultureVsCrows 2d space shooter: "startup.h">
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
#ifndef STARTUP
#define STARTUP

#include <GL/glew.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include "textfile.h"

#include "lua_util.h"
const string settings_file="resources/video_settings.lua";
const string log_file="resources/log.txt";
const string img_file="resources/images.lua";



class Image: public sf::Image
{
public:
    Image();
    bool LoadFromFile (const std::string &Filename);
    operator GLuint();

    GLuint texture;
};

class Window:public sf::RenderWindow
{
public:
    Window();
    virtual ~Window();
    void Reset(int VMn);

    void Display();

    Image GetTex(string s);
    unsigned int GetVideoModeNum();
    const sf::Input& GetInput() const;
    void Load_Images(string tablename,map<string,Image> &imagemap);

    void TakeScreenshot();

    lua_State *L;
    double ratio;
    ofstream *logstream;
    GLhandleARB backs_prog;
    GLuint fboId;
    GLuint fboTextureId;

private:
    GLhandleARB vertex_shader,fragment_shader;
    void init_window_n_gl();
    void load_video_settings(sf::VideoMode &VM,sf::WindowSettings &WSettings);
    void save_video_settings();

    bool take_screenshot;

    map<string,Image> imagelist;
    string title;
    sf::VideoMode VM;
    sf::WindowSettings WSettings;
};

string GetVideoModeString(int i);
void glColorsf(sf::Color c);




#endif
