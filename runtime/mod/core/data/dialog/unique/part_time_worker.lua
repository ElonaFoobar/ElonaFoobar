local Chara = require("core.Chara")
local God = require("core.God")
local Item = require("core.Item")
local Map = require("core.Map")

return {
   root = "core.talk.unique.part_time_worker",
   nodes = {
      __start = function()
         if not (Map.id() == "core.noyel" and Map.area().christmas_festival) then
            return "__END__"
         end
         if Chara.player().religion == "core.jure" then
            return "already_believe_in_jure"
         end

         return "dialog"
      end,
      already_believe_in_jure = {
         text = {
            {"already_believe_in_jure"},
         },
      },
      dialog = {
         text = {
            {"dialog"},
         },
         choices = {
            {"confirm", "choices.yes"},
            {"no", "choices.no"}
         },
         default_choice = "no"
      },
      confirm = {
         text = {
            {"yes.dialog"},
         },
         choices = {
            {"convert_to_jure", "yes.choices.yes"},
            {"no", "yes.choices.no"}
         },
         default_choice = "no"
      },
      convert_to_jure = {
         text = {
            {"yes.yes"},
         },
         on_finish = function()
            Item.create(Chara.player().position, "core.jures_body_pillow", 0)
            God.switch_religion(Chara.player(), "core.jure")
         end
      },
      no = {
         text = {
            {"no"},
         },
      },
   }
}
