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

class Window:public sf::Window
{
public:
    Window();
    virtual ~Window();
    void Reset(int VMn);

    void Display();

    Image GetTex(string s);
    unsigned int GetVideoModeNum();
    const sf::Input& GetInput() const;

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
    void Load_Images();

    map<string,Image> imagelist;
    string title;
    sf::VideoMode VM;
    sf::WindowSettings WSettings;
};

string GetVideoModeString(int i);
void glColorsf(sf::Color c);




#endif
