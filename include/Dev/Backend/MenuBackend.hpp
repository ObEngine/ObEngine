#pragma once

#include <Backend/Backend.hpp>

namespace obe::Backend
{
    enum class MenuCode
    {
        None,
        Play,
        Edit,
        Help
    };

    class MenuBackend : public Backend
	{
		Q_OBJECT
    private:
        MenuCode m_code = MenuCode::None;
	public:
		Q_INVOKABLE void play();
		Q_INVOKABLE void edit();
		Q_INVOKABLE bool hasBootFile() const;
		Q_INVOKABLE bool hasMapFolder() const;
        MenuCode getAction() const;
	};
}

#include "MenuBackend.moc"