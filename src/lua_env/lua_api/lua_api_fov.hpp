#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace FOV
{
bool los(const Position&, const Position&);
bool los_xy(int, int, int, int);

bool you_see(LuaCharacterHandle);
bool you_see_pos(const Position&);
bool you_see_pos_xy(int, int);

void refresh();


void bind(sol::table&);
}; // namespace FOV

} // namespace lua
} // namespace elona
