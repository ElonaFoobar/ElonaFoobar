local Chara = Elona.game.Chara
local Internal = Elona.game.Internal
local map = {}

function map.puppy_cave(generator)
   generator.generate_nefia()
   if generator.is_deepest_level() then
      if Internal.get_quest_flag('puppys_cave') < 2 then
         if not Chara.find('elona.poppy', 'Allies') then
            local poppy = Chara.create(-3, 0, 'elona.poppy')
            poppy:set_flag('IsNotAttackedByEnemy', true)
         end
      end
   end
end

return map
