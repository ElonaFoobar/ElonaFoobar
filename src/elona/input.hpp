#pragma once
#include <string>
#include "../snail/input.hpp"
#include "enums.hpp"
#include "optional.hpp"


namespace elona
{

enum class ActionCategory;
class InputContext;

enum class PromptType
{
    normal,
    cannot_cancel,
    with_number,
};

// int show_prompt(
//     int x,
//     int y,
//     int width,
//     PromptType type = PromptType::normal,
//     int initial_number = 0);


void input_number_dialog(int x, int y, int max_number, int initial_number = 0);

bool input_text_dialog(
    int x,
    int y,
    int val2,
    bool is_cancelable = true,
    bool limit_length = true);

StickKey stick(StickKey allow_repeat_keys = StickKey::none);

std::string key_check(KeyWaitDelay = KeyWaitDelay::always);
std::string key_check_pc_turn(KeyWaitDelay = KeyWaitDelay::always);
std::string cursor_check_ex();
std::string cursor_check_ex(int& index);
std::string get_selected_item(int& p_);
optional<int> get_shortcut(const std::string& action);
int yes_or_no(int x, int y, int width);
bool is_modifier_pressed(snail::ModKey modifier);
void wait_key_released();
void wait_key_pressed(bool only_enter_or_cancel = false);


} // namespace elona
