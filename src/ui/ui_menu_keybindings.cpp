#include "ui_menu_keybindings.hpp"
#include "../audio.hpp"
#include "../i18n.hpp"
#include "../keybind/keybind.hpp"

namespace elona
{
namespace ui
{

bool UIMenuKeybindings::init()
{
    page = 0;
    pagesize = 15;
    listmax = 0;
    cs = 0;

    wx = (windoww - 700) / 2 + inf_screenx;
    wy = winposy(400) - 10;
    ww = 700;
    wh = 400;

    gsel(7);
    picload(filesystem::dir::graphic() / u8"ie_sheet.bmp");
    gsel(0);

    for (int i = 0; i < 100; i++)
    {
        list(0, listmax) = i % 7 == 0 ? -1 : 999;
        listn(0, listmax) = "dood";
        listmax++;
    }

    windowshadow = 1;

    return true;
}

void UIMenuKeybindings::update()
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

static void _draw_window()
{
    s(0) = "Keybindings";
    s(1) = "dood";

    display_window(wx, wy, ww, wh);
}

static void _draw_topics()
{
    display_topic("Name", wx + 28, wy + 36);
    display_topic("Primary", wx + 182, wy + 36);
    display_topic("Alternate", wx + 320, wy + 36);
    display_topic("Joystick", wx + 458, wy + 36);
}

static void _draw_keys()
{
    keyrange = 0;
    int item_count = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        int index = pagesize * page + cnt;
        if (index >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;

        int list_item = list(0, index);

        if (list_item < 0)
        {
            item_count = 1;
            continue;
        }
        ++item_count;
        if (list_item < 100)
        {
            x = 52;
            dx = 18;
        }
        else
        {
            x = 70;
            dx = 0;
        }
        if (item_count % 2 == 0)
        {
            boxf(wx + x, wy + 66 + cnt * 19, 595 + dx, 18, {12, 14, 16, 16});
        }
        if (list_item < 100)
        {
            continue;
        }
        display_key(wx + 32, wy + 66 + cnt * 19 - 2, cnt);
    }
}

static void _draw_keybind_entry(int cnt, const std::string& text)
{
    cs_list(cs == cnt, text, wx + 56 + x, wy + 66 + cnt * 19 - 1);
}

static void _draw_text_entry(int cnt, const std::string& text)
{
    font(12 + sizefix - en * 2, snail::Font::Style::bold);
    cs_list(cs == cnt, text, wx + 88, wy + 66 + cnt * 19);
    font(14 - en * 2);
}

static void
_draw_single_list_entry(int cnt, int list_item, const std::string& text)
{
    if (list_item >= 0)
    {
        _draw_keybind_entry(cnt, text);
    }
    else
    {
        _draw_text_entry(cnt, text);
    }
}

static void _draw_list_entries()
{
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        int index = pagesize * page + cnt;
        if (index >= listmax)
        {
            break;
        }

        x = 0;

        int list_item = list(0, index);
        const std::string& text = listn(0, index);

        _draw_single_list_entry(cnt, list_item, text);
    }
    cs_bk = cs;
}

void UIMenuKeybindings::draw()
{
    _draw_window();
    _draw_topics();
    _draw_keys();
    _draw_list_entries();
}

static void _prompt_for_key()
{
    size_t width = 100;
    size_t height = 100;
    int font_size = 13 + sizefix - en * 2;

    std::string line = "Please press a key.";
    strlen_u(line) * 8 + 40;
    height += font_size;

    int x = promptx - (width / 2);
    int y = prompty - (height / 2);

    snd(26);

    std::string mod_key_string = "";
    optional<snail::Key> last_key = none;
    snail::ModKey last_modifiers = snail::ModKey::none;

    while (true)
    {
        gmode(6, 80);
        window(x + 12, y + 12, width, height, true); // Shadow
        gmode(2);

        window(x + 8, y + 8, width, height, false);

        font(font_size);
        pos(x + 40, y + font_size + 36);
        mes(line);

        redraw();

        await(Config::instance().wait1);

        const auto& keys = snail::Input::instance().pressed_keys();
        auto modifiers = snail::Input::instance().modifiers();

        if (modifiers != last_modifiers)
        {
            mod_key_string = "";
            if ((modifiers & snail::ModKey::ctrl) != snail::ModKey::none)
            {
                mod_key_string += "Ctrl+";
            }
            if ((modifiers & snail::ModKey::shift) != snail::ModKey::none)
            {
                mod_key_string += "Shift+";
            }
            if ((modifiers & snail::ModKey::alt) != snail::ModKey::none)
            {
                mod_key_string += "Alt+";
            }
            if ((modifiers & snail::ModKey::gui) != snail::ModKey::none)
            {
                mod_key_string += "Gui+";
            }
        }

        last_modifiers = modifiers;

        for (const auto& key : keys)
        {
            if (!is_modifier(key))
            {
                if (!keybind_can_bind_key(key))
                {
                    std::cerr << "Cannot bind key " << static_cast<int>(key)
                              << std::endl;
                }
                else
                {
                    last_key = key;
                }
            }
            break;
        }

        if (last_key)
        {
            break;
        }
    }

    listn(0, cs) = Keybind{*last_key, modifiers}.to_string();
    std::cerr << "Get " << listn(0, cs) << std::endl;
}

optional<UIMenuKeybindings::ResultType> UIMenuKeybindings::on_key(
    const std::string& key)
{
    ELONA_GET_SELECTED_ITEM(p, cs = i);

    if (p != -1)
    {
        _prompt_for_key();
        return none;
    }
    else if (key == key_pageup)
    {
        ++page;
        snd(1);
        set_reupdate();
    }
    else if (key == key_pagedown)
    {
        --page;
        snd(1);
        set_reupdate();
    }
    if (key == key_cancel)
    {
        return UIMenuKeybindings::Result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona