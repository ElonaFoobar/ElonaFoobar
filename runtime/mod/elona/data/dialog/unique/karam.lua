local Chara = Elona.game.Chara
local GUI = Elona.game.GUI
local I18N = Elona.game.I18N
local Internal = Elona.game.Internal
local Item = Elona.game.Item
local Map = Elona.game.Map
local Rand = Elona.game.Rand

return {
   id = "karam",
   root = "elona.talk.unique.karam",
   nodes = {
      __start = function()
         local flag = Internal.get_quest_flag("main_quest")
         if flag == 90 then
            return "dialog"
         end

         return "__IGNORED__"
      end,
      dialog = {
         text = {
            function() Internal.set_quest_flag("main_quest", 100) end,
            {"dialog._0"},
            {"dialog._1"},
            {"dialog._2"},
            {"dialog._3"},
            {"dialog._4"},
            {"dialog._5"},
         },
         on_finish = function(t)
            for i=0,3 do
               Item.create(
                  Chara.player().position,
                  {
                     level = Map.data.current_dungeon_level,
                     quality = "Bad",
                     flttypemajor = Internal.filter_set_dungeon()
                  }
               )
            end
            Item.create(Chara.player().position, "elona.gold_piece", Rand.between(1000, 1200))
            Item.create(Chara.player().position, "elona.platinum_coin", 3)
            local item = Item.create(Chara.player().position, "elona.bejeweled_chest", 0)
            item.param2 = 0
            GUI.show_journal_update_message()
            GUI.txt(I18N.get("core.talk.unique.karam.dies", t.speaker))
            t.speaker:vanquish()
         end
      }
   },
}
