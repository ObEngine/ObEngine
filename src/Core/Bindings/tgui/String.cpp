#include <Bindings/tgui/tgui.hpp>

#include <../../tgui/include/TGUI/String.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassString(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::String> bindString = tguiNamespace.new_usertype<tgui::String>("String",
            sol::call_constructor,
            sol::constructors<tgui::String(), tgui::String(const std::string&),
                tgui::String(const std::wstring&), tgui::String(const std::u16string&),
                tgui::String(const std::u32string&), tgui::String(char), tgui::String(wchar_t),
                tgui::String(char16_t), tgui::String(char32_t), tgui::String(const char*),
                tgui::String(const wchar_t*), tgui::String(const char16_t*),
                tgui::String(const char32_t*), tgui::String(std::size_t, char),
                tgui::String(std::size_t, wchar_t), tgui::String(std::size_t, char16_t),
                tgui::String(std::size_t, char32_t), tgui::String(const std::string&, std::size_t),
                tgui::String(const std::wstring&, std::size_t),
                tgui::String(const std::u16string&, std::size_t),
                tgui::String(const std::u32string&, std::size_t),
                tgui::String(const std::string&, std::size_t, std::size_t),
                tgui::String(const std::wstring&, std::size_t, std::size_t),
                tgui::String(const std::u16string&, std::size_t, std::size_t),
                tgui::String(const std::u32string&, std::size_t, std::size_t),
                tgui::String(const char*, std::size_t), tgui::String(const wchar_t*, std::size_t),
                tgui::String(const char16_t*, std::size_t),
                tgui::String(const char32_t*, std::size_t),
                tgui::String(std::initializer_list<char>),
                tgui::String(std::initializer_list<wchar_t>),
                tgui::String(std::initializer_list<char16_t>),
                tgui::String(std::initializer_list<char32_t>),
                tgui::String(std::string::const_iterator, std::string::const_iterator),
                tgui::String(std::wstring::const_iterator, std::wstring::const_iterator),
                tgui::String(std::u16string::const_iterator, std::u16string::const_iterator),
                tgui::String(std::u32string::const_iterator, std::u32string::const_iterator)>());
        bindString["attemptToInt"] = &tgui::String::attemptToInt;
        bindString["attemptToUInt"] = &tgui::String::attemptToUInt;
        bindString["attemptToFloat"] = &tgui::String::attemptToFloat;
        bindString["toInt"] = sol::overload([](tgui::String* self) -> int { return self->toInt(); },
            [](tgui::String* self, int defaultValue) -> int { return self->toInt(defaultValue); });
        bindString["toUInt"]
            = sol::overload([](tgui::String* self) -> unsigned int { return self->toUInt(); },
                [](tgui::String* self, unsigned int defaultValue) -> unsigned int {
                    return self->toUInt(defaultValue);
                });
        bindString["toFloat"]
            = sol::overload([](tgui::String* self) -> float { return self->toFloat(); },
                [](tgui::String* self, float defaultValue) -> float {
                    return self->toFloat(defaultValue);
                });
        bindString["trim"] = &tgui::String::trim;
        bindString["toLower"] = &tgui::String::toLower;
        bindString["toUpper"] = &tgui::String::toUpper;
        bindString["equalIgnoreCase"] = &tgui::String::equalIgnoreCase;
        bindString["startsWith"] = &tgui::String::startsWith;
        bindString["endsWith"] = &tgui::String::endsWith;
        bindString["replace"] = sol::overload(
            static_cast<tgui::String& (tgui::String::*)(const tgui::String&, const tgui::String&)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const std::string&)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const std::wstring&)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const std::u16string&)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const std::u32string&)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const tgui::String&)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const std::string&)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const std::wstring&)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const std::u16string&)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const std::u32string&)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const tgui::String&)>(&tgui::String::replace),
            [](tgui::String* self, std::size_t pos, std::size_t count, const std::string& str,
                std::size_t pos2) -> tgui::String& { return self->replace(pos, count, str, pos2); },
            [](tgui::String* self, std::size_t pos, std::size_t count, const std::string& str,
                std::size_t pos2, std::size_t count2) -> tgui::String& {
                return self->replace(pos, count, str, pos2, count2);
            },
            [](tgui::String* self, std::size_t pos, std::size_t count, const std::wstring& str,
                std::size_t pos2) -> tgui::String& { return self->replace(pos, count, str, pos2); },
            [](tgui::String* self, std::size_t pos, std::size_t count, const std::wstring& str,
                std::size_t pos2, std::size_t count2) -> tgui::String& {
                return self->replace(pos, count, str, pos2, count2);
            },
            [](tgui::String* self, std::size_t pos, std::size_t count, const std::u16string& str,
                std::size_t pos2) -> tgui::String& { return self->replace(pos, count, str, pos2); },
            [](tgui::String* self, std::size_t pos, std::size_t count, const std::u16string& str,
                std::size_t pos2, std::size_t count2) -> tgui::String& {
                return self->replace(pos, count, str, pos2, count2);
            },
            [](tgui::String* self, std::size_t pos, std::size_t count, const std::u32string& str,
                std::size_t pos2) -> tgui::String& { return self->replace(pos, count, str, pos2); },
            [](tgui::String* self, std::size_t pos, std::size_t count, const std::u32string& str,
                std::size_t pos2, std::size_t count2) -> tgui::String& {
                return self->replace(pos, count, str, pos2, count2);
            },
            [](tgui::String* self, std::size_t pos, std::size_t count, const tgui::String& str,
                std::size_t pos2) -> tgui::String& { return self->replace(pos, count, str, pos2); },
            [](tgui::String* self, std::size_t pos, std::size_t count, const tgui::String& str,
                std::size_t pos2, std::size_t count2) -> tgui::String& {
                return self->replace(pos, count, str, pos2, count2);
            },
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, std::string::const_iterator,
                std::string::const_iterator)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, std::wstring::const_iterator,
                std::wstring::const_iterator)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, std::u16string::const_iterator,
                std::u16string::const_iterator)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, std::u32string::const_iterator,
                std::u32string::const_iterator)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t, const char*,
                std::size_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t, const wchar_t*,
                std::size_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t, const char16_t*,
                std::size_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t, const char32_t*,
                std::size_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const char*, std::size_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const wchar_t*, std::size_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const char16_t*, std::size_t)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const char32_t*, std::size_t)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t, const char*)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t, const wchar_t*)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t, const char16_t*)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t, const char32_t*)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const char*)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const wchar_t*)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const char16_t*)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const char32_t*)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t, std::size_t,
                char)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t, std::size_t,
                wchar_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t, std::size_t,
                char16_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t, std::size_t,
                char32_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, std::size_t, char)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, std::size_t, wchar_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, std::size_t, char16_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, std::size_t, char32_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, std::initializer_list<char>)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, std::initializer_list<wchar_t>)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, std::initializer_list<char16_t>)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, std::initializer_list<char32_t>)>(
                &tgui::String::replace));
        bindString["split"] = &tgui::String::split;
        bindString["toAnsiString"] = &tgui::String::toAnsiString;
        bindString["toStdString"] = &tgui::String::toStdString;
        bindString["toWideString"] = &tgui::String::toWideString;
        bindString["toUtf16"] = &tgui::String::toUtf16;
        bindString["toUtf32"] = &tgui::String::toUtf32;
        bindString["toUtf8"] = &tgui::String::toUtf8;
        bindString["assign"] = sol::overload(
            static_cast<tgui::String& (tgui::String::*)(std::size_t, char)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, wchar_t)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, char16_t)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, char32_t)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const std::string&)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const std::wstring&)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const std::u16string&)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const std::u32string&)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const tgui::String&)>(
                &tgui::String::assign),
            [](tgui::String* self, const std::string& str, std::size_t pos) -> tgui::String& {
                return self->assign(str, pos);
            },
            [](tgui::String* self, const std::string& str, std::size_t pos,
                std::size_t count) -> tgui::String& { return self->assign(str, pos, count); },
            [](tgui::String* self, const std::wstring& str, std::size_t pos) -> tgui::String& {
                return self->assign(str, pos);
            },
            [](tgui::String* self, const std::wstring& str, std::size_t pos,
                std::size_t count) -> tgui::String& { return self->assign(str, pos, count); },
            [](tgui::String* self, const std::u16string& str, std::size_t pos) -> tgui::String& {
                return self->assign(str, pos);
            },
            [](tgui::String* self, const std::u16string& str, std::size_t pos,
                std::size_t count) -> tgui::String& { return self->assign(str, pos, count); },
            [](tgui::String* self, const std::u32string& str, std::size_t pos) -> tgui::String& {
                return self->assign(str, pos);
            },
            [](tgui::String* self, const std::u32string& str, std::size_t pos,
                std::size_t count) -> tgui::String& { return self->assign(str, pos, count); },
            [](tgui::String* self, const tgui::String& str, std::size_t pos) -> tgui::String& {
                return self->assign(str, pos);
            },
            [](tgui::String* self, const tgui::String& str, std::size_t pos,
                std::size_t count) -> tgui::String& { return self->assign(str, pos, count); },
            static_cast<tgui::String& (tgui::String::*)(std::string &&)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(std::wstring &&)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(std::u16string &&)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(std::u32string &&)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(tgui::String &&)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const char*, std::size_t)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const wchar_t*, std::size_t)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const char16_t*, std::size_t)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const char32_t*, std::size_t)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const char*)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const wchar_t*)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const char16_t*)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const char32_t*)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(std::initializer_list<char>)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(std::initializer_list<wchar_t>)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(std::initializer_list<char16_t>)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(std::initializer_list<char32_t>)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(std::string::const_iterator,
                std::string::const_iterator)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(std::wstring::const_iterator,
                std::wstring::const_iterator)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(std::u16string::const_iterator,
                std::u16string::const_iterator)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(std::u32string::const_iterator,
                std::u32string::const_iterator)>(&tgui::String::assign));
        bindString["at"] = sol::overload(
            static_cast<tgui::String::reference (tgui::String::*)(std::size_t)>(&tgui::String::at),
            static_cast<tgui::String::const_reference (tgui::String::*)(std::size_t) const>(
                &tgui::String::at));
        bindString[sol::meta_function::index] = sol::overload(
            static_cast<tgui::String::const_reference (tgui::String::*)(std::size_t) const>(
                &tgui::String::operator[]),
            static_cast<tgui::String::reference (tgui::String::*)(std::size_t)>(
                &tgui::String::operator[]));
        bindString["front"] = sol::overload(
            static_cast<tgui::String::reference (tgui::String::*)()>(&tgui::String::front),
            static_cast<tgui::String::const_reference (tgui::String::*)() const>(
                &tgui::String::front));
        bindString["back"] = sol::overload(
            static_cast<tgui::String::reference (tgui::String::*)()>(&tgui::String::back),
            static_cast<tgui::String::const_reference (tgui::String::*)() const>(
                &tgui::String::back));
        bindString["data"] = &tgui::String::data;
        bindString["c_str"] = &tgui::String::c_str;
        bindString["begin"] = sol::overload(
            static_cast<tgui::String::iterator (tgui::String::*)()>(&tgui::String::begin),
            static_cast<tgui::String::const_iterator (tgui::String::*)() const>(
                &tgui::String::begin));
        bindString["cbegin"] = &tgui::String::cbegin;
        bindString["end"] = sol::overload(
            static_cast<tgui::String::iterator (tgui::String::*)()>(&tgui::String::end),
            static_cast<tgui::String::const_iterator (tgui::String::*)() const>(
                &tgui::String::end));
        bindString["cend"] = &tgui::String::cend;
        bindString["rbegin"] = sol::overload(
            static_cast<tgui::String::reverse_iterator (tgui::String::*)()>(&tgui::String::rbegin),
            static_cast<tgui::String::const_reverse_iterator (tgui::String::*)() const>(
                &tgui::String::rbegin));
        bindString["crbegin"] = &tgui::String::crbegin;
        bindString["rend"] = sol::overload(
            static_cast<tgui::String::reverse_iterator (tgui::String::*)()>(&tgui::String::rend),
            static_cast<tgui::String::const_reverse_iterator (tgui::String::*)() const>(
                &tgui::String::rend));
        bindString["crend"] = &tgui::String::crend;
        bindString["empty"] = &tgui::String::empty;
        bindString["size"] = &tgui::String::size;
        bindString["length"] = &tgui::String::length;
        bindString["max_size"] = &tgui::String::max_size;
        bindString["reserve"] = &tgui::String::reserve;
        bindString["capacity"] = &tgui::String::capacity;
        bindString["shrink_to_fit"] = &tgui::String::shrink_to_fit;
        bindString["clear"] = &tgui::String::clear;
        bindString["insert"] = sol::overload(
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t, char)>(
                &tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t, wchar_t)>(
                &tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t, char16_t)>(
                &tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t, char32_t)>(
                &tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const std::string&)>(
                &tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const std::wstring&)>(
                &tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const std::u16string&)>(
                &tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const std::u32string&)>(
                &tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const tgui::String&)>(
                &tgui::String::insert),
            [](tgui::String* self, std::size_t index, const std::string& str,
                std::size_t pos) -> tgui::String& { return self->insert(index, str, pos); },
            [](tgui::String* self, std::size_t index, const std::string& str, std::size_t pos,
                std::size_t count) -> tgui::String& {
                return self->insert(index, str, pos, count);
            },
            [](tgui::String* self, std::size_t index, const std::wstring& str,
                std::size_t pos) -> tgui::String& { return self->insert(index, str, pos); },
            [](tgui::String* self, std::size_t index, const std::wstring& str, std::size_t pos,
                std::size_t count) -> tgui::String& {
                return self->insert(index, str, pos, count);
            },
            [](tgui::String* self, std::size_t index, const std::u16string& str,
                std::size_t pos) -> tgui::String& { return self->insert(index, str, pos); },
            [](tgui::String* self, std::size_t index, const std::u16string& str, std::size_t pos,
                std::size_t count) -> tgui::String& {
                return self->insert(index, str, pos, count);
            },
            [](tgui::String* self, std::size_t index, const std::u32string& str,
                std::size_t pos) -> tgui::String& { return self->insert(index, str, pos); },
            [](tgui::String* self, std::size_t index, const std::u32string& str, std::size_t pos,
                std::size_t count) -> tgui::String& {
                return self->insert(index, str, pos, count);
            },
            [](tgui::String* self, std::size_t index, const tgui::String& str,
                std::size_t pos) -> tgui::String& { return self->insert(index, str, pos); },
            [](tgui::String* self, std::size_t index, const tgui::String& str, std::size_t pos,
                std::size_t count) -> tgui::String& {
                return self->insert(index, str, pos, count);
            },
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const char*, std::size_t)>(
                &tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const wchar_t*, std::size_t)>(
                &tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const char16_t*, std::size_t)>(
                &tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const char32_t*, std::size_t)>(
                &tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const char*)>(
                &tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const wchar_t*)>(
                &tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const char16_t*)>(
                &tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const char32_t*)>(
                &tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, char)>(&tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, wchar_t)>(&tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, char16_t)>(&tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, char32_t)>(&tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, std::size_t, char)>(&tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, std::size_t, wchar_t)>(&tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, std::size_t, char16_t)>(&tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, std::size_t, char32_t)>(&tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, std::initializer_list<char>)>(&tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(tgui::String::const_iterator,
                std::initializer_list<wchar_t>)>(&tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(tgui::String::const_iterator,
                std::initializer_list<char16_t>)>(&tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(tgui::String::const_iterator,
                std::initializer_list<char32_t>)>(&tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(tgui::String::const_iterator,
                std::string::const_iterator, std::string::const_iterator)>(&tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(tgui::String::const_iterator,
                std::wstring::const_iterator, std::wstring::const_iterator)>(&tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(tgui::String::const_iterator,
                std::u16string::const_iterator, std::u16string::const_iterator)>(
                &tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(tgui::String::const_iterator,
                std::u32string::const_iterator, std::u32string::const_iterator)>(
                &tgui::String::insert));
        bindString["erase"]
            = sol::overload([](tgui::String* self) -> tgui::String& { return self->erase(); },
                [](tgui::String* self, std::size_t index) -> tgui::String& {
                    return self->erase(index);
                },
                [](tgui::String* self, std::size_t index, std::size_t count) -> tgui::String& {
                    return self->erase(index, count);
                },
                static_cast<tgui::String::iterator (tgui::String::*)(tgui::String::const_iterator)>(
                    &tgui::String::erase),
                static_cast<tgui::String::iterator (tgui::String::*)(tgui::String::const_iterator,
                    tgui::String::const_iterator)>(&tgui::String::erase));
        bindString["push_back"]
            = sol::overload(static_cast<void (tgui::String::*)(char)>(&tgui::String::push_back),
                static_cast<void (tgui::String::*)(wchar_t)>(&tgui::String::push_back),
                static_cast<void (tgui::String::*)(char16_t)>(&tgui::String::push_back),
                static_cast<void (tgui::String::*)(char32_t)>(&tgui::String::push_back));
        bindString["pop_back"] = &tgui::String::pop_back;
        bindString["append"] = sol::overload(
            static_cast<tgui::String& (tgui::String::*)(std::size_t, char)>(&tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, wchar_t)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, char16_t)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, char32_t)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const std::string&)>(&tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const std::wstring&)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const std::u16string&)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const std::u32string&)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const tgui::String&)>(
                &tgui::String::append),
            [](tgui::String* self, const std::string& str, std::size_t pos) -> tgui::String& {
                return self->append(str, pos);
            },
            [](tgui::String* self, const std::string& str, std::size_t pos,
                std::size_t count) -> tgui::String& { return self->append(str, pos, count); },
            [](tgui::String* self, const std::wstring& str, std::size_t pos) -> tgui::String& {
                return self->append(str, pos);
            },
            [](tgui::String* self, const std::wstring& str, std::size_t pos,
                std::size_t count) -> tgui::String& { return self->append(str, pos, count); },
            [](tgui::String* self, const std::u16string& str, std::size_t pos) -> tgui::String& {
                return self->append(str, pos);
            },
            [](tgui::String* self, const std::u16string& str, std::size_t pos,
                std::size_t count) -> tgui::String& { return self->append(str, pos, count); },
            [](tgui::String* self, const std::u32string& str, std::size_t pos) -> tgui::String& {
                return self->append(str, pos);
            },
            [](tgui::String* self, const std::u32string& str, std::size_t pos,
                std::size_t count) -> tgui::String& { return self->append(str, pos, count); },
            [](tgui::String* self, const tgui::String& str, std::size_t pos) -> tgui::String& {
                return self->append(str, pos);
            },
            [](tgui::String* self, const tgui::String& str, std::size_t pos,
                std::size_t count) -> tgui::String& { return self->append(str, pos, count); },
            static_cast<tgui::String& (tgui::String::*)(const char*, std::size_t)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const wchar_t*, std::size_t)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const char16_t*, std::size_t)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const char32_t*, std::size_t)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const char*)>(&tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const wchar_t*)>(&tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const char16_t*)>(&tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const char32_t*)>(&tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(std::string::const_iterator,
                std::string::const_iterator)>(&tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(std::wstring::const_iterator,
                std::wstring::const_iterator)>(&tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(std::u16string::const_iterator,
                std::u16string::const_iterator)>(&tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(std::u32string::const_iterator,
                std::u32string::const_iterator)>(&tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(std::initializer_list<char>)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(std::initializer_list<wchar_t>)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(std::initializer_list<char16_t>)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(std::initializer_list<char32_t>)>(
                &tgui::String::append));
        bindString["compare"] = sol::overload(
            static_cast<int (tgui::String::*)(const std::string&) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(const std::wstring&) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(const std::u16string&) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(const std::u32string&) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(const tgui::String&) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const std::string&) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const std::wstring&) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const std::u16string&)
                    const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const std::u32string&)
                    const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const tgui::String&) const>(
                &tgui::String::compare),
            [](tgui::String* self, std::size_t pos1, std::size_t count1, const std::string& str,
                std::size_t pos2) -> int { return self->compare(pos1, count1, str, pos2); },
            [](tgui::String* self, std::size_t pos1, std::size_t count1, const std::string& str,
                std::size_t pos2, std::size_t count2) -> int {
                return self->compare(pos1, count1, str, pos2, count2);
            },
            [](tgui::String* self, std::size_t pos1, std::size_t count1, const std::wstring& str,
                std::size_t pos2) -> int { return self->compare(pos1, count1, str, pos2); },
            [](tgui::String* self, std::size_t pos1, std::size_t count1, const std::wstring& str,
                std::size_t pos2, std::size_t count2) -> int {
                return self->compare(pos1, count1, str, pos2, count2);
            },
            [](tgui::String* self, std::size_t pos1, std::size_t count1, const std::u16string& str,
                std::size_t pos2) -> int { return self->compare(pos1, count1, str, pos2); },
            [](tgui::String* self, std::size_t pos1, std::size_t count1, const std::u16string& str,
                std::size_t pos2, std::size_t count2) -> int {
                return self->compare(pos1, count1, str, pos2, count2);
            },
            [](tgui::String* self, std::size_t pos1, std::size_t count1, const std::u32string& str,
                std::size_t pos2) -> int { return self->compare(pos1, count1, str, pos2); },
            [](tgui::String* self, std::size_t pos1, std::size_t count1, const std::u32string& str,
                std::size_t pos2, std::size_t count2) -> int {
                return self->compare(pos1, count1, str, pos2, count2);
            },
            [](tgui::String* self, std::size_t pos1, std::size_t count1, const tgui::String& str,
                std::size_t pos2) -> int { return self->compare(pos1, count1, str, pos2); },
            [](tgui::String* self, std::size_t pos1, std::size_t count1, const tgui::String& str,
                std::size_t pos2, std::size_t count2) -> int {
                return self->compare(pos1, count1, str, pos2, count2);
            },
            static_cast<int (tgui::String::*)(const char*) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(const wchar_t*) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(const char16_t*) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(const char32_t*) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char*) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const wchar_t*) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char16_t*) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char32_t*) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char*, std::size_t)
                    const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const wchar_t*, std::size_t)
                    const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char16_t*,
                std::size_t) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char32_t*,
                std::size_t) const>(&tgui::String::compare));
        bindString["substr"] = sol::overload(
            [](tgui::String* self) -> tgui::String { return self->substr(); },
            [](tgui::String* self, std::size_t pos) -> tgui::String { return self->substr(pos); },
            [](tgui::String* self, std::size_t pos, std::size_t count) -> tgui::String {
                return self->substr(pos, count);
            });
        bindString["copy"] = sol::overload(
            [](tgui::String* self, char32_t* dest, std::size_t count) -> std::size_t {
                return self->copy(dest, count);
            },
            [](tgui::String* self, char32_t* dest, std::size_t count,
                std::size_t pos) -> std::size_t { return self->copy(dest, count, pos); });
        bindString["resize"]
            = sol::overload(static_cast<void (tgui::String::*)(std::size_t)>(&tgui::String::resize),
                static_cast<void (tgui::String::*)(std::size_t, char)>(&tgui::String::resize),
                static_cast<void (tgui::String::*)(std::size_t, wchar_t)>(&tgui::String::resize),
                static_cast<void (tgui::String::*)(std::size_t, char16_t)>(&tgui::String::resize),
                static_cast<void (tgui::String::*)(std::size_t, char32_t)>(&tgui::String::resize));
        bindString["swap"] = &tgui::String::swap;
        bindString["find"] = sol::overload(
            [](tgui::String* self, const std::string& str) -> std::size_t {
                return self->find(str);
            },
            [](tgui::String* self, const std::string& str, std::size_t pos) -> std::size_t {
                return self->find(str, pos);
            },
            [](tgui::String* self, const std::wstring& str) -> std::size_t {
                return self->find(str);
            },
            [](tgui::String* self, const std::wstring& str, std::size_t pos) -> std::size_t {
                return self->find(str, pos);
            },
            [](tgui::String* self, const std::u16string& str) -> std::size_t {
                return self->find(str);
            },
            [](tgui::String* self, const std::u16string& str, std::size_t pos) -> std::size_t {
                return self->find(str, pos);
            },
            [](tgui::String* self, const std::u32string& str) -> std::size_t {
                return self->find(str);
            },
            [](tgui::String* self, const std::u32string& str, std::size_t pos) -> std::size_t {
                return self->find(str, pos);
            },
            [](tgui::String* self, const tgui::String& str) -> std::size_t {
                return self->find(str);
            },
            [](tgui::String* self, const tgui::String& str, std::size_t pos) -> std::size_t {
                return self->find(str, pos);
            },
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t, std::size_t) const>(
                &tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t, std::size_t)
                    const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t, std::size_t)
                    const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t, std::size_t)
                    const>(&tgui::String::find),
            [](tgui::String* self, const char* s) -> std::size_t { return self->find(s); },
            [](tgui::String* self, const char* s, std::size_t pos) -> std::size_t {
                return self->find(s, pos);
            },
            [](tgui::String* self, const wchar_t* s) -> std::size_t { return self->find(s); },
            [](tgui::String* self, const wchar_t* s, std::size_t pos) -> std::size_t {
                return self->find(s, pos);
            },
            [](tgui::String* self, const char16_t* s) -> std::size_t { return self->find(s); },
            [](tgui::String* self, const char16_t* s, std::size_t pos) -> std::size_t {
                return self->find(s, pos);
            },
            [](tgui::String* self, const char32_t* s) -> std::size_t { return self->find(s); },
            [](tgui::String* self, const char32_t* s, std::size_t pos) -> std::size_t {
                return self->find(s, pos);
            },
            [](tgui::String* self, char ch) -> std::size_t { return self->find(ch); },
            [](tgui::String* self, char ch, std::size_t pos) -> std::size_t {
                return self->find(ch, pos);
            },
            [](tgui::String* self, wchar_t ch) -> std::size_t { return self->find(ch); },
            [](tgui::String* self, wchar_t ch, std::size_t pos) -> std::size_t {
                return self->find(ch, pos);
            },
            [](tgui::String* self, char16_t ch) -> std::size_t { return self->find(ch); },
            [](tgui::String* self, char16_t ch, std::size_t pos) -> std::size_t {
                return self->find(ch, pos);
            },
            [](tgui::String* self, char32_t ch) -> std::size_t { return self->find(ch); },
            [](tgui::String* self, char32_t ch, std::size_t pos) -> std::size_t {
                return self->find(ch, pos);
            });
        bindString["find_first_of"] = sol::overload(
            [](tgui::String* self, const std::string& str) -> std::size_t {
                return self->find_first_of(str);
            },
            [](tgui::String* self, const std::string& str, std::size_t pos) -> std::size_t {
                return self->find_first_of(str, pos);
            },
            [](tgui::String* self, const std::wstring& str) -> std::size_t {
                return self->find_first_of(str);
            },
            [](tgui::String* self, const std::wstring& str, std::size_t pos) -> std::size_t {
                return self->find_first_of(str, pos);
            },
            [](tgui::String* self, const std::u16string& str) -> std::size_t {
                return self->find_first_of(str);
            },
            [](tgui::String* self, const std::u16string& str, std::size_t pos) -> std::size_t {
                return self->find_first_of(str, pos);
            },
            [](tgui::String* self, const std::u32string& str) -> std::size_t {
                return self->find_first_of(str);
            },
            [](tgui::String* self, const std::u32string& str, std::size_t pos) -> std::size_t {
                return self->find_first_of(str, pos);
            },
            [](tgui::String* self, const tgui::String& str) -> std::size_t {
                return self->find_first_of(str);
            },
            [](tgui::String* self, const tgui::String& str, std::size_t pos) -> std::size_t {
                return self->find_first_of(str, pos);
            },
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t, std::size_t) const>(
                &tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t, std::size_t)
                    const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t, std::size_t)
                    const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t, std::size_t)
                    const>(&tgui::String::find_first_of),
            [](tgui::String* self, const char* s) -> std::size_t { return self->find_first_of(s); },
            [](tgui::String* self, const char* s, std::size_t pos) -> std::size_t {
                return self->find_first_of(s, pos);
            },
            [](tgui::String* self, const wchar_t* s) -> std::size_t {
                return self->find_first_of(s);
            },
            [](tgui::String* self, const wchar_t* s, std::size_t pos) -> std::size_t {
                return self->find_first_of(s, pos);
            },
            [](tgui::String* self, const char16_t* s) -> std::size_t {
                return self->find_first_of(s);
            },
            [](tgui::String* self, const char16_t* s, std::size_t pos) -> std::size_t {
                return self->find_first_of(s, pos);
            },
            [](tgui::String* self, const char32_t* s) -> std::size_t {
                return self->find_first_of(s);
            },
            [](tgui::String* self, const char32_t* s, std::size_t pos) -> std::size_t {
                return self->find_first_of(s, pos);
            },
            [](tgui::String* self, char ch) -> std::size_t { return self->find_first_of(ch); },
            [](tgui::String* self, char ch, std::size_t pos) -> std::size_t {
                return self->find_first_of(ch, pos);
            },
            [](tgui::String* self, wchar_t ch) -> std::size_t { return self->find_first_of(ch); },
            [](tgui::String* self, wchar_t ch, std::size_t pos) -> std::size_t {
                return self->find_first_of(ch, pos);
            },
            [](tgui::String* self, char16_t ch) -> std::size_t { return self->find_first_of(ch); },
            [](tgui::String* self, char16_t ch, std::size_t pos) -> std::size_t {
                return self->find_first_of(ch, pos);
            },
            [](tgui::String* self, char32_t ch) -> std::size_t { return self->find_first_of(ch); },
            [](tgui::String* self, char32_t ch, std::size_t pos) -> std::size_t {
                return self->find_first_of(ch, pos);
            });
        bindString["find_first_not_of"] = sol::overload(
            [](tgui::String* self, const std::string& str) -> std::size_t {
                return self->find_first_not_of(str);
            },
            [](tgui::String* self, const std::string& str, std::size_t pos) -> std::size_t {
                return self->find_first_not_of(str, pos);
            },
            [](tgui::String* self, const std::wstring& str) -> std::size_t {
                return self->find_first_not_of(str);
            },
            [](tgui::String* self, const std::wstring& str, std::size_t pos) -> std::size_t {
                return self->find_first_not_of(str, pos);
            },
            [](tgui::String* self, const std::u16string& str) -> std::size_t {
                return self->find_first_not_of(str);
            },
            [](tgui::String* self, const std::u16string& str, std::size_t pos) -> std::size_t {
                return self->find_first_not_of(str, pos);
            },
            [](tgui::String* self, const std::u32string& str) -> std::size_t {
                return self->find_first_not_of(str);
            },
            [](tgui::String* self, const std::u32string& str, std::size_t pos) -> std::size_t {
                return self->find_first_not_of(str, pos);
            },
            [](tgui::String* self, const tgui::String& str) -> std::size_t {
                return self->find_first_not_of(str);
            },
            [](tgui::String* self, const tgui::String& str, std::size_t pos) -> std::size_t {
                return self->find_first_not_of(str, pos);
            },
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t, std::size_t) const>(
                &tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t, std::size_t)
                    const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t, std::size_t)
                    const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t, std::size_t)
                    const>(&tgui::String::find_first_not_of),
            [](tgui::String* self, const char* s) -> std::size_t {
                return self->find_first_not_of(s);
            },
            [](tgui::String* self, const char* s, std::size_t pos) -> std::size_t {
                return self->find_first_not_of(s, pos);
            },
            [](tgui::String* self, const wchar_t* s) -> std::size_t {
                return self->find_first_not_of(s);
            },
            [](tgui::String* self, const wchar_t* s, std::size_t pos) -> std::size_t {
                return self->find_first_not_of(s, pos);
            },
            [](tgui::String* self, const char16_t* s) -> std::size_t {
                return self->find_first_not_of(s);
            },
            [](tgui::String* self, const char16_t* s, std::size_t pos) -> std::size_t {
                return self->find_first_not_of(s, pos);
            },
            [](tgui::String* self, const char32_t* s) -> std::size_t {
                return self->find_first_not_of(s);
            },
            [](tgui::String* self, const char32_t* s, std::size_t pos) -> std::size_t {
                return self->find_first_not_of(s, pos);
            },
            [](tgui::String* self, char ch) -> std::size_t { return self->find_first_not_of(ch); },
            [](tgui::String* self, char ch, std::size_t pos) -> std::size_t {
                return self->find_first_not_of(ch, pos);
            },
            [](tgui::String* self, wchar_t ch) -> std::size_t {
                return self->find_first_not_of(ch);
            },
            [](tgui::String* self, wchar_t ch, std::size_t pos) -> std::size_t {
                return self->find_first_not_of(ch, pos);
            },
            [](tgui::String* self, char16_t ch) -> std::size_t {
                return self->find_first_not_of(ch);
            },
            [](tgui::String* self, char16_t ch, std::size_t pos) -> std::size_t {
                return self->find_first_not_of(ch, pos);
            },
            [](tgui::String* self, char32_t ch) -> std::size_t {
                return self->find_first_not_of(ch);
            },
            [](tgui::String* self, char32_t ch, std::size_t pos) -> std::size_t {
                return self->find_first_not_of(ch, pos);
            });
        bindString["rfind"] = sol::overload(
            [](tgui::String* self, const std::string& str) -> std::size_t {
                return self->rfind(str);
            },
            [](tgui::String* self, const std::string& str, std::size_t pos) -> std::size_t {
                return self->rfind(str, pos);
            },
            [](tgui::String* self, const std::wstring& str) -> std::size_t {
                return self->rfind(str);
            },
            [](tgui::String* self, const std::wstring& str, std::size_t pos) -> std::size_t {
                return self->rfind(str, pos);
            },
            [](tgui::String* self, const std::u16string& str) -> std::size_t {
                return self->rfind(str);
            },
            [](tgui::String* self, const std::u16string& str, std::size_t pos) -> std::size_t {
                return self->rfind(str, pos);
            },
            [](tgui::String* self, const std::u32string& str) -> std::size_t {
                return self->rfind(str);
            },
            [](tgui::String* self, const std::u32string& str, std::size_t pos) -> std::size_t {
                return self->rfind(str, pos);
            },
            [](tgui::String* self, const tgui::String& str) -> std::size_t {
                return self->rfind(str);
            },
            [](tgui::String* self, const tgui::String& str, std::size_t pos) -> std::size_t {
                return self->rfind(str, pos);
            },
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t, std::size_t) const>(
                &tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t, std::size_t)
                    const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t, std::size_t)
                    const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t, std::size_t)
                    const>(&tgui::String::rfind),
            [](tgui::String* self, const char* s) -> std::size_t { return self->rfind(s); },
            [](tgui::String* self, const char* s, std::size_t pos) -> std::size_t {
                return self->rfind(s, pos);
            },
            [](tgui::String* self, const wchar_t* s) -> std::size_t { return self->rfind(s); },
            [](tgui::String* self, const wchar_t* s, std::size_t pos) -> std::size_t {
                return self->rfind(s, pos);
            },
            [](tgui::String* self, const char16_t* s) -> std::size_t { return self->rfind(s); },
            [](tgui::String* self, const char16_t* s, std::size_t pos) -> std::size_t {
                return self->rfind(s, pos);
            },
            [](tgui::String* self, const char32_t* s) -> std::size_t { return self->rfind(s); },
            [](tgui::String* self, const char32_t* s, std::size_t pos) -> std::size_t {
                return self->rfind(s, pos);
            },
            [](tgui::String* self, char ch) -> std::size_t { return self->rfind(ch); },
            [](tgui::String* self, char ch, std::size_t pos) -> std::size_t {
                return self->rfind(ch, pos);
            },
            [](tgui::String* self, wchar_t ch) -> std::size_t { return self->rfind(ch); },
            [](tgui::String* self, wchar_t ch, std::size_t pos) -> std::size_t {
                return self->rfind(ch, pos);
            },
            [](tgui::String* self, char16_t ch) -> std::size_t { return self->rfind(ch); },
            [](tgui::String* self, char16_t ch, std::size_t pos) -> std::size_t {
                return self->rfind(ch, pos);
            },
            [](tgui::String* self, char32_t ch) -> std::size_t { return self->rfind(ch); },
            [](tgui::String* self, char32_t ch, std::size_t pos) -> std::size_t {
                return self->rfind(ch, pos);
            });
        bindString["find_last_of"] = sol::overload(
            [](tgui::String* self, const std::string& str) -> std::size_t {
                return self->find_last_of(str);
            },
            [](tgui::String* self, const std::string& str, std::size_t pos) -> std::size_t {
                return self->find_last_of(str, pos);
            },
            [](tgui::String* self, const std::wstring& str) -> std::size_t {
                return self->find_last_of(str);
            },
            [](tgui::String* self, const std::wstring& str, std::size_t pos) -> std::size_t {
                return self->find_last_of(str, pos);
            },
            [](tgui::String* self, const std::u16string& str) -> std::size_t {
                return self->find_last_of(str);
            },
            [](tgui::String* self, const std::u16string& str, std::size_t pos) -> std::size_t {
                return self->find_last_of(str, pos);
            },
            [](tgui::String* self, const std::u32string& str) -> std::size_t {
                return self->find_last_of(str);
            },
            [](tgui::String* self, const std::u32string& str, std::size_t pos) -> std::size_t {
                return self->find_last_of(str, pos);
            },
            [](tgui::String* self, const tgui::String& str) -> std::size_t {
                return self->find_last_of(str);
            },
            [](tgui::String* self, const tgui::String& str, std::size_t pos) -> std::size_t {
                return self->find_last_of(str, pos);
            },
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t, std::size_t) const>(
                &tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t, std::size_t)
                    const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t, std::size_t)
                    const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t, std::size_t)
                    const>(&tgui::String::find_last_of),
            [](tgui::String* self, const char* s) -> std::size_t { return self->find_last_of(s); },
            [](tgui::String* self, const char* s, std::size_t pos) -> std::size_t {
                return self->find_last_of(s, pos);
            },
            [](tgui::String* self, const wchar_t* s) -> std::size_t {
                return self->find_last_of(s);
            },
            [](tgui::String* self, const wchar_t* s, std::size_t pos) -> std::size_t {
                return self->find_last_of(s, pos);
            },
            [](tgui::String* self, const char16_t* s) -> std::size_t {
                return self->find_last_of(s);
            },
            [](tgui::String* self, const char16_t* s, std::size_t pos) -> std::size_t {
                return self->find_last_of(s, pos);
            },
            [](tgui::String* self, const char32_t* s) -> std::size_t {
                return self->find_last_of(s);
            },
            [](tgui::String* self, const char32_t* s, std::size_t pos) -> std::size_t {
                return self->find_last_of(s, pos);
            },
            [](tgui::String* self, char ch) -> std::size_t { return self->find_last_of(ch); },
            [](tgui::String* self, char ch, std::size_t pos) -> std::size_t {
                return self->find_last_of(ch, pos);
            },
            [](tgui::String* self, wchar_t ch) -> std::size_t { return self->find_last_of(ch); },
            [](tgui::String* self, wchar_t ch, std::size_t pos) -> std::size_t {
                return self->find_last_of(ch, pos);
            },
            [](tgui::String* self, char16_t ch) -> std::size_t { return self->find_last_of(ch); },
            [](tgui::String* self, char16_t ch, std::size_t pos) -> std::size_t {
                return self->find_last_of(ch, pos);
            },
            [](tgui::String* self, char32_t ch) -> std::size_t { return self->find_last_of(ch); },
            [](tgui::String* self, char32_t ch, std::size_t pos) -> std::size_t {
                return self->find_last_of(ch, pos);
            });
        bindString["find_last_not_of"] = sol::overload(
            [](tgui::String* self, const std::string& str) -> std::size_t {
                return self->find_last_not_of(str);
            },
            [](tgui::String* self, const std::string& str, std::size_t pos) -> std::size_t {
                return self->find_last_not_of(str, pos);
            },
            [](tgui::String* self, const std::wstring& str) -> std::size_t {
                return self->find_last_not_of(str);
            },
            [](tgui::String* self, const std::wstring& str, std::size_t pos) -> std::size_t {
                return self->find_last_not_of(str, pos);
            },
            [](tgui::String* self, const std::u16string& str) -> std::size_t {
                return self->find_last_not_of(str);
            },
            [](tgui::String* self, const std::u16string& str, std::size_t pos) -> std::size_t {
                return self->find_last_not_of(str, pos);
            },
            [](tgui::String* self, const std::u32string& str) -> std::size_t {
                return self->find_last_not_of(str);
            },
            [](tgui::String* self, const std::u32string& str, std::size_t pos) -> std::size_t {
                return self->find_last_not_of(str, pos);
            },
            [](tgui::String* self, const tgui::String& str) -> std::size_t {
                return self->find_last_not_of(str);
            },
            [](tgui::String* self, const tgui::String& str, std::size_t pos) -> std::size_t {
                return self->find_last_not_of(str, pos);
            },
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t, std::size_t) const>(
                &tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t, std::size_t)
                    const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t, std::size_t)
                    const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t, std::size_t)
                    const>(&tgui::String::find_last_not_of),
            [](tgui::String* self, const char* s) -> std::size_t {
                return self->find_last_not_of(s);
            },
            [](tgui::String* self, const char* s, std::size_t pos) -> std::size_t {
                return self->find_last_not_of(s, pos);
            },
            [](tgui::String* self, const wchar_t* s) -> std::size_t {
                return self->find_last_not_of(s);
            },
            [](tgui::String* self, const wchar_t* s, std::size_t pos) -> std::size_t {
                return self->find_last_not_of(s, pos);
            },
            [](tgui::String* self, const char16_t* s) -> std::size_t {
                return self->find_last_not_of(s);
            },
            [](tgui::String* self, const char16_t* s, std::size_t pos) -> std::size_t {
                return self->find_last_not_of(s, pos);
            },
            [](tgui::String* self, const char32_t* s) -> std::size_t {
                return self->find_last_not_of(s);
            },
            [](tgui::String* self, const char32_t* s, std::size_t pos) -> std::size_t {
                return self->find_last_not_of(s, pos);
            },
            [](tgui::String* self, char ch) -> std::size_t { return self->find_last_not_of(ch); },
            [](tgui::String* self, char ch, std::size_t pos) -> std::size_t {
                return self->find_last_not_of(ch, pos);
            },
            [](tgui::String* self, wchar_t ch) -> std::size_t {
                return self->find_last_not_of(ch);
            },
            [](tgui::String* self, wchar_t ch, std::size_t pos) -> std::size_t {
                return self->find_last_not_of(ch, pos);
            },
            [](tgui::String* self, char16_t ch) -> std::size_t {
                return self->find_last_not_of(ch);
            },
            [](tgui::String* self, char16_t ch, std::size_t pos) -> std::size_t {
                return self->find_last_not_of(ch, pos);
            },
            [](tgui::String* self, char32_t ch) -> std::size_t {
                return self->find_last_not_of(ch);
            },
            [](tgui::String* self, char32_t ch, std::size_t pos) -> std::size_t {
                return self->find_last_not_of(ch, pos);
            });
        bindString["join"] = &tgui::String::join;
        bindString["npos"] = sol::var(&tgui::String::npos);
    }
};