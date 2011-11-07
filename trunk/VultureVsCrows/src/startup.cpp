#include "startup.h"
#include <sstream>

using namespace std;


Image::Image():sf::Image()
{

}

bool Image::LoadFromFile (const std::string &Filename)
{
    bool b;
    b = sf::Image::LoadFromFile(Filename);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, GetWidth(), GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, GetPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    return b;
}

Image::operator GLuint()
{
    return texture;
}

Window::Window():sf::Window()
{
    L = lua_open();
    luaL_openlibs(L);

    logstream= new ofstream(log_file.c_str());

    WSettings = sf::WindowSettings();
    VM = sf::VideoMode::GetMode(0);
    title="Vulture";

    load_video_settings(VM,WSettings);
    init_window_n_gl();

    *logstream<<"Window init done"<<endl;

    Load_Images();

    ShowMouseCursor(false);
}


Window::~Window()
{
    save_video_settings();
    lua_close(L);
    delete logstream;
};

void Window::Reset(int VMn)
{
    VM = sf::VideoMode::GetMode(VMn);
    init_window_n_gl();
}

void Window::init_window_n_gl()
{
    sf::Window::Create(VM,title,sf::Style::Fullscreen,WSettings);
    ratio=GetWidth()*1.0/GetHeight();

    glViewport(0, 0, GetWidth(), GetHeight());
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-ratio, ratio, -1., 1, 0, 1);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//GL_SRC_ALPHA,GL_ONE
    glEnable(GL_BLEND);
    glDisable(GL_COLOR_MATERIAL);
    glClearColor(0.0,0.0,0.00,1.0);
    glEnable( GL_TEXTURE_2D );

    glewInit();

    if (!glewIsSupported("GL_VERSION_2_0"))
        cerr<<"WHAT!!! no shaders!?"<<endl;
    else
    {
       char *vs,*fs;

        vertex_shader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
        fragment_shader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);


        vs = textFileRead("resources/shaders/shader.vert");
        fs = textFileRead("resources/shaders/shader.frag");

        const char * ff = fs;
        const char * vv = vs;

        glShaderSourceARB(vertex_shader, 1, &vv,NULL);
        glShaderSourceARB(fragment_shader, 1, &ff,NULL);

        free(vs);free(fs);

        glCompileShaderARB(vertex_shader);
        glCompileShaderARB(fragment_shader);

        int infoLogLength = 0;
        glGetObjectParameterivARB(vertex_shader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &infoLogLength);

        char *buffer = new char[infoLogLength];
        glGetInfoLogARB(vertex_shader, infoLogLength, 0, buffer);
        cerr<<buffer;
        delete[] buffer;
        buffer=NULL;

        glGetObjectParameterivARB(fragment_shader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &infoLogLength);

        buffer = new char[infoLogLength];
        glGetInfoLogARB(fragment_shader, infoLogLength, 0, buffer);
        cerr<<buffer;
        delete[] buffer;



        backs_prog = glCreateProgramObjectARB();
        glAttachObjectARB(backs_prog,vertex_shader);
        glAttachObjectARB(backs_prog,fragment_shader);


        glLinkProgramARB(backs_prog);

    }


    ///framebuffer
    // create a texture object
    glGenTextures(1, &fboTextureId);
    glBindTexture(GL_TEXTURE_2D, fboTextureId);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, GetWidth(), GetHeight(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // create a renderbuffer object to store depth info


    // create a framebuffer object
    glGenFramebuffersEXT(1, &fboId);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);

    // attach the texture to FBO color attachment point
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
                              GL_TEXTURE_2D, fboTextureId, 0);


    // check FBO status
    GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
    {
        cerr<<"no framebuffer!";
    }


    // switch back to window-system-provided framebuffer
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    ///

}

