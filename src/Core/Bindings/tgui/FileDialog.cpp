#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/Widgets/FileDialog.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassFileDialog(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::FileDialog> bindFileDialog
            = tguiNamespace.new_usertype<tgui::FileDialog>("FileDialog", sol::call_constructor,
                sol::constructors<tgui::FileDialog(), tgui::FileDialog(const char*),
                    tgui::FileDialog(const char*, bool),
                    tgui::FileDialog(const tgui::FileDialog&)>(),
                sol::base_classes, sol::bases<tgui::ChildWindow, tgui::Container, tgui::Widget>());
        bindFileDialog["operator="] = sol::overload(
            static_cast<tgui::FileDialog& (tgui::FileDialog::*)(const tgui::FileDialog&)>(
                &tgui::FileDialog::operator=),
            static_cast<tgui::FileDialog& (tgui::FileDialog::*)(tgui::FileDialog &&)>(
                &tgui::FileDialog::operator=));
        bindFileDialog["getSharedRenderer"]
            = sol::overload(static_cast<tgui::FileDialogRenderer* (tgui::FileDialog::*)()>(
                                &tgui::FileDialog::getSharedRenderer),
                static_cast<const tgui::FileDialogRenderer* (tgui::FileDialog::*)() const>(
                    &tgui::FileDialog::getSharedRenderer));
        bindFileDialog["getRenderer"]
            = sol::overload(static_cast<tgui::FileDialogRenderer* (tgui::FileDialog::*)()>(
                                &tgui::FileDialog::getRenderer),
                static_cast<const tgui::FileDialogRenderer* (tgui::FileDialog::*)() const>(
                    &tgui::FileDialog::getRenderer));
        bindFileDialog["getSelectedPaths"] = &tgui::FileDialog::getSelectedPaths;
        bindFileDialog["setPath"]
            = sol::overload(static_cast<void (tgui::FileDialog::*)(const tgui::String&)>(
                                &tgui::FileDialog::setPath),
                static_cast<void (tgui::FileDialog::*)(const tgui::Filesystem::Path&)>(
                    &tgui::FileDialog::setPath));
        bindFileDialog["getPath"] = &tgui::FileDialog::getPath;
        bindFileDialog["setFilename"] = &tgui::FileDialog::setFilename;
        bindFileDialog["getFilename"] = &tgui::FileDialog::getFilename;
        bindFileDialog["setFileTypeFilters"] = sol::overload(
            [](tgui::FileDialog* self,
                const std::vector<std::pair<tgui::String, std::vector<tgui::String>>>& filters)
                -> void { return self->setFileTypeFilters(filters); },
            [](tgui::FileDialog* self,
                const std::vector<std::pair<tgui::String, std::vector<tgui::String>>>& filters,
                std::size_t defaultFilterIndex) -> void {
                return self->setFileTypeFilters(filters, defaultFilterIndex);
            });
        bindFileDialog["getFileTypeFilters"] = &tgui::FileDialog::getFileTypeFilters;
        bindFileDialog["getFileTypeFiltersIndex"] = &tgui::FileDialog::getFileTypeFiltersIndex;
        bindFileDialog["setConfirmButtonText"] = sol::overload(
            [](tgui::FileDialog* self) -> void { return self->setConfirmButtonText(); },
            [](tgui::FileDialog* self, const tgui::String& text) -> void {
                return self->setConfirmButtonText(text);
            });
        bindFileDialog["getConfirmButtonText"] = &tgui::FileDialog::getConfirmButtonText;
        bindFileDialog["setCancelButtonText"] = sol::overload(
            [](tgui::FileDialog* self) -> void { return self->setCancelButtonText(); },
            [](tgui::FileDialog* self, const tgui::String& text) -> void {
                return self->setCancelButtonText(text);
            });
        bindFileDialog["getCancelButtonText"] = &tgui::FileDialog::getCancelButtonText;
        bindFileDialog["setFilenameLabelText"] = sol::overload(
            [](tgui::FileDialog* self) -> void { return self->setFilenameLabelText(); },
            [](tgui::FileDialog* self, const tgui::String& labelText) -> void {
                return self->setFilenameLabelText(labelText);
            });
        bindFileDialog["getFilenameLabelText"] = &tgui::FileDialog::getFilenameLabelText;
        bindFileDialog["setListViewColumnCaptions"] = sol::overload(
            [](tgui::FileDialog* self) -> void { return self->setListViewColumnCaptions(); },
            [](tgui::FileDialog* self, const tgui::String& nameColumnText) -> void {
                return self->setListViewColumnCaptions(nameColumnText);
            },
            [](tgui::FileDialog* self, const tgui::String& nameColumnText,
                const tgui::String& sizeColumnText) -> void {
                return self->setListViewColumnCaptions(nameColumnText, sizeColumnText);
            },
            [](tgui::FileDialog* self, const tgui::String& nameColumnText,
                const tgui::String& sizeColumnText,
                const tgui::String& modifiedColumnText) -> void {
                return self->setListViewColumnCaptions(
                    nameColumnText, sizeColumnText, modifiedColumnText);
            });
        bindFileDialog["getListViewColumnCaptions"] = &tgui::FileDialog::getListViewColumnCaptions;
        bindFileDialog["setFileMustExist"] = &tgui::FileDialog::setFileMustExist;
        bindFileDialog["getFileMustExist"] = &tgui::FileDialog::getFileMustExist;
        bindFileDialog["setSelectingDirectory"] = &tgui::FileDialog::setSelectingDirectory;
        bindFileDialog["getSelectingDirectory"] = &tgui::FileDialog::getSelectingDirectory;
        bindFileDialog["setMultiSelect"] = &tgui::FileDialog::setMultiSelect;
        bindFileDialog["getMultiSelect"] = &tgui::FileDialog::getMultiSelect;
        bindFileDialog["setIconLoader"] = &tgui::FileDialog::setIconLoader;
        bindFileDialog["getIconLoader"] = &tgui::FileDialog::getIconLoader;
        bindFileDialog["keyPressed"] = &tgui::FileDialog::keyPressed;
        bindFileDialog["create"]
            = sol::overload([]() -> tgui::FileDialog::Ptr { return tgui::FileDialog::create(); },
                [](tgui::String title) -> tgui::FileDialog::Ptr {
                    return tgui::FileDialog::create(title);
                },
                [](tgui::String title, tgui::String confirmButtonText) -> tgui::FileDialog::Ptr {
                    return tgui::FileDialog::create(title, confirmButtonText);
                });
        bindFileDialog["copy"] = &tgui::FileDialog::copy;
        bindFileDialog["onFileSelect"] = &tgui::FileDialog::onFileSelect;
    }
};