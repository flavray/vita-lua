#ifndef __LUA_MODULES_H__
#define __LUA_MODULES_H__

#include <lauxlib.h>

/**
 * Require all created modules
 *
 * Modules list:
 * - ctrl
 */
void luarequire_modules(lua_State *L);

#endif
