#ifndef __LUA_HELPER_H__
#define __LUA_HELPER_H__

#include <lauxlib.h>

/**
 * Compare the number of arguments passed to a lua method to `expected_count`.
 * Read the actual count by looking at the number of items on the state stack.
 *
 * Raise a lua_error if counts do not match
 *
 * @param expected_count expected number of arguments
 */
int luaH_arguments(lua_State *L, int expected_count);

/**
 * Raise a lua_error because an argument given to a function did not match
 * its expected type
 *
 * @param narg index of the argument with the wrong type
 * @param tname expected argument type
 */
int luaH_typerror(lua_State *L, int narg, const char *tname);

#endif
