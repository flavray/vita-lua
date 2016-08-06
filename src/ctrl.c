#include <lauxlib.h>
#include <psp2/ctrl.h>

#include "ctrl.h"
#include "lua_helper.h"

#define ctrl_button(name, button) \
    int ctrl_##name(lua_State *L) { \
        if (luaH_arguments(L, 1) != LUA_OK) \
            return 0; \
        SceCtrlData *pad = ctrl_get(L, 1); \
        lua_pushboolean(L, pad->buttons & button); \
        return 1; \
    }

int ctrl_new(lua_State *L) {
    lua_newuserdata(L, sizeof(SceCtrlData));
    luaL_setmetatable(L, LUA_CTRL_HANDLE);
    return 1;
}

SceCtrlData *ctrl_get(lua_State *L, int index) {
    SceCtrlData *data = (SceCtrlData*)lua_touserdata(L, index);
    if (!data)
        luaH_typerror(L, index, LUA_CTRL_HANDLE);
    return data;
}

int ctrl_read(lua_State *L) {
    if (luaH_arguments(L, 1) != LUA_OK)
        return 0;

    SceCtrlData *pad = ctrl_get(L, 1);
    sceCtrlPeekBufferPositive(0, pad, 1);

    return 0;
}

int ctrl_buttons(lua_State *L) {
    if (luaH_arguments(L, 1) != LUA_OK)
        return 0;

    SceCtrlData *pad = ctrl_get(L, 1);

    lua_pushnumber(L, pad->buttons);
    return 1;
}

ctrl_button(cross, SCE_CTRL_CROSS)
ctrl_button(circle, SCE_CTRL_CIRCLE)
ctrl_button(square, SCE_CTRL_SQUARE)
ctrl_button(triangle, SCE_CTRL_TRIANGLE)

int luaopen_ctrl(lua_State *L) {
    luaL_newlib(L, ctrl_functions);

    luaL_newmetatable(L, LUA_CTRL_HANDLE);
    luaL_newlib(L, ctrl_methods);
    lua_setfield(L, -2, "__index");
    lua_pop(L, 1);

    return 1;
}

void luarequire_ctrl(lua_State *L) {
    luaL_requiref(L, LUA_CTRL_HANDLE, &luaopen_ctrl, 1);
    lua_pop(L, 1); 
}
