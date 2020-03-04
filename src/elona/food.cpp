#include "food.hpp"

#include "../util/strutil.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "buff.hpp"
#include "calc.hpp"
#include "chara_db.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "data/types/type_buff.hpp"
#include "data/types/type_item.hpp"
#include "debug.hpp"
#include "deferred_event.hpp"
#include "dmgheal.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "message.hpp"
#include "random.hpp"
#include "status_ailment.hpp"
#include "trait.hpp"
#include "variables.hpp"



namespace
{

void _food_gets_rotten(int chara_idx, Item& food)
{
    if (food.material != 35)
    {
        return;
    }
    if (food.param3 <= 0)
    {
        return; // Has already been rotten.
    }
    if (food.param3 > game_data.date.hours())
    {
        return; // The expiration date has not come yet.
    }
    if (food.own_state > 0)
    {
        return; // On the field.
    }

    // Is it corpse(s) on a dryrock?
    if (chara_idx == -1 && food.id == ItemId::corpse &&
        chip_data.for_cell(food.position.x, food.position.y).kind == 1)
    {
        if (game_data.weather != 0)
        {
            return;
        }
        txt(i18n::s.get("core.misc.corpse_is_dried_up", food));
        food.param3 = game_data.date.hours() + 2160;
        food.image = 337;
        food.id = ItemId::jerky;
        food.param1 = 0;
        food.param2 = 5;
        cell_refresh(food.position.x, food.position.y);
        return;
    }

    if (0 <= chara_idx && chara_idx < 16)
    {
        txt(i18n::s.get("core.misc.get_rotten", food));
    }

    food.param3 = -1;
    food.image = 336;

    if (chara_idx == -1)
    {
        cell_refresh(food.position.x, food.position.y);
    }

    if (chara_idx == 0 && cdata.player().god_id == core_god::kumiromi)
    {
        if (rnd(3) == 0)
        {
            txt(i18n::s.get("core.misc.extract_seed", food));
            const auto seed_num = rnd_capped(food.number()) + 1;
            food.modify_number(-food.number());
            flt(calcobjlv(cdata.player().level));
            flttypeminor = 58500;
            itemcreate_player_inv(0, seed_num);
        }
    }
}

} // namespace



