#ifndef LUA_UTIL
#define LUA_UTIL

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include <iostream>
using namespace std;

template <class T>
bool Lget_num(lua_State *L,string name,T& num)
{
    lua_getglobal(L, name.c_str());
    if (!lua_isnumber(L, -1))
    {
        lua_pop(L,1);
        return false;
    }
    num=(T)lua_tonumber(L,-1);
    lua_pop(L,1);
    return true;
}


double  Lget_double_or_default(lua_State *L,string name,double dflt,bool bdflt=false);
bool    Lget_bool_or_default(lua_State *L,string name,bool dflt,bool bdflt=false);
#endif
