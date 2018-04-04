#include <QQmlEngine>

#include <Backend/Backend.hpp>
#include <Backend/MenuBackend.hpp>
#include <Backend/ToolkitBackend.hpp>

namespace obe::Backend
{
    void RegisterTypes()
    {
        qmlRegisterType<MenuBackend>("obe.Backend.Menu", 1, 0, "MenuBackend");
        qmlRegisterType<ToolkitBackend>("obe.Backend.Toolkit", 1, 0, "ToolkitBackend");
    }
}