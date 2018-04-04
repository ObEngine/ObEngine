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
            kaguya::State toolkitState;
            Q_PROPERTY(QTextEdit* textEdit MEMBER m_textEdit)
            QTextEdit* m_textEdit;
            Q_PROPERTY(QTextEdit* textInput MEMBER m_textInput)
            QTextEdit* m_textInput;
        public:
            ToolkitBackend();
            Q_INVOKABLE void init();
			Q_INVOKABLE void execute(const QString& code);
	};
}

#include "ToolkitBackend.moc"