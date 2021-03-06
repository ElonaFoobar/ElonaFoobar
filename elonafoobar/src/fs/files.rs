use crate::fs::dirs;
use crate::mods::{ModId, Version};
use crate::profile::ProfileId;
use std::path::PathBuf;

pub fn global_config() -> PathBuf {
    dirs::root().join("config.json")
}

pub fn local_config(profile_id: &ProfileId) -> PathBuf {
    dirs::profile_of(profile_id).join("config.json")
}

pub fn mod_list(profile_id: &ProfileId) -> PathBuf {
    dirs::profile_of(profile_id).join("mods.json")
}

pub fn manifest_of(mod_id: &ModId, version: &Version) -> PathBuf {
    dirs::mod_of(mod_id, version).join("mod.json")
}

pub fn bundled_font() -> PathBuf {
    dirs::font().join("GenShinGothic/GenShinGothic-Monospace-Regular.ttf")
}

pub fn entry_point() -> PathBuf {
    dirs::script().join("main.lua")
}
