#include <Bindings/tgui/tgui.hpp>

#include <TGUI/String.hpp>

#include <Bindings/Config.hpp>

namespace tgui::Bindings
{
    void LoadClassString(sol::state_view state)
    {
        sol::table tguiNamespace = state["tgui"].get<sol::table>();
        sol::usertype<tgui::String> bindString = tguiNamespace.new_usertype<tgui::String>(
            "String", sol::call_constructor,
            sol::constructors<tgui::String(), tgui::String(const std::string&),
                tgui::String(const std::wstring&), tgui::String(const std::u16string&),
                tgui::String(const std::u32string&), tgui::String(char),
                tgui::String(wchar_t), tgui::String(char16_t), tgui::String(char32_t),
                tgui::String(const char*), tgui::String(const wchar_t*),
                tgui::String(const char16_t*), tgui::String(const char32_t*),
                tgui::String(std::size_t, char), tgui::String(std::size_t, wchar_t),
                tgui::String(std::size_t, char16_t), tgui::String(std::size_t, char32_t),
                tgui::String(const std::string&, std::size_t),
                tgui::String(const std::wstring&, std::size_t),
                tgui::String(const std::u16string&, std::size_t),
                tgui::String(const std::u32string&, std::size_t),
                tgui::String(const std::string&, std::size_t, std::size_t),
                tgui::String(const std::wstring&, std::size_t, std::size_t),
                tgui::String(const std::u16string&, std::size_t, std::size_t),
                tgui::String(const std::u32string&, std::size_t, std::size_t),
                tgui::String(const char*, std::size_t),
                tgui::String(const wchar_t*, std::size_t),
                tgui::String(const char16_t*, std::size_t),
                tgui::String(const char32_t*, std::size_t),
                tgui::String(std::initializer_list<char>),
                tgui::String(std::initializer_list<wchar_t>),
                tgui::String(std::initializer_list<char16_t>),
                tgui::String(std::initializer_list<char32_t>),
                tgui::String(std::string::const_iterator, std::string::const_iterator),
                tgui::String(std::wstring::const_iterator, std::wstring::const_iterator),
                tgui::String(
                    std::u16string::const_iterator, std::u16string::const_iterator),
                tgui::String(
                    std::u32string::const_iterator, std::u32string::const_iterator)>());
        bindString["attemptToInt"] =

            [](tgui::String* self, int result) { self->attemptToInt(result); }

        ;
        bindString["attemptToUInt"] =

            [](tgui::String* self, unsigned int result) { self->attemptToUInt(result); }

        ;
        bindString["attemptToFloat"] =

            [](tgui::String* self, float result) { self->attemptToFloat(result); }

        ;
        bindString["toInt"]
            = sol::overload([](tgui::String* self) -> int { return self->toInt(); },
                [](tgui::String* self, int defaultValue) -> int {
                    return self->toInt(defaultValue);
                });
        bindString["toUInt"] = sol::overload(
            [](tgui::String* self) -> unsigned int { return self->toUInt(); },
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
            static_cast<tgui::String& (tgui::String::*)(const tgui::String&,
                const tgui::String&)>(&tgui::String::replace),
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
                tgui::String::const_iterator, const std::string&)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const std::wstring&)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const std::u16string&)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const std::u32string&)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const tgui::String&)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const std::string&, std::size_t, std::size_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const std::wstring&, std::size_t, std::size_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const std::u16string&, std::size_t, std::size_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const std::u32string&, std::size_t, std::size_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const tgui::String&, std::size_t, std::size_t)>(&tgui::String::replace),
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
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const char*, std::size_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const wchar_t*, std::size_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const char16_t*, std::size_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const char32_t*, std::size_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const char*, std::size_t)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const wchar_t*, std::size_t)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const char16_t*, std::size_t)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const char32_t*, std::size_t)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const char*)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const wchar_t*)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const char16_t*)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                const char32_t*)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const char*)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const wchar_t*)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const char16_t*)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, const char32_t*)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                std::size_t, char)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                std::size_t, wchar_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                std::size_t, char16_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                std::size_t, char32_t)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, std::size_t, char)>(&tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, std::size_t, wchar_t)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, std::size_t, char16_t)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, std::size_t, char32_t)>(
                &tgui::String::replace),
            static_cast<tgui::String& (tgui::String::*)(tgui::String::const_iterator,
                tgui::String::const_iterator, std::initializer_list<char>)>(
                &tgui::String::replace),
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
            static_cast<tgui::String& (tgui::String::*)(std::size_t, char)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, wchar_t)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, char16_t)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, char32_t)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const std::string&)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const std::wstring&)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const std::u16string&)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const std::u32string&)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const tgui::String&)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const std::string&, std::size_t,
                std::size_t)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const std::wstring&, std::size_t,
                std::size_t)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const std::u16string&,
                std::size_t, std::size_t)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const std::u32string&,
                std::size_t, std::size_t)>(&tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const tgui::String&, std::size_t,
                std::size_t)>(&tgui::String::assign),
            [](tgui::String* self, std::string str) { self->assign(std::move(str)); },
            [](tgui::String* self, std::wstring str) { self->assign(std::move(str)); },
            [](tgui::String* self, std::u16string str) { self->assign(std::move(str)); },
            [](tgui::String* self, std::u32string str) { self->assign(std::move(str)); },
            [](tgui::String* self, tgui::String str) { self->assign(std::move(str)); },
            static_cast<tgui::String& (tgui::String::*)(const char*, std::size_t)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const wchar_t*, std::size_t)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const char16_t*, std::size_t)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const char32_t*, std::size_t)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const char*)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const wchar_t*)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const char16_t*)>(
                &tgui::String::assign),
            static_cast<tgui::String& (tgui::String::*)(const char32_t*)>(
                &tgui::String::assign),
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
            static_cast<tgui::String::reference (tgui::String::*)(std::size_t)>(
                &tgui::String::at),
            static_cast<tgui::String::const_reference (tgui::String::*)(std::size_t)
                    const>(&tgui::String::at));
        bindString[sol::meta_function::index]
            = sol::overload(static_cast<tgui::String::const_reference (tgui::String::*)(
                                std::size_t) const>(&tgui::String::operator[]),
                static_cast<tgui::String::reference (tgui::String::*)(std::size_t)>(
                    &tgui::String::operator[]));
        bindString["front"]
            = sol::overload(static_cast<tgui::String::reference (tgui::String::*)()>(
                                &tgui::String::front),
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
            static_cast<tgui::String::reverse_iterator (tgui::String::*)()>(
                &tgui::String::rbegin),
            static_cast<tgui::String::const_reverse_iterator (tgui::String::*)() const>(
                &tgui::String::rbegin));
        bindString["crbegin"] = &tgui::String::crbegin;
        bindString["rend"] = sol::overload(
            static_cast<tgui::String::reverse_iterator (tgui::String::*)()>(
                &tgui::String::rend),
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
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                wchar_t)>(&tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                char16_t)>(&tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t,
                char32_t)>(&tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const std::string&)>(
                &tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t,
                const std::wstring&)>(&tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t,
                const std::u16string&)>(&tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t,
                const std::u32string&)>(&tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t,
                const tgui::String&)>(&tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const std::string&,
                std::size_t, std::size_t)>(&tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const std::wstring&,
                std::size_t, std::size_t)>(&tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t,
                const std::u16string&, std::size_t, std::size_t)>(&tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t,
                const std::u32string&, std::size_t, std::size_t)>(&tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const tgui::String&,
                std::size_t, std::size_t)>(&tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const char*,
                std::size_t)>(&tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const wchar_t*,
                std::size_t)>(&tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const char16_t*,
                std::size_t)>(&tgui::String::insert),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, const char32_t*,
                std::size_t)>(&tgui::String::insert),
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
                tgui::String::const_iterator, std::size_t, wchar_t)>(
                &tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, std::size_t, char16_t)>(
                &tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, std::size_t, char32_t)>(
                &tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, std::initializer_list<char>)>(
                &tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, std::initializer_list<wchar_t>)>(
                &tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, std::initializer_list<char16_t>)>(
                &tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, std::initializer_list<char32_t>)>(
                &tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, std::string::const_iterator,
                std::string::const_iterator)>(&tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, std::wstring::const_iterator,
                std::wstring::const_iterator)>(&tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, std::u16string::const_iterator,
                std::u16string::const_iterator)>(&tgui::String::insert),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, std::u32string::const_iterator,
                std::u32string::const_iterator)>(&tgui::String::insert));
        bindString["erase"] = sol::overload(
            static_cast<tgui::String& (tgui::String::*)(std::size_t, std::size_t)>(
                &tgui::String::erase),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator)>(&tgui::String::erase),
            static_cast<tgui::String::iterator (tgui::String::*)(
                tgui::String::const_iterator, tgui::String::const_iterator)>(
                &tgui::String::erase));
        bindString["push_back"] = sol::overload(
            static_cast<void (tgui::String::*)(char)>(&tgui::String::push_back),
            static_cast<void (tgui::String::*)(wchar_t)>(&tgui::String::push_back),
            static_cast<void (tgui::String::*)(char16_t)>(&tgui::String::push_back),
            static_cast<void (tgui::String::*)(char32_t)>(&tgui::String::push_back));
        bindString["pop_back"] = &tgui::String::pop_back;
        bindString["append"] = sol::overload(
            static_cast<tgui::String& (tgui::String::*)(std::size_t, char)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, wchar_t)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, char16_t)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(std::size_t, char32_t)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const std::string&)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const std::wstring&)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const std::u16string&)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const std::u32string&)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const tgui::String&)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const std::string&, std::size_t,
                std::size_t)>(&tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const std::wstring&, std::size_t,
                std::size_t)>(&tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const std::u16string&,
                std::size_t, std::size_t)>(&tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const std::u32string&,
                std::size_t, std::size_t)>(&tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const tgui::String&, std::size_t,
                std::size_t)>(&tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const char*, std::size_t)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const wchar_t*, std::size_t)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const char16_t*, std::size_t)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const char32_t*, std::size_t)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const char*)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const wchar_t*)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const char16_t*)>(
                &tgui::String::append),
            static_cast<tgui::String& (tgui::String::*)(const char32_t*)>(
                &tgui::String::append),
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
            static_cast<int (tgui::String::*)(const std::string&) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(const std::wstring&) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(const std::u16string&) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(const std::u32string&) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(const tgui::String&) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const std::string&) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const std::wstring&) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const std::u16string&) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const std::u32string&) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const tgui::String&) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const std::string&, std::size_t, std::size_t) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const std::wstring&, std::size_t, std::size_t) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const std::u16string&, std::size_t, std::size_t) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const std::u32string&, std::size_t, std::size_t) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t,
                const tgui::String&, std::size_t, std::size_t) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(const char*) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(const wchar_t*) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(const char16_t*) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(const char32_t*) const>(
                &tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char*)
                    const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const wchar_t*)
                    const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char16_t*)
                    const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char32_t*)
                    const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char*,
                std::size_t) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const wchar_t*,
                std::size_t) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char16_t*,
                std::size_t) const>(&tgui::String::compare),
            static_cast<int (tgui::String::*)(std::size_t, std::size_t, const char32_t*,
                std::size_t) const>(&tgui::String::compare));
        bindString["substr"] = sol::overload(
            [](tgui::String* self) -> tgui::String { return self->substr(); },
            [](tgui::String* self, std::size_t pos) -> tgui::String {
                return self->substr(pos);
            },
            [](tgui::String* self, std::size_t pos, std::size_t count) -> tgui::String {
                return self->substr(pos, count);
            });
        bindString["copy"] = sol::overload(
            [](tgui::String* self, char32_t* dest, std::size_t count) -> std::size_t {
                return self->copy(dest, count);
            },
            [](tgui::String* self, char32_t* dest, std::size_t count,
                std::size_t pos) -> std::size_t { return self->copy(dest, count, pos); });
        bindString["resize"] = sol::overload(
            static_cast<void (tgui::String::*)(std::size_t)>(&tgui::String::resize),
            static_cast<void (tgui::String::*)(std::size_t, char)>(&tgui::String::resize),
            static_cast<void (tgui::String::*)(std::size_t, wchar_t)>(
                &tgui::String::resize),
            static_cast<void (tgui::String::*)(std::size_t, char16_t)>(
                &tgui::String::resize),
            static_cast<void (tgui::String::*)(std::size_t, char32_t)>(
                &tgui::String::resize));
        bindString["swap"] = &tgui::String::swap;
        bindString["find"] = sol::overload(
            static_cast<std::size_t (tgui::String::*)(const std::string&, std::size_t)
                    const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const std::wstring&, std::size_t)
                    const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const std::u16string&, std::size_t)
                    const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const std::u32string&, std::size_t)
                    const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const tgui::String&, std::size_t)
                    const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(
                const char*, std::size_t, std::size_t) const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(
                const wchar_t*, std::size_t, std::size_t) const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(
                const char16_t*, std::size_t, std::size_t) const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(
                const char32_t*, std::size_t, std::size_t) const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t) const>(
                &tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t) const>(
                &tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t)
                    const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t)
                    const>(&tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(char, std::size_t) const>(
                &tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(wchar_t, std::size_t) const>(
                &tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(char16_t, std::size_t) const>(
                &tgui::String::find),
            static_cast<std::size_t (tgui::String::*)(char32_t, std::size_t) const>(
                &tgui::String::find));
        bindString["find_first_of"] = sol::overload(
            static_cast<std::size_t (tgui::String::*)(const std::string&, std::size_t)
                    const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const std::wstring&, std::size_t)
                    const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const std::u16string&, std::size_t)
                    const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const std::u32string&, std::size_t)
                    const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const tgui::String&, std::size_t)
                    const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t,
                std::size_t) const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t) const>(
                &tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t) const>(
                &tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t)
                    const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t)
                    const>(&tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(char, std::size_t) const>(
                &tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(wchar_t, std::size_t) const>(
                &tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(char16_t, std::size_t) const>(
                &tgui::String::find_first_of),
            static_cast<std::size_t (tgui::String::*)(char32_t, std::size_t) const>(
                &tgui::String::find_first_of));
        bindString["find_first_not_of"] = sol::overload(
            static_cast<std::size_t (tgui::String::*)(const std::string&, std::size_t)
                    const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const std::wstring&, std::size_t)
                    const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const std::u16string&, std::size_t)
                    const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const std::u32string&, std::size_t)
                    const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const tgui::String&, std::size_t)
                    const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t,
                std::size_t) const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t) const>(
                &tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t) const>(
                &tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t)
                    const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t)
                    const>(&tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(char, std::size_t) const>(
                &tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(wchar_t, std::size_t) const>(
                &tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(char16_t, std::size_t) const>(
                &tgui::String::find_first_not_of),
            static_cast<std::size_t (tgui::String::*)(char32_t, std::size_t) const>(
                &tgui::String::find_first_not_of));
        bindString["rfind"] = sol::overload(
            static_cast<std::size_t (tgui::String::*)(const std::string&, std::size_t)
                    const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const std::wstring&, std::size_t)
                    const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const std::u16string&, std::size_t)
                    const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const std::u32string&, std::size_t)
                    const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const tgui::String&, std::size_t)
                    const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(
                const char*, std::size_t, std::size_t) const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(
                const wchar_t*, std::size_t, std::size_t) const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(
                const char16_t*, std::size_t, std::size_t) const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(
                const char32_t*, std::size_t, std::size_t) const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t) const>(
                &tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t) const>(
                &tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t)
                    const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t)
                    const>(&tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(char, std::size_t) const>(
                &tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(wchar_t, std::size_t) const>(
                &tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(char16_t, std::size_t) const>(
                &tgui::String::rfind),
            static_cast<std::size_t (tgui::String::*)(char32_t, std::size_t) const>(
                &tgui::String::rfind));
        bindString["find_last_of"] = sol::overload(
            static_cast<std::size_t (tgui::String::*)(const std::string&, std::size_t)
                    const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const std::wstring&, std::size_t)
                    const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const std::u16string&, std::size_t)
                    const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const std::u32string&, std::size_t)
                    const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const tgui::String&, std::size_t)
                    const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t,
                std::size_t) const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t) const>(
                &tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t) const>(
                &tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t)
                    const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t)
                    const>(&tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(char, std::size_t) const>(
                &tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(wchar_t, std::size_t) const>(
                &tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(char16_t, std::size_t) const>(
                &tgui::String::find_last_of),
            static_cast<std::size_t (tgui::String::*)(char32_t, std::size_t) const>(
                &tgui::String::find_last_of));
        bindString["find_last_not_of"] = sol::overload(
            static_cast<std::size_t (tgui::String::*)(const std::string&, std::size_t)
                    const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const std::wstring&, std::size_t)
                    const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const std::u16string&, std::size_t)
                    const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const std::u32string&, std::size_t)
                    const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const tgui::String&, std::size_t)
                    const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t,
                std::size_t) const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t,
                std::size_t) const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const char*, std::size_t) const>(
                &tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const wchar_t*, std::size_t) const>(
                &tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const char16_t*, std::size_t)
                    const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(const char32_t*, std::size_t)
                    const>(&tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(char, std::size_t) const>(
                &tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(wchar_t, std::size_t) const>(
                &tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(char16_t, std::size_t) const>(
                &tgui::String::find_last_not_of),
            static_cast<std::size_t (tgui::String::*)(char32_t, std::size_t) const>(
                &tgui::String::find_last_not_of));
        bindString["join"] = &tgui::String::join;
        bindString["npos"] = sol::var(&tgui::String::npos);
    }
};