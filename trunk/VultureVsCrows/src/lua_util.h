/**
<VultureVsCrows 2d space shooter: "lua_util.h">
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
