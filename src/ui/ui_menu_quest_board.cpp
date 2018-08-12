#include "ui_menu_quest_board.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../quest.hpp"

namespace elona
{
namespace ui
{

void ui_menu_quest_board::init()
{
    quest_refresh_list();
    listmax = 0;
    page = 0;
    pagesize = 4;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    for (int cnt = 0, cnt_end = (gdata_number_of_existing_quests);
         cnt < cnt_end;
         ++cnt)
    {
        if (qdata(1, cnt) != gdata_current_map)
        {
            continue;
        }
        if (qdata(3, cnt) == 0)
        {
            continue;
        }
        if (qdata(8, cnt) != 0)
        {
            continue;
        }
        rc = qdata(0, cnt);
        if (cdata[rc].state() != character::state_t::alive)
        {
            continue;
        }
        list(0, listmax) = cnt;
        list(1, listmax) = qdata(5, cnt);
        ++listmax;
    }

    if (listmax == 0)
    {
        txt(i18n::s.get("core.locale.ui.board.no_new_notices"));
        set_init_failed();
        return;
    }

    sort_list_by_column1();
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_board.bmp", 1);
    gsel(0);
    gsel(4);
    fillbg(3, 960, 96, 128, 128);
    ww = 560;
    int h = 140;
    wh = h * 4;
    wx = (windoww - ww) / 2 + inf_screenx;
    wy = winposy(wh);
    for (int cnt = 0; cnt < 4; ++cnt)
    {
        y = wy + cnt * 120;
        window(wx + 4, y + 4, ww, h, true);
        window(wx, y, ww, h);
        pos(wx + 20, y + 8);
        gcopy(3, 960, 240, 48, 84);
    }
    render_hud();
    gsel(0);
}

void ui_menu_quest_board::update()
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

void ui_menu_quest_board::draw()
{
    s(0) = i18n::s.get("core.locale.ui.board.title");
    s(1) = strhint2 + strhint3b;
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, inf_ver);
    gmode(2);
    font(16 - en * 2);
    bmes(u8"Page "s + (page + 1) + u8"/"s + (pagemax + 1), wx + ww + 20, wy);
    keyrange = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        y = wy + cnt * 120 + 20;
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        boxf(wx + 70, y, 460, 18, {12, 14, 16, 16});
        display_key(wx + 70, y - 2, cnt);
    }
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        y = wy + cnt * 120 + 20;
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        rq = list(0, p);
        tc = qdata(0, rq);
        quest_set_data(0);
        p = pagesize * page + cnt;
        font(14 - en * 2);
        cs_list(cs == cnt, s(3), wx + 96, y - 1, 19);
        s(2) = u8"("s + nquestdate + u8")"s;
        pos(wx + 344, y + 2);
        mes(s(2));
        s(4) = cdatan(0, tc);
        cutname(s(4), 20);
        pos(wx + 392, y + 2);
        mes(s(4));
        talk_conv(buff, 70);
        p(0) = qdata(5, rq) / 5 + 1;
        p(1) = 14;
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (cdata.player().level * 2 < qdata(5, rq))
            {
                color(205, 0, 0);
                break;
            }
            if (cdata.player().level * 3 / 2 < qdata(5, rq))
            {
                color(140, 80, 0);
                break;
            }
            if (cdata.player().level < qdata(5, rq))
            {
                color(0, 0, 205);
                break;
            }
            color(0, 155, 0);
        }
        if (p < 11)
        {
            dy = 0;
            if (p > 5)
            {
                font(10 - en * 2);
                dy = -3;
            }
            for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
            {
                pos(wx + 270 + cnt % 5 * 13, y + dy + cnt / 5 * 8 + 2);
                mes(i18n::s.get("core.locale.ui.board.difficulty"));
            }
        }
        else
        {
            pos(wx + 270, y + 2);
            mes(i18n::s.get("core.locale.ui.board.difficulty_counter") + p);
        }
        color(0, 0, 0);
        font(13 - en * 2);
        pos(wx + 20, y + 20);
        mes(buff);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

optional<ui_menu_quest_board::result_type> ui_menu_quest_board::on_key(
    const std::string& key)
{
    int _p;

    ELONA_GET_SELECTED_ITEM(_p, 0);

    if (_p != -1)
    {
        txtnew();
        txt(i18n::s.get("core.locale.ui.board.do_you_meet"));
        ELONA_YES_NO_PROMPT();
        rtval = show_prompt(promptx, prompty, 160);
        if (rtval != 0)
        {
            set_reupdate();
            return none;
        }
        return ui_menu_quest_board::result::finish(_p);
    }
    else if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            set_reupdate();
        }
    }
    else if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            set_reupdate();
        }
    }
    else if (key == key_cancel)
    {
        return ui_menu_quest_board::result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
