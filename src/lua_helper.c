#include "lua_helper.h"

int luaH_arguments(lua_State *L, int expected_count) {
    int count = lua_gettop(L);
    if (count != expected_count) {
        luaL_error(L, "Expected %i arguments, got %i", expected_count, count);
        return LUA_ERRERR;
    }
    return LUA_OK;
}

int luaH_typerror(lua_State *L, int narg, const char *tname) {
  const char *message = lua_pushfstring(L, "%s expected, got %s", tname, luaL_typename(L, narg));
  return luaL_argerror(L, narg, message);
}
