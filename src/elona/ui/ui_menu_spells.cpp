#include "ui_menu_spells.hpp"
#include "../ability.hpp"
#include "../audio.hpp"
#include "../calc.hpp"
#include "../i18n.hpp"
#include "../keybind/keybind.hpp"
#include "../menu.hpp"
#include "../message.hpp"

namespace elona
{
namespace ui
{

static void _populate_spell_list()
{
    for (int cnt = 0; cnt < 200; ++cnt)
    {
        if (spell(cnt) > 0)
        {
            list(0, listmax) = cnt + 400;
            list(1, listmax) = the_ability_db[400 + cnt]
                                   ->related_basic_attribute; // TODO coupling
            ++listmax;
        }
    }
    sort_list_by_column1();
}

bool UIMenuSpells::init()
{
    listmax = 0;
    page = 0;
    pagesize = 16;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    cs = commark(1) % 1000;
    page = commark(1) / 1000;

    snd("core.spell");
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_spell.bmp", 1);
    gsel(0);
    windowshadow = 1;

    _populate_spell_list();

    return true;
}

void UIMenuSpells::update()
{
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
    {
        page = pagemax;
    }
    else if (page > pagemax)
    {
        page = 0;
    }
}

void UIMenuSpells::_draw_window()
{
    ui_display_window(
        i18n::s.get("core.locale.ui.spell.title"),
        strhint2 + strhint3 + strhint7,
        (windoww - 720) / 2 + inf_screenx,
        winposy(438),
        720,
        438);
    display_topic(i18n::s.get("core.locale.ui.spell.name"), wx + 28, wy + 36);
    display_topic(
        i18n::s.get("core.locale.ui.spell.cost") + "(" +
            i18n::s.get("core.locale.ui.spell.stock") + ")" + " " +
            i18n::s.get("core.locale.ui.spell.lv_chance"),
        wx + 220,
        wy + 36);
    display_topic(
        i18n::s.get("core.locale.ui.spell.effect"), wx + 400, wy + 36);

    pos(wx + 46, wy - 16);
    gcopy(3, 912, 48, 48, 48);
    pos(wx + ww - 78, wy);
    gcopy(3, 960, 96, 72, 144);
    pos(wx + ww - 180, wy);
    gcopy(3, 1032, 96, 72, 96);
}

void UIMenuSpells::_draw_key(int cnt)
{
    if (cnt % 2 == 0)
    {
        boxf(wx + 70, wy + 66 + cnt * 19, 620, 18, {12, 14, 16, 16});
    }
    display_key(wx + 58, wy + 66 + cnt * 19 - 2, cnt);
}

void UIMenuSpells::_draw_keys()
{
    keyrange = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        _draw_key(cnt);
    }
}

void UIMenuSpells::_draw_spell_attribute(int cnt, int spell_id)
{
    pos(wx + 40, wy + 74 + cnt * 19);
    gmode(2);
    gcopy_c(
        1,
        (the_ability_db[spell_id]->related_basic_attribute - 10) * inf_tiles,
        672,
        inf_tiles,
        inf_tiles);
}

void UIMenuSpells::_draw_spell_name(int cnt, int spell_id)
{
    std::string spell_shortcut = "";
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        if (game_data.skill_shortcuts.at(cnt) == spell_id)
        {
            spell_shortcut =
                u8"{"s + get_bound_shortcut_key_name_by_index(cnt) + u8"}"s;
        }
    }
    cs_list(
        cs == cnt,
        i18n::s.get_m(
            "locale.ability",
            the_ability_db.get_id_from_legacy(spell_id)->get(),
            "name") +
            spell_shortcut,
        wx + 84,
        wy + 66 + cnt * 19 - 1);
}

void UIMenuSpells::_draw_spell_cost(int cnt, int spell_id)
{
    std::string spell_cost = ""s + calcspellcostmp(spell_id, cc) + u8" ("s +
        spell((spell_id - 400)) + u8")"s;
    pos(wx + 328 - strlen_u(spell_cost) * 7, wy + 66 + cnt * 19 + 2);
    mes(spell_cost);
}

void UIMenuSpells::_draw_spell_power(int cnt, int spell_id)
{
    std::string spell_power_raw = make_spell_description(spell_id);
    std::string spell_power = strmid(spell_power_raw, 0, 40);
    pos(wx + 340, wy + 66 + cnt * 19 + 2);
    mes(""s + sdata(spell_id, cc) + u8"/"s + calcspellfail(spell_id, cc) +
        u8"%"s);
    pos(wx + 420, wy + 66 + cnt * 19 + 2);
    mes(spell_power);
}

void UIMenuSpells::_draw_single_list_entry(int cnt, int spell_id)
{
    _draw_spell_attribute(cnt, spell_id);
    _draw_spell_name(cnt, spell_id);
    _draw_spell_cost(cnt, spell_id);
    _draw_spell_power(cnt, spell_id);
}

void UIMenuSpells::_draw_list_entries()
{
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        int spell_id = list(0, p);
        _draw_single_list_entry(cnt, spell_id);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

void UIMenuSpells::draw()
{
    _draw_window();
    _draw_keys();
    _draw_list_entries();
}

void UIMenuSpells::_assign_shortcut(int sc_, int spell_id)
{
    snd("core.ok1");
    if (game_data.skill_shortcuts.at(sc_) == spell_id)
    {
        game_data.skill_shortcuts.at(sc_) = 0;
        return;
    }
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        if (game_data.skill_shortcuts.at(cnt) == spell_id)
        {
            game_data.skill_shortcuts.at(cnt) = 0;
        }
    }
    game_data.skill_shortcuts.at(sc_) = spell_id;
    txt(i18n::s.get(
        "core.locale.ui.assign_shortcut",
        get_bound_shortcut_key_name_by_index(sc_)));
}

optional<UIMenuSpells::ResultType> UIMenuSpells::on_key(
    const std::string& action)
{
    commark(1) = page * 1000 + cs;

    if (auto selected = get_selected_item())
    {
        menucycle = 0;
        return UIMenuSpells::Result::finish(
            UIMenuCompositeSkillsResult(UIMenuSpellsResult{*selected}));
    }
    else if (auto sc = get_shortcut(action))
    {
        int selected_spell = list(0, pagesize * page + cs);
        _assign_shortcut(*sc, selected_spell);
        set_reupdate();
        return none;
    }
    else if (action == "next_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            ++page;
            set_reupdate();
        }
    }
    else if (action == "previous_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            --page;
            set_reupdate();
        }
    }
    else if (action == "cancel")
    {
        update_screen();
        return UIMenuSpells::Result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona
