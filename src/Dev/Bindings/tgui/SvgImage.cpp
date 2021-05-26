#include <Bindings/tgui/tgui.hpp>

#include <TGUI/SvgImage.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassSvgImage(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::SvgImage> bindSvgImage
            = tguiNamespace.new_usertype<tgui::SvgImage>("SvgImage",
                sol::call_constructor,
                sol::constructors<tgui::SvgImage(),
                    tgui::SvgImage(const tgui::String&)>());
        bindSvgImage["isSet"] = &tgui::SvgImage::isSet;
        bindSvgImage["getSize"] = &tgui::SvgImage::getSize;
        bindSvgImage["rasterize"] =

            [](tgui::SvgImage* self, tgui::BackendTextureBase* texture,
                tgui::Vector2u size) { self->rasterize(*texture, size); }

        ;
    }
};