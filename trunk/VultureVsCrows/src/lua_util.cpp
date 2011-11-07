/**
<VultureVsCrows 2d space shooter: "lua_util.cpp">
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
#include "lua_util.h"

double Lget_double_or_default(lua_State *L,string name,double dflt,bool bdflt)
{
    if(bdflt)
        return dflt;

    double num;
    lua_getglobal(L, name.c_str());
    if (!lua_isnumber(L, -1))
    {
        lua_pop(L,1);
        return dflt;
    }
    num=lua_tonumber(L,-1);
    lua_pop(L,1);

    return num;
}
bool Lget_bool_or_default(lua_State *L,string name,bool dflt,bool bdflt)
{
    if(bdflt)
        return dflt;

    bool b;
    lua_getglobal(L, name.c_str());
    if (!lua_isboolean(L, -1))
    {
        lua_pop(L,1);
        return dflt;
    }
    b=lua_toboolean(L,-1);
    lua_pop(L,1);

    return b;
}
