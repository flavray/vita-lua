#ifndef __CTRL_H__
#define __CTRL_H__

#include <lua.h>

#include "lua_helper.h"

#define LUA_CTRL_HANDLE "ctrl"

int ctrl_new(lua_State *L);

int ctrl_read(lua_State *L);

int ctrl_buttons(lua_State *L);

int ctrl_cross(lua_State *L);

int ctrl_circle(lua_State *L);

int ctrl_square(lua_State *L);

int ctrl_triangle(lua_State *L);

void luarequire_ctrl(lua_State *L);

static const luaL_Reg ctrl_functions[] = {
    { "new", &ctrl_new },
    { NULL, NULL }
};

static const luaL_Reg ctrl_methods[] = {
    { "read", &ctrl_read },
    { "buttons", &ctrl_buttons },
    { "cross", &ctrl_cross },
    { "circle", &ctrl_circle },
    { "square", &ctrl_square },
    { "triangle", &ctrl_triangle },
    { NULL, NULL }
};

#endif
