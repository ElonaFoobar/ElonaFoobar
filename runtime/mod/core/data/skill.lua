local data = require("core.data")

data.define_prototype("skill")
data.add(
   "core.skill",
   {
      stat_life = {
         integer_id = 2,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      stat_mana = {
         integer_id = 3,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      stat_strength = {
         integer_id = 10,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      stat_constitution = {
         integer_id = 11,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      stat_dexterity = {
         integer_id = 12,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      stat_perception = {
         integer_id = 13,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      stat_learning = {
         integer_id = 14,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      stat_will = {
         integer_id = 15,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      stat_magic = {
         integer_id = 16,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      stat_charisma = {
         integer_id = 17,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      stat_speed = {
         integer_id = 18,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      stat_luck = {
         integer_id = 19,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      long_sword = {
         integer_id = 100,
         related_basic_attribute = 10,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      short_sword = {
         integer_id = 101,
         related_basic_attribute = 12,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      axe = {
         integer_id = 102,
         related_basic_attribute = 10,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      blunt = {
         integer_id = 103,
         related_basic_attribute = 11,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      polearm = {
         integer_id = 104,
         related_basic_attribute = 11,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      stave = {
         integer_id = 105,
         related_basic_attribute = 11,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      scythe = {
         integer_id = 107,
         related_basic_attribute = 10,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      bow = {
         integer_id = 108,
         related_basic_attribute = 12,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      crossbow = {
         integer_id = 109,
         related_basic_attribute = 12,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      firearm = {
         integer_id = 110,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      throwing = {
         integer_id = 111,
         related_basic_attribute = 12,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      martial_arts = {
         integer_id = 106,
         related_basic_attribute = 10,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      shield = {
         integer_id = 168,
         related_basic_attribute = 11,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      evasion = {
         integer_id = 173,
         related_basic_attribute = 12,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      dual_wield = {
         integer_id = 166,
         related_basic_attribute = 12,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      two_hand = {
         integer_id = 167,
         related_basic_attribute = 10,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      element_fire = {
         integer_id = 50,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 1,
         difficulty = 0,
      },
      element_cold = {
         integer_id = 51,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 1,
         difficulty = 0,
      },
      element_lightning = {
         integer_id = 52,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 1,
         difficulty = 0,
      },
      element_darkness = {
         integer_id = 53,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 2,
         difficulty = 0,
      },
      element_mind = {
         integer_id = 54,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 2,
         difficulty = 0,
      },
      element_nether = {
         integer_id = 56,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 4,
         difficulty = 0,
      },
      element_poison = {
         integer_id = 55,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 3,
         difficulty = 0,
      },
      element_sound = {
         integer_id = 57,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 3,
         difficulty = 0,
      },
      element_chaos = {
         integer_id = 59,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 4,
         difficulty = 0,
      },
      element_nerve = {
         integer_id = 58,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 3,
         difficulty = 0,
      },
      element_magic = {
         integer_id = 60,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 5,
         difficulty = 0,
      },
      element_cut = {
         integer_id = 61,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      element_acid = {
         integer_id = 63,
         related_basic_attribute = 0,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      weight_lifting = {
         integer_id = 153,
         related_basic_attribute = 10,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      tactics = {
         integer_id = 152,
         related_basic_attribute = 10,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      marksman = {
         integer_id = 189,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      healing = {
         integer_id = 154,
         related_basic_attribute = 11,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      mining = {
         integer_id = 163,
         related_basic_attribute = 11,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      carpentry = {
         integer_id = 176,
         related_basic_attribute = 11,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      heavy_armor = {
         integer_id = 169,
         related_basic_attribute = 11,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      medium_armor = {
         integer_id = 170,
         related_basic_attribute = 11,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      light_armor = {
         integer_id = 171,
         related_basic_attribute = 12,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      lock_picking = {
         integer_id = 158,
         related_basic_attribute = 12,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      disarm_trap = {
         integer_id = 175,
         related_basic_attribute = 12,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      tailoring = {
         integer_id = 177,
         related_basic_attribute = 12,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      jeweler = {
         integer_id = 179,
         related_basic_attribute = 12,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      pickpocket = {
         integer_id = 300,
         related_basic_attribute = 12,
         ability_type = 0,
         cost = 20,
         range = 8000,
         difficulty = 0,
      },
      stealth = {
         integer_id = 157,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      detection = {
         integer_id = 159,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      sense_quality = {
         integer_id = 162,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      eye_of_mind = {
         integer_id = 186,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      fishing = {
         integer_id = 185,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 5,
         range = 10000,
         difficulty = 0,
      },
      greater_evasion = {
         integer_id = 187,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      anatomy = {
         integer_id = 161,
         related_basic_attribute = 14,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      literacy = {
         integer_id = 150,
         related_basic_attribute = 14,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      memorization = {
         integer_id = 165,
         related_basic_attribute = 14,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      alchemy = {
         integer_id = 178,
         related_basic_attribute = 14,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      gardening = {
         integer_id = 180,
         related_basic_attribute = 14,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      gene_engineer = {
         integer_id = 151,
         related_basic_attribute = 14,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      cooking = {
         integer_id = 184,
         related_basic_attribute = 14,
         ability_type = 0,
         cost = 15,
         range = 10000,
         difficulty = 0,
      },
      meditation = {
         integer_id = 155,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      magic_device = {
         integer_id = 174,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      casting = {
         integer_id = 172,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      control_magic = {
         integer_id = 188,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      magic_capacity = {
         integer_id = 164,
         related_basic_attribute = 15,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      faith = {
         integer_id = 181,
         related_basic_attribute = 15,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      traveling = {
         integer_id = 182,
         related_basic_attribute = 15,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      riding = {
         integer_id = 301,
         related_basic_attribute = 15,
         ability_type = 0,
         cost = 20,
         range = 8000,
         difficulty = 0,
      },
      negotiation = {
         integer_id = 156,
         related_basic_attribute = 17,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      investing = {
         integer_id = 160,
         related_basic_attribute = 17,
         ability_type = 0,
         cost = 0,
         range = 0,
         difficulty = 0,
      },
      performer = {
         integer_id = 183,
         related_basic_attribute = 17,
         ability_type = 0,
         cost = 25,
         range = 10000,
         difficulty = 0,
      },
      heal_light = {
         integer_id = 400,
         related_basic_attribute = 15,
         ability_type = 4,
         cost = 6,
         range = 3000,
         difficulty = 80,
      },
      heal_critical = {
         integer_id = 401,
         related_basic_attribute = 15,
         ability_type = 4,
         cost = 15,
         range = 3000,
         difficulty = 350,
      },
      cure_of_eris = {
         integer_id = 402,
         related_basic_attribute = 15,
         ability_type = 4,
         cost = 35,
         range = 3000,
         difficulty = 800,
      },
      cure_of_jure = {
         integer_id = 403,
         related_basic_attribute = 15,
         ability_type = 4,
         cost = 80,
         range = 3000,
         difficulty = 1300,
      },
      healing_touch = {
         integer_id = 405,
         related_basic_attribute = 15,
         ability_type = 4,
         cost = 20,
         range = 8000,
         difficulty = 400,
      },
      holy_light = {
         integer_id = 406,
         related_basic_attribute = 15,
         ability_type = 0,
         cost = 15,
         range = 3000,
         difficulty = 400,
      },
      vanquish_hex = {
         integer_id = 407,
         related_basic_attribute = 15,
         ability_type = 0,
         cost = 35,
         range = 3000,
         difficulty = 850,
      },
      teleport_other = {
         integer_id = 409,
         related_basic_attribute = 16,
         ability_type = 5,
         cost = 10,
         range = 5000,
         difficulty = 200,
      },
      teleport = {
         integer_id = 408,
         related_basic_attribute = 16,
         ability_type = 5,
         cost = 10,
         range = 10000,
         difficulty = 400,
      },
      short_teleport = {
         integer_id = 410,
         related_basic_attribute = 16,
         ability_type = 5,
         cost = 8,
         range = 10000,
         difficulty = 120,
      },
      identify = {
         integer_id = 411,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 28,
         range = 10000,
         difficulty = 800,
      },
      uncurse = {
         integer_id = 412,
         related_basic_attribute = 15,
         ability_type = 0,
         cost = 35,
         range = 3000,
         difficulty = 700,
      },
      oracle = {
         integer_id = 413,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 150,
         range = 3000,
         difficulty = 1500,
      },
      magic_dart = {
         integer_id = 414,
         related_basic_attribute = 16,
         ability_type = 2,
         cost = 5,
         range = 2006,
         difficulty = 110,
      },
      nether_arrow = {
         integer_id = 415,
         related_basic_attribute = 16,
         ability_type = 2,
         cost = 8,
         range = 2006,
         difficulty = 400,
      },
      chaos_eye = {
         integer_id = 417,
         related_basic_attribute = 16,
         ability_type = 2,
         cost = 10,
         range = 2006,
         difficulty = 650,
      },
      nerve_arrow = {
         integer_id = 416,
         related_basic_attribute = 16,
         ability_type = 2,
         cost = 10,
         range = 2006,
         difficulty = 400,
      },
      dark_eye = {
         integer_id = 418,
         related_basic_attribute = 16,
         ability_type = 2,
         cost = 10,
         range = 2006,
         difficulty = 200,
      },
      crystal_spear = {
         integer_id = 459,
         related_basic_attribute = 16,
         ability_type = 2,
         cost = 24,
         range = 2006,
         difficulty = 950,
      },
      ice_bolt = {
         integer_id = 419,
         related_basic_attribute = 16,
         ability_type = 1,
         cost = 10,
         range = 9006,
         difficulty = 220,
      },
      fire_bolt = {
         integer_id = 420,
         related_basic_attribute = 16,
         ability_type = 1,
         cost = 10,
         range = 9006,
         difficulty = 220,
      },
      lightning_bolt = {
         integer_id = 421,
         related_basic_attribute = 16,
         ability_type = 1,
         cost = 10,
         range = 9006,
         difficulty = 220,
      },
      darkness_bolt = {
         integer_id = 422,
         related_basic_attribute = 16,
         ability_type = 1,
         cost = 12,
         range = 9006,
         difficulty = 350,
      },
      mind_bolt = {
         integer_id = 423,
         related_basic_attribute = 16,
         ability_type = 1,
         cost = 12,
         range = 9006,
         difficulty = 350,
      },
      suicide_attack = {
         integer_id = 644,
         related_basic_attribute = 11,
         ability_type = 3,
         cost = 16,
         range = 8000,
         difficulty = 450,
      },
      ice_ball = {
         integer_id = 431,
         related_basic_attribute = 16,
         ability_type = 3,
         cost = 16,
         range = 3002,
         difficulty = 450,
      },
      fire_ball = {
         integer_id = 432,
         related_basic_attribute = 16,
         ability_type = 3,
         cost = 16,
         range = 3002,
         difficulty = 450,
      },
      chaos_ball = {
         integer_id = 433,
         related_basic_attribute = 16,
         ability_type = 3,
         cost = 20,
         range = 3002,
         difficulty = 1000,
      },
      raging_roar = {
         integer_id = 434,
         related_basic_attribute = 16,
         ability_type = 3,
         cost = 18,
         range = 3002,
         difficulty = 700,
      },
      magic_storm = {
         integer_id = 460,
         related_basic_attribute = 16,
         ability_type = 3,
         cost = 40,
         range = 3002,
         difficulty = 1400,
      },
      healing_rain = {
         integer_id = 404,
         related_basic_attribute = 15,
         ability_type = 3,
         cost = 38,
         range = 3002,
         difficulty = 500,
      },
      rain_of_sanity = {
         integer_id = 637,
         related_basic_attribute = 15,
         ability_type = 3,
         cost = 50,
         range = 3002,
         difficulty = 500,
      },
      gravity = {
         integer_id = 466,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 24,
         range = 3002,
         difficulty = 750,
      },
      summon_monsters = {
         integer_id = 424,
         related_basic_attribute = 16,
         ability_type = 7,
         cost = 15,
         range = 2006,
         difficulty = 200,
      },
      summon_wild = {
         integer_id = 425,
         related_basic_attribute = 16,
         ability_type = 7,
         cost = 15,
         range = 2006,
         difficulty = 200,
      },
      summon_fire = {
         integer_id = 642,
         related_basic_attribute = 16,
         ability_type = 7,
         cost = 15,
         range = 2006,
         difficulty = 200,
      },
      summon_pawn = {
         integer_id = 641,
         related_basic_attribute = 16,
         ability_type = 7,
         cost = 15,
         range = 2006,
         difficulty = 200,
      },
      summon_cats = {
         integer_id = 639,
         related_basic_attribute = 16,
         ability_type = 7,
         cost = 15,
         range = 2006,
         difficulty = 200,
      },
      summon_yeek = {
         integer_id = 640,
         related_basic_attribute = 16,
         ability_type = 7,
         cost = 15,
         range = 2006,
         difficulty = 200,
      },
      summon_sister = {
         integer_id = 643,
         related_basic_attribute = 16,
         ability_type = 7,
         cost = 15,
         range = 2006,
         difficulty = 200,
      },
      dominate = {
         integer_id = 435,
         related_basic_attribute = 17,
         ability_type = 0,
         cost = 125,
         range = 2006,
         difficulty = 2000,
      },
      web = {
         integer_id = 436,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 10,
         range = 7000,
         difficulty = 150,
      },
      mist_of_darkness = {
         integer_id = 437,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 12,
         range = 7000,
         difficulty = 320,
      },
      wall_creation = {
         integer_id = 438,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 20,
         range = 7000,
         difficulty = 250,
      },
      door_creation = {
         integer_id = 457,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 15,
         range = 7000,
         difficulty = 200,
      },
      acid_ground = {
         integer_id = 455,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 18,
         range = 7000,
         difficulty = 480,
      },
      ether_ground = {
         integer_id = 634,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 18,
         range = 7000,
         difficulty = 480,
      },
      fire_wall = {
         integer_id = 456,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 24,
         range = 7000,
         difficulty = 640,
      },
      curse = {
         integer_id = 645,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 10,
         range = 2004,
         difficulty = 100,
      },
      ["return"] = {
         integer_id = 428,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 28,
         range = 10000,
         difficulty = 550,
      },
      four_dimensional_pocket = {
         integer_id = 463,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 60,
         range = 10000,
         difficulty = 750,
      },
      magic_map = {
         integer_id = 429,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 30,
         range = 10000,
         difficulty = 450,
      },
      wizards_harvest = {
         integer_id = 464,
         related_basic_attribute = 17,
         ability_type = 0,
         cost = 45,
         range = 10000,
         difficulty = 350,
      },
      sense_object = {
         integer_id = 430,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 22,
         range = 10000,
         difficulty = 250,
      },
      restore_body = {
         integer_id = 439,
         related_basic_attribute = 15,
         ability_type = 0,
         cost = 18,
         range = 3000,
         difficulty = 250,
      },
      restore_spirit = {
         integer_id = 440,
         related_basic_attribute = 15,
         ability_type = 0,
         cost = 18,
         range = 3000,
         difficulty = 250,
      },
      resurrection = {
         integer_id = 461,
         related_basic_attribute = 15,
         ability_type = 0,
         cost = 60,
         range = 10000,
         difficulty = 1650,
      },
      wish = {
         integer_id = 441,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 580,
         range = 10000,
         difficulty = 5250,
      },
      meteor = {
         integer_id = 465,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 220,
         range = 10000,
         difficulty = 1450,
      },
      mutation = {
         integer_id = 454,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 70,
         range = 3000,
         difficulty = 2250,
      },
      holy_shield = {
         integer_id = 442,
         related_basic_attribute = 15,
         ability_type = 1001,
         cost = 8,
         range = 3000,
         difficulty = 150,
      },
      mist_of_silence = {
         integer_id = 443,
         related_basic_attribute = 13,
         ability_type = 1002,
         cost = 24,
         range = 2006,
         difficulty = 620,
      },
      regeneration = {
         integer_id = 444,
         related_basic_attribute = 15,
         ability_type = 1003,
         cost = 16,
         range = 3000,
         difficulty = 400,
      },
      elemental_shield = {
         integer_id = 445,
         related_basic_attribute = 15,
         ability_type = 1004,
         cost = 14,
         range = 3000,
         difficulty = 350,
      },
      speed = {
         integer_id = 446,
         related_basic_attribute = 15,
         ability_type = 1005,
         cost = 28,
         range = 3000,
         difficulty = 1050,
      },
      slow = {
         integer_id = 447,
         related_basic_attribute = 16,
         ability_type = 1006,
         cost = 10,
         range = 2006,
         difficulty = 450,
      },
      hero = {
         integer_id = 448,
         related_basic_attribute = 15,
         ability_type = 1007,
         cost = 12,
         range = 3000,
         difficulty = 80,
      },
      mist_of_frailness = {
         integer_id = 449,
         related_basic_attribute = 16,
         ability_type = 1008,
         cost = 8,
         range = 2006,
         difficulty = 300,
      },
      element_scar = {
         integer_id = 450,
         related_basic_attribute = 16,
         ability_type = 1009,
         cost = 15,
         range = 2006,
         difficulty = 600,
      },
      holy_veil = {
         integer_id = 451,
         related_basic_attribute = 15,
         ability_type = 1010,
         cost = 20,
         range = 3000,
         difficulty = 900,
      },
      nightmare = {
         integer_id = 452,
         related_basic_attribute = 13,
         ability_type = 1011,
         cost = 15,
         range = 2006,
         difficulty = 500,
      },
      divine_wisdom = {
         integer_id = 453,
         related_basic_attribute = 14,
         ability_type = 1012,
         cost = 22,
         range = 10000,
         difficulty = 350,
      },
      incognito = {
         integer_id = 458,
         related_basic_attribute = 13,
         ability_type = 1015,
         cost = 38,
         range = 10000,
         difficulty = 250,
      },
      contingency = {
         integer_id = 462,
         related_basic_attribute = 15,
         ability_type = 1018,
         cost = 25,
         range = 3000,
         difficulty = 1250,
      },
      boost = {
         integer_id = 647,
         related_basic_attribute = 15,
         ability_type = 1017,
         cost = 50,
         range = 10000,
         difficulty = 500,
      },
      death_word = {
         integer_id = 646,
         related_basic_attribute = 15,
         ability_type = 1016,
         cost = 15,
         range = 2006,
         difficulty = 500,
      },
      punishment = {
         integer_id = 622,
         related_basic_attribute = 15,
         ability_type = 1013,
         cost = 15,
         range = 2006,
         difficulty = 500,
      },
      lulwys_trick = {
         integer_id = 625,
         related_basic_attribute = 12,
         ability_type = 1014,
         cost = 20,
         range = 10000,
         difficulty = 500,
      },
      harvest_mana = {
         integer_id = 621,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 10,
         range = 3000,
         difficulty = 700,
      },
      drain_blood = {
         integer_id = 601,
         related_basic_attribute = 12,
         ability_type = 6,
         cost = 7,
         range = 2000,
         difficulty = 0,
      },
      power_breath = {
         integer_id = 612,
         related_basic_attribute = 11,
         ability_type = 8,
         cost = 10,
         range = 9005,
         difficulty = 0,
      },
      fire_breath = {
         integer_id = 602,
         related_basic_attribute = 11,
         ability_type = 8,
         cost = 12,
         range = 9005,
         difficulty = 0,
      },
      cold_breath = {
         integer_id = 603,
         related_basic_attribute = 11,
         ability_type = 8,
         cost = 10,
         range = 9005,
         difficulty = 0,
      },
      lightning_breath = {
         integer_id = 604,
         related_basic_attribute = 11,
         ability_type = 8,
         cost = 10,
         range = 9005,
         difficulty = 0,
      },
      chaos_breath = {
         integer_id = 606,
         related_basic_attribute = 11,
         ability_type = 8,
         cost = 10,
         range = 9005,
         difficulty = 0,
      },
      poison_breath = {
         integer_id = 610,
         related_basic_attribute = 11,
         ability_type = 8,
         cost = 10,
         range = 9005,
         difficulty = 0,
      },
      nether_breath = {
         integer_id = 608,
         related_basic_attribute = 11,
         ability_type = 8,
         cost = 10,
         range = 9005,
         difficulty = 0,
      },
      sound_breath = {
         integer_id = 607,
         related_basic_attribute = 11,
         ability_type = 8,
         cost = 10,
         range = 9005,
         difficulty = 0,
      },
      darkness_breath = {
         integer_id = 605,
         related_basic_attribute = 11,
         ability_type = 8,
         cost = 10,
         range = 9005,
         difficulty = 0,
      },
      mind_breath = {
         integer_id = 611,
         related_basic_attribute = 11,
         ability_type = 8,
         cost = 10,
         range = 9005,
         difficulty = 0,
      },
      nerve_breath = {
         integer_id = 609,
         related_basic_attribute = 11,
         ability_type = 8,
         cost = 10,
         range = 9005,
         difficulty = 0,
      },
      shadow_step = {
         integer_id = 619,
         related_basic_attribute = 15,
         ability_type = 5,
         cost = 10,
         range = 6005,
         difficulty = 0,
      },
      dimensional_move = {
         integer_id = 627,
         related_basic_attribute = 15,
         ability_type = 5,
         cost = 15,
         range = 10000,
         difficulty = 0,
      },
      draw_shadow = {
         integer_id = 620,
         related_basic_attribute = 15,
         ability_type = 5,
         cost = 10,
         range = 6005,
         difficulty = 0,
      },
      prayer_of_jure = {
         integer_id = 623,
         related_basic_attribute = 15,
         ability_type = 4,
         cost = 30,
         range = 3000,
         difficulty = 0,
      },
      absorb_magic = {
         integer_id = 624,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 25,
         range = 10000,
         difficulty = 0,
      },
      pregnant = {
         integer_id = 654,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 15,
         range = 2001,
         difficulty = 0,
      },
      touch_of_weakness = {
         integer_id = 613,
         related_basic_attribute = 16,
         ability_type = 6,
         cost = 10,
         range = 8000,
         difficulty = 0,
      },
      touch_of_hunger = {
         integer_id = 614,
         related_basic_attribute = 16,
         ability_type = 6,
         cost = 10,
         range = 8000,
         difficulty = 0,
      },
      touch_of_poison = {
         integer_id = 615,
         related_basic_attribute = 12,
         ability_type = 6,
         cost = 10,
         range = 8000,
         difficulty = 0,
      },
      touch_of_nerve = {
         integer_id = 616,
         related_basic_attribute = 12,
         ability_type = 6,
         cost = 10,
         range = 8000,
         difficulty = 0,
      },
      touch_of_fear = {
         integer_id = 617,
         related_basic_attribute = 15,
         ability_type = 6,
         cost = 10,
         range = 8000,
         difficulty = 0,
      },
      touch_of_sleep = {
         integer_id = 618,
         related_basic_attribute = 15,
         ability_type = 6,
         cost = 10,
         range = 8000,
         difficulty = 0,
      },
      suspicious_hand = {
         integer_id = 635,
         related_basic_attribute = 12,
         ability_type = 5,
         cost = 10,
         range = 8000,
         difficulty = 0,
      },
      scavenge = {
         integer_id = 651,
         related_basic_attribute = 12,
         ability_type = 0,
         cost = 10,
         range = 8000,
         difficulty = 0,
      },
      decapitation = {
         integer_id = 658,
         related_basic_attribute = 12,
         ability_type = 0,
         cost = 10,
         range = 2001,
         difficulty = 0,
      },
      manis_disassembly = {
         integer_id = 660,
         related_basic_attribute = 15,
         ability_type = 6,
         cost = 10,
         range = 8000,
         difficulty = 0,
      },
      eye_of_mutation = {
         integer_id = 632,
         related_basic_attribute = 15,
         ability_type = 0,
         cost = 10,
         range = 2002,
         difficulty = 0,
      },
      eye_of_ether = {
         integer_id = 633,
         related_basic_attribute = 15,
         ability_type = 0,
         cost = 10,
         range = 2002,
         difficulty = 0,
      },
      eye_of_insanity = {
         integer_id = 636,
         related_basic_attribute = 17,
         ability_type = 0,
         cost = 10,
         range = 2002,
         difficulty = 0,
      },
      eye_of_dimness = {
         integer_id = 638,
         related_basic_attribute = 17,
         ability_type = 0,
         cost = 10,
         range = 2002,
         difficulty = 0,
      },
      eye_of_mana = {
         integer_id = 652,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 10,
         range = 2002,
         difficulty = 0,
      },
      insult = {
         integer_id = 648,
         related_basic_attribute = 17,
         ability_type = 0,
         cost = 10,
         range = 2004,
         difficulty = 0,
      },
      vanish = {
         integer_id = 653,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 10,
         range = 10000,
         difficulty = 0,
      },
      distant_attack = {
         integer_id = 649,
         related_basic_attribute = 10,
         ability_type = 10,
         cost = 10,
         range = 2004,
         difficulty = 0,
      },
      distant_attack_2 = {
         integer_id = 650,
         related_basic_attribute = 10,
         ability_type = 10,
         cost = 10,
         range = 2007,
         difficulty = 0,
      },
      change = {
         integer_id = 628,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 10,
         range = 2006,
         difficulty = 0,
      },
      draw_charge = {
         integer_id = 629,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 1,
         range = 10000,
         difficulty = 0,
      },
      fill_charge = {
         integer_id = 630,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 10,
         range = 10000,
         difficulty = 0,
      },
      swarm = {
         integer_id = 631,
         related_basic_attribute = 10,
         ability_type = 0,
         cost = 5,
         range = 10000,
         difficulty = 220,
      },
      cheer = {
         integer_id = 656,
         related_basic_attribute = 17,
         ability_type = 0,
         cost = 28,
         range = 3006,
         difficulty = 500,
      },
      mewmewmew = {
         integer_id = 657,
         related_basic_attribute = 19,
         ability_type = 0,
         cost = 1,
         range = 3000,
         difficulty = 500,
      },
      mirror = {
         integer_id = 626,
         related_basic_attribute = 13,
         ability_type = 0,
         cost = 30,
         range = 10000,
         difficulty = 500,
      },
      grenade = {
         integer_id = 655,
         related_basic_attribute = 16,
         ability_type = 3,
         cost = 18,
         range = 3000,
         difficulty = 700,
      },
      drop_mine = {
         integer_id = 659,
         related_basic_attribute = 16,
         ability_type = 0,
         cost = 15,
         range = 3000,
         difficulty = 0,
      },
   }
)
