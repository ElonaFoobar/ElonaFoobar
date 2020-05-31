#pragma once

#include "../common.hpp"



namespace elona::lua::api::modules
{

/**
 * @luadoc
 *
 * Functions for working with the state of the game world.
 */
namespace LuaApiWorld
{
void add_deferred_event(int, sol::optional<int>, sol::optional<int>);

int deferred_event_id();

int home_scale();

bool belongs_to_guild(const std::string&);

void join_guild(const std::string&);

std::string ranking_title(int);

void modify_ranking(int, int, int);

std::string random_title(const EnumString&);


void bind(sol::table);
} // namespace LuaApiWorld

} // namespace elona::lua::api::modules