void Window::Display()
{
    glMatrixMode (GL_MODELVIEW);
    glBindTexture( GL_TEXTURE_2D, GetTex("mouse") );
    glColor4f(1.0,1.0,1.0,1.0);
    glLoadIdentity();

    double x=GetInput().GetMouseX()*1.0/GetHeight()*2.-ratio;
    double y=-(GetInput().GetMouseY()*1.0/GetHeight()*2.-1.);

    double xm=GetInput().IsMouseButtonDown(sf::Mouse::Left)?0.5:0.0;
    double ym =GetInput().IsMouseButtonDown(sf::Mouse::Right)?0.5:0.0;

    glTranslated( x, y, 0 );

    glBegin( GL_QUADS );
        glTexCoord2f( 0.+xm,0.+ym);glVertex2d( -0.005, 0.005 );
        glTexCoord2f( 0.+xm, 0.5+ym);glVertex2d( -0.005, -.075 );
        glTexCoord2f( 0.5+xm, 0.5+ym);glVertex2d( .075, -.075 );
        glTexCoord2f( 0.5+xm, 0.+ym); glVertex2d( .075, 0.005 );
    glEnd( );

    glLoadIdentity();

    sf::Window::Display();
    glClear(GL_COLOR_BUFFER_BIT);
}

Image Window::GetTex(string s)
{
    return imagelist[s];
}

unsigned int Window::GetVideoModeNum()
{
    unsigned int i;
    for(i=0;i<sf::VideoMode::GetModesCount();i++)
    {
        if(sf::VideoMode::GetMode(i)==VM)
            return i;
    }
    return 0;
}

const sf::Input& Window::GetInput() const
{
    return sf::Window::GetInput();
}

void Window::load_video_settings(sf::VideoMode &VM,sf::WindowSettings &WSettings)
{
    bool default_settings=false;

    if (luaL_dofile(L,settings_file.c_str()))
    {
        default_settings=true;
        *logstream << "Settings file ("<<settings_file<<") not found!"<<endl;
    }

    VM.Width        =Lget_double_or_default(L,"Width",VM.Width,default_settings);
    VM.Height       =Lget_double_or_default(L,"Height",VM.Height,default_settings);
    VM.BitsPerPixel =Lget_double_or_default(L,"BitsPerPixel",VM.BitsPerPixel,default_settings);

    if(!VM.IsValid())
    {
        VM = sf::VideoMode::GetMode(0);
        return;
    }

    WSettings.AntialiasingLevel =   Lget_double_or_default(L,"AntialiasingLevel",WSettings.AntialiasingLevel,default_settings);
    WSettings.DepthBits         =   Lget_double_or_default(L,"DepthBits",WSettings.DepthBits,default_settings);
    WSettings.StencilBits       =   Lget_double_or_default(L,"StencilBits",WSettings.StencilBits,default_settings);

}

void Window::save_video_settings()
{
    ofstream sfile(settings_file.c_str());
    if (sfile.is_open())
    {
        sfile << "Width"            <<" = "<<VM.Width         <<endl;
        sfile << "Height"           <<" = "<<VM.Height        <<endl;
        sfile << "BitsPerPixel"     <<" = "<<VM.BitsPerPixel  <<endl;
        sfile << "AntialiasingLevel"<<" = "<<WSettings.AntialiasingLevel                <<endl;
        sfile << "DepthBits"        <<" = "<<WSettings.DepthBits                        <<endl;
        sfile << "StencilBits"      <<" = "<<WSettings.StencilBits                      <<endl;
        sfile.close();
    }
    else *logstream << "settings file ("<<settings_file<<") cannot be created";
}

void Window::Load_Images()
{
    if (luaL_dofile(L,img_file.c_str()))
    {
        *logstream << "Image list ("<<img_file<<") not found!"<<endl;
    }

    lua_getglobal(L, "images");
    lua_pushnil(L);

    Image image;
    for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1))
    {
        if(image.LoadFromFile(lua_tolstring(L,-1,NULL)))
        {
            imagelist.insert ( pair<string,Image>(lua_tolstring(L,-2,NULL),image) );
        }
        else
            *logstream<<"Error at loading image (name: "<<lua_tolstring(L,-2,NULL)<<" path: "<<lua_tolstring(L,-1,NULL)<<" )!" <<endl;
    }

    lua_pop(L, 1);
    *logstream<<"Image loading done!"<<endl;
}





void glColorsf(sf::Color c)
{
    glColor4f(c.r/255., c.g/255., c.b/255., c.a/255.);
}

string GetVideoModeString(int i)
{
    stringstream ss;
    sf::VideoMode VM = sf::VideoMode::GetMode(i);
    ss<<VM.Width<<" X "<<VM.Height<<" X "<<VM.BitsPerPixel;
    return ss.str();

}

