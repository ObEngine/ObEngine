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
        m_toolkitState["This"] = &m_toolkitState;
        m_toolkitState.dofile("Lib/Internal/ScriptInit.lua");
        Bindings::BindTree(&m_toolkitState);
    }

    void ToolkitBackend::init()
    {
        m_toolkitState["_term_display"] = kaguya::function([this](const std::vector<std::string>& strings, const std::vector<sf::Color>& colors)
        {
            QString msgs;
            for (int i = 0; i < strings.size(); i++)
            {
                sf::Color c = colors.at(i);
                QColor ccolor(c.r, c.g, c.b);
                msgs += QString::fromStdString("<font color='" + ccolor.name().toStdString() + "'>" + strings.at(i) + "</font>");
            }
            //QMetaObject::invokeMethod(this, "term_display", Q_ARG(QVariant, msgs));
            this->termDisplay(msgs);
        });
        m_toolkitState["_term_clear"] = kaguya::function([this]()
        {
            QMetaObject::invokeMethod(this, "term_clear");
        });
        m_toolkitState["_term_write"] = kaguya::function([this](const std::string& string)
        {
            QMetaObject::invokeMethod(this, "term_write", Q_ARG(QVariant, QString::fromStdString(string)));
        });
        m_toolkitState["_term_last"] = kaguya::function([this]()
        {
            QMetaObject::invokeMethod(this, "term_last");
        });
        m_toolkitState["_term_get"] = kaguya::function([this]() -> std::string
        {
            QVariant returnedValue;
            QMetaObject::invokeMethod(this, "term_get", Q_RETURN_ARG(QVariant, returnedValue));
            return returnedValue.toString().toStdString();
        });
        m_toolkitState["_term_close"] = kaguya::function([this]()
        {
            m_window->close();
        });

        m_toolkitState.dofile("Lib/Toolkit/Toolkit.lua");
    }

    void ToolkitBackend::execute(const QString& code)
    {
        std::cout << "Code executed : " << code.toStdString() << std::endl;

        m_toolkitState["evaluate"](code.toStdString());
        m_commandHistory.erase(std::remove_if(m_commandHistory.begin(), m_commandHistory.end(), [&code](const std::string& command) {
            return (command == code.toStdString());
        }), m_commandHistory.end());
        m_commandHistory.push_back(code.toStdString());
        m_commandHistoryIndex = m_commandHistory.size();
    }

	void ToolkitBackend::autocomplete()
	{
		std::cout << "Autocomplete from Backend" << std::endl;
		std::cout << "Got input content" << std::endl;
		m_toolkitState["autocomplete"](m_input.toStdString());
		std::cout << "Autocomplete function called" << std::endl;
	}
}

#include "ToolkitBackend.moc"