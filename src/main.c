#include <stdbool.h>
#include <stdio.h>

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <psp2/kernel/processmgr.h>

#include "lua_modules.h"

#define LUA_MAIN_SCRIPT "main.lua"

int pmain(lua_State *L);

int main(int argc, char *argv[]) {
    int status;

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, &pmain);
    status = lua_pcall(L, 0, 0, 0);

    if (status != LUA_OK)
        printf("An error occured.\n");

    lua_close(L);

    sceKernelExitProcess(0);
    return 0;
}

/**
 * Protected main (https://www.lua.org/pil/24.3.1.html)
 */
int pmain(lua_State *L) {
    int status;

    luaL_checkversion(L);

    // Load & Require our crafted modules
    luarequire_modules(L);

    while (true) {
        status = luaL_loadfile(L, LUA_MAIN_SCRIPT);
        if (status == LUA_OK)
            status = lua_pcall(L, 0, LUA_MULTRET, 0);

        // Retry only if an error occured
        if (status == LUA_OK)
            break;

        printf("Error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    return 0;
}
