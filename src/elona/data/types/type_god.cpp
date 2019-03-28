#include "type_god.hpp"



namespace elona
{

GodDB the_god_db;
const constexpr char* data::LuaLazyCacheTraits<GodDB>::type_id;


static std::unordered_map<int, GodSkillBonus> _convert_skills(
    const lua::ConfigTable& data,
    const std::string& id)
{
    std::unordered_map<int, GodSkillBonus> skills;

    if (auto it = data.optional<sol::table>(id))
    {
        for (const auto& kvp : *it)
        {
            int k = kvp.first.as<int>();
            lua::ConfigTable v = kvp.second.as<sol::table>();


            int factor = v.required<int>("factor");
            int max = v.required<int>("max");

            skills.emplace(k, GodSkillBonus{factor, max});
        }
    }

    return skills;
}

static std::unordered_set<SharedId> _convert_offerings(
    const lua::ConfigTable& data,
    const std::string& id)
{
    std::unordered_set<SharedId> offerings;

    if (auto it = data.optional<sol::table>(id))
    {
        for (const auto& kvp : *it)
        {
            std::string v = kvp.second.as<std::string>();
            offerings.emplace(SharedId(v));
        }
    }

    return offerings;
}

GodData GodDB::convert(const lua::ConfigTable& data, const std::string& id)
{
    auto legacy_id = data.required<int>("legacy_id");
    DATA_OPT(wish_name, std::string);
    DATA_OPT(summon_id, std::string);
    DATA_REQ(servant, std::string);
    DATA_REQ(items, sol::table);
    DATA_REQ(artifact, std::string);

    auto skills = _convert_skills(data, "skills");
    auto offerings = _convert_offerings(data, "offerings");

    optional<SharedId> summon_id_ = none;
    if (summon_id)
    {
        summon_id_ = SharedId(*summon_id);
    }

    return GodData{SharedId{id},
                   legacy_id,
                   wish_name,
                   summon_id_,
                   items,
                   SharedId(servant),
                   skills,
                   SharedId(artifact),
                   offerings};
}

} // namespace elona
