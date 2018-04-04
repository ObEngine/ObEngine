#include <Backend/MenuBackend.hpp>
#include <Modes/Game.hpp>
#include <System/Path.hpp>

namespace obe::Backend
{
    void MenuBackend::play()
	{
        Modes::startGame();
	}

	void MenuBackend::edit()
	{
		m_code = MenuCode::Edit;
		m_window->close();
	}

	bool MenuBackend::hasBootFile() const
	{
		return !System::Path("boot.lua").find().empty();
	}

	bool MenuBackend::hasMapFolder() const
	{
		return !System::Path("Data/Maps").find(System::PathType::Directory).empty();
	}

    MenuCode MenuBackend::getAction() const
    {
        return m_code;
    }
}