namespace elona
{

int cieat = 0;
int nutrition = 0;
int fdmax = 0;
elona_vector2<int> fdlist;



void show_eating_message()
{
    if (cdata[cc].nutrition >= 12000)
    {
        txt(i18n::s.get("core.food.eating_message.bloated"),
            Message::color{ColorIndex::green});
    }
    else if (cdata[cc].nutrition >= 10000)
    {
        txt(i18n::s.get("core.food.eating_message.satisfied"),
            Message::color{ColorIndex::green});
    }
    else if (cdata[cc].nutrition >= 5000)
    {
        txt(i18n::s.get("core.food.eating_message.normal"),
            Message::color{ColorIndex::green});
    }
    else if (cdata[cc].nutrition >= 2000)
    {
        txt(i18n::s.get("core.food.eating_message.hungry"),
            Message::color{ColorIndex::green});
    }
    else if (cdata[cc].nutrition >= 1000)
    {
        txt(i18n::s.get("core.food.eating_message.very_hungry"),
            Message::color{ColorIndex::green});
    }
    else
    {
        txt(i18n::s.get("core.food.eating_message.starving"),
            Message::color{ColorIndex::green});
    }
}



void eat_rotten_food()
{
    if (cdata[cc].can_digest_rotten_food() == 1)
    {
        txt(i18n::s.get("core.food.not_affected_by_rotten", cdata[cc]));
        return;
    }
    fdmax = 0;
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 10;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 11;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 17;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 16;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 12;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 13;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 14;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 15;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    nutrition = 1000;
    status_ailment_damage(cdata[cc], StatusAilment::paralyzed, 100);
    status_ailment_damage(cdata[cc], StatusAilment::confused, 200);
}



void cure_anorexia(Character& cc)
{
    if (!cc.has_anorexia())
        return;

    cc.has_anorexia() = false;
    if (is_in_fov(cc) || cc.index < 16)
    {
        txt(i18n::s.get("core.food.anorexia.recovers_from", cc));
        snd("core.offer1");
    }
}



void chara_vomit(Character& cc)
{
    ++cc.anorexia_count;

    if (is_in_fov(cc))
    {
        snd("core.vomit");
        txt(i18n::s.get("core.food.vomits", cc));
    }

    if (cc.is_pregnant())
    {
        cc.is_pregnant() = false;
        if (is_in_fov(cc))
        {
            txt(i18n::s.get("core.food.spits_alien_children", cc));
        }
    }

    // Lose food buff.
    for (size_t i = 0; i < cc.buffs.size();)
    {
        if (cc.buffs[i].id == 0)
        {
            break;
        }
        if (the_buff_db[cc.buffs[i].id]->type == BuffType::food)
        {
            buff_delete(cc, i);
        }
        else
        {
            ++i;
        }
    }

    // Vomit.
    if (map_data.type != mdata_t::MapType::world_map)
    {
        auto p = 2;
        for (const auto& item : inv.ground())
        {
            if (item.number() > 0)
            {
                if (item.id == ItemId::vomit)
                {
                    ++p;
                }
            }
        }
        if (rnd_capped(p * p * p) == 0 || cc.index == 0)
        {
            flt();
            if (const auto item = itemcreate_extra_inv(704, cc.position, 0))
            {
                if (cc.index != 0)
                {
                    item->subname = charaid2int(cc.id);
                }
            }
        }
    }

    if (cc.has_anorexia())
    {
        chara_gain_fixed_skill_exp(cc, 10, -50);
        chara_gain_fixed_skill_exp(cc, 11, -75);
        chara_gain_fixed_skill_exp(cc, 17, -100);
    }
    else
    {
        if ((cc.index < 16 && cc.anorexia_count > 10) ||
            (cc.index >= 16 && rnd(4) == 0))
        {
            if (rnd(5) == 0)
            {
                cc.has_anorexia() = true;
                if (is_in_fov(cc))
                {
                    txt(i18n::s.get("core.food.anorexia.develops", cc));
                    snd("core.offer1");
                }
            }
        }
    }

    status_ailment_damage(cc, StatusAilment::dimmed, 100);
    modify_weight(cc, -(1 + rnd(5)));
    if (cc.nutrition <= 0)
    {
        damage_hp(cc, 9999, -3);
    }
    cc.nutrition -= 3000;
}



void eatstatus(CurseState curse_state, int eater)
{
    if (cdata[eater].state() != Character::State::alive)
        return;

    if (is_cursed(curse_state))
    {
        cdata[eater].nutrition -= 1500;
        if (is_in_fov(cdata[eater]))
        {
            txt(i18n::s.get("core.food.eat_status.bad", cdata[eater]));
        }
        chara_vomit(cdata[eater]);
    }
    else if (curse_state == CurseState::blessed)
    {
        if (is_in_fov(cdata[eater]))
        {
            txt(i18n::s.get("core.food.eat_status.good", cdata[eater]));
        }
        if (rnd(5) == 0)
        {
            buff_add(cdata[eater], "elona.luck", 100, 500 + rnd(500));
        }
        heal_insanity(cdata[eater], 2);
    }
}



void chara_anorexia(Character& cc)
{
    if (cc.has_anorexia())
    {
        chara_vomit(cc);
    }
}



void get_sick_if_cursed(CurseState curse_state, Character& drinker)
{
    if (!is_cursed(curse_state))
        return;

    if (is_in_fov(drinker))
    {
        txt(i18n::s.get("core.food.eat_status.cursed_drink", drinker));
    }
    status_ailment_damage(drinker, StatusAilment::sick, 200);
}



void get_hungry(Character& cc)
{
    if ((trait(158) && rnd(3) == 0) || debug::voldemort)
        return;

    int p = cc.nutrition / 1000;
    cc.nutrition -= 8;
    if (cc.nutrition / 1000 != p)
    {
        if (p == 1)
        {
            input_halt_input(HaltInput::alert);
            txt(i18n::s.get("core.food.hunger_status.starving"));
        }
        else if (p == 2)
        {
            input_halt_input(HaltInput::alert);
            txt(i18n::s.get("core.food.hunger_status.very_hungry"));
        }
        else if (p == 5)
        {
            input_halt_input(HaltInput::alert);
            txt(i18n::s.get("core.food.hunger_status.hungry"));
        }
        refresh_speed(cc);
    }
}



void cook(Item& cook_tool, Item& food)
{
    snd("core.cook1");
    item_separate(food.index);

    const auto item_name_prev = itemname(food.index);

    int dish_rank =
        rnd_capped(sdata(184, cc) + 6) + rnd(cook_tool.param1 / 50 + 1);
    if (dish_rank > sdata(184, cc) / 5 + 7)
    {
        dish_rank = sdata(184, cc) / 5 + 7;
    }
    dish_rank = rnd(dish_rank + 1);
    if (dish_rank > 3)
    {
        dish_rank = rnd(dish_rank);
    }
    if (sdata(184, cc) >= 5)
    {
        if (dish_rank < 3)
        {
            if (rnd(4) == 0)
            {
                dish_rank = 3;
            }
        }
    }
    if (sdata(184, cc) >= 10)
    {
        if (dish_rank < 3)
        {
            if (rnd(3) == 0)
            {
                dish_rank = 3;
            }
        }
    }
    dish_rank += cook_tool.param1 / 100;
    dish_rank = clamp(dish_rank, 1, 9);

    make_dish(food, dish_rank);
    txt(i18n::s.get("core.food.cook", item_name_prev, cook_tool, food));
    item_stack(0, food, true);
    const auto rank = food.param2;
    if (rank > 2)
    {
        chara_gain_skill_exp(cdata[cc], 184, 30 + rank * 5);
    }
    refresh_burden_state();
}



void make_dish(Item& food, int dish_rank)
{
    food.image = picfood(dish_rank, food.param1 / 1000);
    food.weight = 500;
    food.param2 = dish_rank;
    if (food.material == 35 && 0 <= food.param3)
    {
        food.param3 = game_data.date.hours() + 72;
    }
}



void apply_general_eating_effect(Character& eater, Item& food)
{
    tc = eater.index;
    DIM3(fdlist, 2, 10);
    for (int cnt = 0, cnt_end = (fdmax); cnt < cnt_end; ++cnt)
    {
        fdlist(0, cnt) = 0;
        fdlist(1, cnt) = 0;
    }
    nutrition = 2500;
    if (the_item_db[itemid2int(food.id)]->is_cargo)
    {
        nutrition += 2500;
    }
    fdmax = 0;
    i = food.param1 / 1000;
    if (i == 1)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 30;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        nutrition = 3500;
    }
    if (i == 8)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        nutrition = 2000;
    }
    if (i == 2)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        nutrition = 2000;
    }
    if (i == 3)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 30;
            ++fdmax;
        }
        nutrition = 1500;
    }
    if (i == 7)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 25;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 25;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 25;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 25;
            ++fdmax;
        }
        nutrition = 2800;
    }
    if (i == 4)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 30;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 30;
            ++fdmax;
        }
        nutrition = 1500;
    }
    if (i == 6)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        nutrition = 3000;
    }
    if (i == 5)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 60;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        nutrition = 3500;
    }
    if (the_item_db[itemid2int(food.id)]->category == ItemCategory::food)
    {
        nutrition = nutrition * (100 + food.param2 * 15) / 100;
    }
    for (int cnt = 0, cnt_end = (fdmax); cnt < cnt_end; ++cnt)
    {
        if (fdlist(1, cnt) > 0)
        {
            if (food.param2 < 3)
            {
                fdlist(1, cnt) = fdlist(1, cnt) / 2;
            }
            else
            {
                fdlist(1, cnt) = fdlist(1, cnt) * (50 + food.param2 * 20) / 100;
            }
        }
        else if (food.param2 < 3)
        {
            fdlist(1, cnt) =
                fdlist(1, cnt) * ((3 - food.param2) * 100 + 100) / 100;
        }
        else
        {
            fdlist(1, cnt) = fdlist(1, cnt) * 100 / (food.param2 * 50);
        }
    }
    if (eater.index == 0)
    {
        p = food.param1 / 1000;
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (eater.index == 0)
            {
                if (trait(41))
                {
                    if (food.id == ItemId::corpse)
                    {
                        s = chara_db_get_filter(int2charaid(food.subname));
                        if (strutil::contains(s(0), u8"/man/"))
                        {
                            txt(i18n::s.get(
                                "core.food.effect.human.delicious"));
                            break;
                        }
                    }
                }
            }
            if (food.material == 35)
            {
                if (food.param3 < 0)
                {
                    txt(i18n::s.get("core.food.effect.rotten"));
                    break;
                }
            }
            if (food.param2 == 0)
            {
                if (p == 1)
                {
                    txt(i18n::s.get("core.food.effect.raw_meat"));
                    break;
                }
                if (p == 7)
                {
                    txt(i18n::s.get("core.food.effect.powder"));
                    break;
                }
                if (p == 5)
                {
                    txt(i18n::s.get("core.food.effect.raw"));
                    break;
                }
                txt(i18n::s.get("core.food.effect.boring"));
                break;
            }
            if (food.param2 < 3)
            {
                txt(i18n::s.get("core.food.effect.quality.bad"));
                break;
            }
            if (food.param2 < 5)
            {
                txt(i18n::s.get("core.food.effect.quality.so_so"));
                break;
            }
            if (food.param2 < 7)
            {
                txt(i18n::s.get("core.food.effect.quality.good"));
                break;
            }
            if (food.param2 < 9)
            {
                txt(i18n::s.get("core.food.effect.quality.great"));
                break;
            }
            txt(i18n::s.get("core.food.effect.quality.delicious"));
        }
    }
    else if (food.material == 35)
    {
        if (food.param3 < 0)
        {
            txt(i18n::s.get("core.food.effect.raw_glum", eater));
        }
    }
    if (food.id == ItemId::curaria)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        nutrition = 2500;
        if (eater.index == 0)
        {
            txt(i18n::s.get("core.food.effect.herb.curaria"),
                Message::color{ColorIndex::green});
        }
    }
    if (food.id == ItemId::morgia)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 900;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 700;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        nutrition = 500;
        modify_potential(eater, 10, 2);
        modify_potential(eater, 11, 2);
        if (eater.index == 0)
        {
            txt(i18n::s.get("core.food.effect.herb.morgia"),
                Message::color{ColorIndex::green});
        }
    }
    if (food.id == ItemId::mareilon)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 800;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 800;
            ++fdmax;
        }
        nutrition = 500;
        modify_potential(eater, 16, 2);
        modify_potential(eater, 15, 2);
        if (eater.index == 0)
        {
            txt(i18n::s.get("core.food.effect.herb.mareilon"),
                Message::color{ColorIndex::green});
        }
    }
    if (food.id == ItemId::spenseweed)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 750;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 800;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        modify_potential(eater, 12, 2);
        modify_potential(eater, 13, 2);
        nutrition = 500;
        if (eater.index == 0)
        {
            txt(i18n::s.get("core.food.effect.herb.spenseweed"),
                Message::color{ColorIndex::green});
        }
    }
    if (food.id == ItemId::alraunia)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 850;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 700;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        nutrition = 500;
        modify_potential(eater, 17, 2);
        modify_potential(eater, 14, 2);
        if (eater.index == 0)
        {
            txt(i18n::s.get("core.food.effect.herb.alraunia"),
                Message::color{ColorIndex::green});
        }
    }
    if (food.id == ItemId::stomafillia)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        nutrition = 20000;
    }
    if (food.id == ItemId::fortune_cookie)
    {
        nutrition = 750;
    }
    if (eater.index == 0)
    {
        if (food.material == 35)
        {
            if (food.param3 < 0)
            {
                eat_rotten_food();
            }
        }
    }
    if (food.id == ItemId::corpse)
    {
        s = chara_db_get_filter(int2charaid(food.subname));
        if (eater.index == 0)
        {
            if (strutil::contains(s(0), u8"/man/"))
            {
                if (trait(41))
                {
                    txt(i18n::s.get("core.food.effect.human.like"));
                }
                else
                {
                    txt(i18n::s.get("core.food.effect.human.dislike"));
                    damage_insanity(eater, 15);
                    status_ailment_damage(eater, StatusAilment::insane, 150);
                    if (trait(41) == 0)
                    {
                        if (rnd(5) == 0)
                        {
                            trait_get_info(0, 41);
                            txt(traitrefn(0),
                                Message::color{ColorIndex::green});
                            trait(41) = 1;
                        }
                    }
                }
            }
            else if (trait(41))
            {
                txt(i18n::s.get(
                    "core.food.effect.human.would_have_rather_eaten"));
                nutrition = nutrition * 2 / 3;
            }
        }
    }
    if (food.id == ItemId::corpse ||
        ((food.id == ItemId::jerky || food.id == ItemId::egg) && rnd(3) == 0))
    {
        chara_db_invoke_eating_effect(int2charaid(food.subname));
    }
    for (int cnt = 0, cnt_end = (fdmax); cnt < cnt_end; ++cnt)
    {
        i = 100;
        if (eater.nutrition >= 5000)
        {
            p = (eater.nutrition - 5000) / 25;
            i = i * 100 / (100 + p);
        }
        if (eater.index != 0)
        {
            i = 1500;
            if (food.material == 35)
            {
                if (food.param3 < 0)
                {
                    i = 500;
                }
            }
        }
        if (i > 0)
        {
            chara_gain_skill_exp(
                eater, fdlist(0, cnt), fdlist(1, cnt) * i / 100);
        }
    }
    if (food.curse_state == CurseState::blessed)
    {
        nutrition = nutrition * 150 / 100;
    }
    if (is_cursed(food.curse_state))
    {
        nutrition = nutrition * 50 / 100;
    }
    eater.nutrition += nutrition;
    if (nutrition >= 3000)
    {
        if (rnd(10) == 0 || eater.nutrition >= 12000)
        {
            modify_weight(
                eater,
                rnd(3) + 1,
                eater.nutrition >= 20000 &&
                    rnd(30000 / std::max(1, eater.nutrition) + 2) == 0);
        }
    }
    if (eater.id == CharaId::cute_fairy)
    {
        if (nutrition >= 2000)
        {
            const auto ci_save = ci;
            flt(calcobjlv(eater.level));
            flttypeminor = 58500;
            if (const auto item = itemcreate_extra_inv(0, eater.position, 0))
            {
                txt(i18n::s.get("core.food.effect.bomb_fish", eater, *item),
                    Message::color{ColorIndex::cyan});
            }
            ci = ci_save;
        }
    }
    if (food.id == ItemId::corpse)
    {
        if (food.subname == 319)
        {
            txt(i18n::s.get("core.food.effect.little_sister", eater),
                Message::color{ColorIndex::green});
            if (rnd_capped(
                    sdata.get(2, eater.index).original_level *
                        sdata.get(2, eater.index).original_level +
                    1) < 2000)
            {
                chara_gain_fixed_skill_exp(eater, 2, 1000);
            }
            if (rnd_capped(
                    sdata.get(3, eater.index).original_level *
                        sdata.get(3, eater.index).original_level +
                    1) < 2000)
            {
                chara_gain_fixed_skill_exp(eater, 3, 1000);
            }
            for (int cnt = 100; cnt < 400; ++cnt)
            {
                if (!the_ability_db[cnt] ||
                    the_ability_db[cnt]->related_basic_attribute == 0 ||
                    sdata.get(cnt, eater.index).original_level == 0)
                {
                    continue;
                }
                modify_potential(eater, cnt, rnd(10) + 1);
            }
        }
    }
    if (food.id == ItemId::kagami_mochi)
    {
        txt(i18n::s.get("core.food.effect.hero_cheese"));
        chara_gain_fixed_skill_exp(eater, 19, 2000);
    }
    if (food.id == ItemId::rabbits_tail)
    {
        chara_gain_fixed_skill_exp(eater, 19, 1000);
    }
    if (food.id == ItemId::happy_apple)
    {
        chara_gain_fixed_skill_exp(eater, 19, 20000);
    }
    if (food.id == ItemId::hero_cheese)
    {
        chara_gain_fixed_skill_exp(eater, 2, 3000);
    }
    if (food.id == ItemId::magic_fruit)
    {
        chara_gain_fixed_skill_exp(eater, 3, 3000);
    }
    if (food.id == ItemId::fortune_cookie)
    {
        if (eater.index < 16)
        {
            txt(i18n::s.get("core.food.effect.fortune_cookie", eater));
            read_talk_file(u8"%COOKIE2");
            if (food.curse_state == CurseState::blessed ||
                (food.curse_state == CurseState::none && rnd(2)))
            {
                read_talk_file(u8"%COOKIE1");
            }
            txt(""s + buff, Message::color{ColorIndex::orange});
        }
    }
    if (food.id == ItemId::sisters_love_fueled_lunch)
    {
        txt(i18n::s.get("core.food.effect.sisters_love_fueled_lunch", eater));
        heal_insanity(eater, 30);
    }
    if (food.is_poisoned())
    {
        if (is_in_fov(eater))
        {
            txt(i18n::s.get("core.food.effect.poisoned.text", eater));
            txt(i18n::s.get("core.food.effect.poisoned.dialog"));
        }
        damage_hp(eater, rnd(250) + 250, -4);
        if (eater.state() != Character::State::alive)
        {
            if (eater.index != 0)
            {
                if (eater.relationship >= 0)
                {
                    modify_karma(cdata.player(), -1);
                }
            }
            return;
        }
    }
    if (food.is_aphrodisiac())
    {
        if (eater.index == 0)
        {
            txt(i18n::s.get("core.food.effect.spiked.self"));
        }
        else
        {
            txt(i18n::s.get("core.food.effect.spiked.other", eater),
                Message::color{ColorIndex::cyan});
            eater.emotion_icon = 317;
            chara_modify_impression(eater, 30);
            modify_karma(cdata.player(), -10);
            lovemiracle(eater.index);
        }
        status_ailment_damage(eater, StatusAilment::dimmed, 500);
        eater.emotion_icon = 317;
    }
    for (int cnt = 0; cnt < 15; ++cnt)
    {
        if (food.enchantments[cnt].id == 0)
        {
            break;
        }
        enc = food.enchantments[cnt].id;
        if (enc == 36)
        {
            p = rnd_capped(food.enchantments[cnt].power / 50 + 1) + 1;
            heal_sp(eater, p);
            continue;
        }
        if (enc == 38)
        {
            p = rnd_capped(food.enchantments[cnt].power / 25 + 1) + 1;
            heal_mp(eater, p / 5);
            continue;
        }
        if (enc == 37)
        {
            event_add(18, eater.index);
            continue;
        }
        if (enc == 40)
        {
            if (game_data.left_turns_of_timestop == 0)
            {
                txt(i18n::s.get("core.action.time_stop.begins", eater),
                    Message::color{ColorIndex::cyan});
                game_data.left_turns_of_timestop =
                    food.enchantments[cnt].power / 100 + 1 + 1;
                continue;
            }
        }
        const auto enc2 = enc / 10000;
        if (enc2 != 0)
        {
            enc = enc % 10000;
            if (enc2 == 1)
            {
                if (is_in_fov(eater))
                {
                    if (food.enchantments[cnt].power / 50 + 1 >= 0)
                    {
                        txt(i18n::s.get(
                            "core.food.effect.ability.develops",
                            eater,
                            i18n::s.get_m(
                                "ability",
                                the_ability_db.get_id_from_legacy(enc)->get(),
                                "name")));
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.food.effect.ability.deteriorates",
                            eater,
                            i18n::s.get_m(
                                "ability",
                                the_ability_db.get_id_from_legacy(enc)->get(),
                                "name")));
                    }
                }
                chara_gain_skill_exp(
                    eater,
                    enc,
                    (food.enchantments[cnt].power / 50 + 1) * 100 *
                        (1 + (eater.index != 0) * 5));
                continue;
            }
            if (enc2 == 6)
            {
                if (is_in_fov(eater))
                {
                    txt(i18n::s.get_enum_property(
                        "core.buff", "apply", enc + 10, eater));
                }

                int legacy_id = 20 + (enc - 10);
                auto buff_id = the_buff_db.get_id_from_legacy(legacy_id);
                assert(buff_id);

                buff_add(
                    eater,
                    *buff_id,
                    (food.enchantments[cnt].power / 50 + 1) * 5 *
                        (1 + (eater.index != 0) * 2),
                    2000);

                continue;
            }
        }
    }
    eatstatus(food.curse_state, eater.index);
}



