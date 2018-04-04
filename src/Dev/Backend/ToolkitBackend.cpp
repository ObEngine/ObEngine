#include <iostream>

#include <QColor>
#include <QTextCursor>
#include <SFML/Graphics/Color.hpp>

#include <Backend/ToolkitBackend.hpp>
#include <Bindings/Bindings.hpp>

namespace obe::Backend
{
    ToolkitBackend::ToolkitBackend()
    {
        std::cout << "Hello there, I'm TKB" << std::endl;
        toolkitState["This"] = &toolkitState;
        toolkitState.dofile("Lib/Internal/ScriptInit.lua");
        Bindings::BindTree(&toolkitState);
    }

    void ToolkitBackend::init()
    {
        std::cout << "Binding Over.." << std::endl;

        std::cout << "MTEXTEDIT : " << m_textEdit << std::endl;

        toolkitState["_term_display"] = kaguya::function([this](const std::vector<std::string>& strings, const std::vector<sf::Color>& colors)
        {
            QList<QVariant> msgs;
            for (int i = 0; i < strings.size(); i++)
            {
                sf::Color c = colors.at(i);
                QColor ccolor(c.r, c.g, c.b);
                msgs.append(QString::fromStdString("<font color='" + ccolor.name().toStdString() + "'>" + strings.at(i) + "</font>"));
            }
            QMetaObject::invokeMethod(this, "term_display", Q_ARG(QVariant, msgs));
        });
        toolkitState["_term_clear"] = kaguya::function([this]()
        {
            QMetaObject::invokeMethod(this, "term_clear");
        });
        toolkitEngine["_term_write"] = kaguya::function([&toolkitInput](const std::string& string)
        {
            QMetaObject::invokeMethod(this, "term_write", Q_ARG(QVariant, string));
        });
        toolkitState["_term_last"] = kaguya::function([this]()
        {
            m_textInput->moveCursor(QTextCursor::End);
        });
        toolkitState["_term_get"] = kaguya::function([this]() -> std::string
        {
            return m_textInput->toPlainText().toStdString();
        });
        toolkitState["_term_close"] = kaguya::function([this]()
        {
            m_window->close();
        });

        toolkitState.dofile("Lib/Toolkit/Toolkit.lua");
    }

    void ToolkitBackend::execute(const QString& code)
    {
        std::cout << "Code executed : " << code.toStdString() << std::endl;
        toolkitState(code.toStdString());
    }
}