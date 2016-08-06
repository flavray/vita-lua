#include "lua_modules.h"

#include "ctrl.h"

void luarequire_modules(lua_State *L) {
    luarequire_ctrl(L);
}
