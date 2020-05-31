#pragma once

#include "../common.hpp"



namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Handle item enchantments.
 */
namespace LuaApiEnchantment
{

void add(LuaItemHandle, int, int);

void bind(sol::table&);

} // namespace LuaApiEnchantment

} // namespace lua
} // namespace elona