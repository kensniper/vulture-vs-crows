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
