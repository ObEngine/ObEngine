#pragma once

#include <kaguya/kaguya.hpp>
#include <QString>
#include <QTextEdit>

#include <Backend/Backend.hpp>

namespace obe::Backend
{
    class ToolkitBackend : public Backend
	{
		Q_OBJECT
        private:
            kaguya::State m_toolkitState;
			std::vector<std::string> m_commandHistory;
			unsigned m_commandHistoryIndex = 0;
        public:
            ToolkitBackend();
            Q_INVOKABLE void init();
			Q_INVOKABLE void execute(const QString& code);
			Q_INVOKABLE void autocomplete();
		signals:
			void termDisplay(QList<QString> strings);
	};
}

#include "ToolkitBackend.moc"