std::string
foodname(int type, const std::string& ingredient_, int rank, int character_id)
{
    std::string ingredient = ingredient_;
    if (type == 1 || type == 8)
    {
        // Food created from character drops (meat and eggs)
        if (character_id == 0)
        {
            ingredient = i18n::s.get_enum_property(
                "core.food.names", "default_origin", type);
        }
        else
        {
            ingredient = chara_db_get_name(int2charaid(character_id));
        }
    }
    else if (type == 5 || type == 7)
    {
        // Food that always always has a default origin (bread and noodles)
        ingredient = i18n::s.get_enum_property(
            "core.food.names", "default_origin", type);
    }
    else if (ingredient == ""s)
    {
        // No ingredient name was provided
        ingredient = i18n::s.get_enum_property(
            "core.food.names", "default_origin", type);
    }

    if ((type < 1 || type > 8) || (rank < 1 || rank > 9))
    {
        return ingredient;
    }
    else
    {
        return i18n::s.get_enum_property(
            "core.food.names", "_" + std::to_string(rank), type, ingredient);
    }
}



void foods_get_rotten()
{
    for (int j = 0; j < ELONA_MAX_CHARACTERS + 1; ++j)
    {
        int chara = j;
        if (j == ELONA_MAX_CHARACTERS)
        {
            chara = -1; // On the ground.
        }
        else if (cdata[chara].state() == Character::State::empty)
        {
            continue;
        }

        for (auto&& item : inv.by_index(chara))
        {
            if (item.number() == 0)
            {
                continue;
            }
            _food_gets_rotten(chara, item);
        }
    }
}

} // namespace elona
