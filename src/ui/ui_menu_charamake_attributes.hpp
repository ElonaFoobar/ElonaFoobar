#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class ui_menu_charamake_attributes : public ui_menu<elona_vector1<int>>
{
public:
    ui_menu_charamake_attributes(
        elona_vector1<int> attributes,
        elona_vector1<int>& locked_attributes)
        : _attributes(attributes)
        , _locked_attributes(locked_attributes)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_charamake_attributes::result_type> on_key(
        const std::string& key);

private:
    elona_vector1<int> _attributes;
    elona_vector1<int>& _locked_attributes;

    bool _minimum = false;
};

} // namespace ui
} // namespace elona