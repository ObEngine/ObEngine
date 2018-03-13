#include <Scene/TXScene.hpp>
#include <Script/GlobalState.hpp>
#include <Triggers/TriggerDatabase.hpp>
#include <Utils/StringUtils.hpp>

namespace obe::Scene
{
    TXScene::TXScene(const std::string& id, bool scriptable) : Types::Identifiable(id)
    {
        if (scriptable)
        {
            m_script = std::make_unique<LuaComponent>();
        }
    }
    TXScene::~TXScene()
    {
            
    }

	void TXScene::clear()
	{
		for (auto& component : m_components)
		{
			component->remove();
		}
		m_components.clear();
	}

	void TXScene::dump(vili::ComplexNode& target) const
	{
	}

	void TXScene::load(vili::ComplexNode& data)
	{
	}

	std::vector<unsigned int> LuaComponent::AllEnvs;
	LuaComponent::LuaComponent()
    {
        m_triggerNamespace = Utils::String::getRandomKey(Utils::String::Alphabet + Utils::String::Numbers, 12);
        Triggers::TriggerDatabase::GetInstance()->createNamespace(m_triggerNamespace);
        m_localTriggers.reset(Triggers::TriggerDatabase::GetInstance()->createTriggerGroup(m_triggerNamespace, "Local"), Triggers::TriggerGroupPtrRemover);

        m_envIndex = Script::ScriptEngine["CreateNewEnv"]();
        AllEnvs.push_back(m_envIndex);
        //std::cout << "Environment Index is : " << m_envIndex << std::endl;

        //executeFile(m_envIndex, System::Path("Lib/Internal/ScriptInit.lua").find());
        //loadScrGameObject(this, m_objectScript.get());

        LUAENV["This"] = this;

        m_localTriggers
            ->addTrigger("Init")
            ->addTrigger("Delete");

        //LUAENV["__OBJECT_TYPE"] = m_type;
        //LUAENV["__OBJECT_ID"] = m_id;
        LUAENV["__OBJECT_INIT"] = false;
        LUAENV["Private"] = m_triggerNamespace;

        Script::executeFile(m_envIndex, System::Path("Lib/Internal/ObjectInit.lua").find());
    }
    void LuaComponent::execute(const std::string& path) const
    {
        Script::executeFile(m_envIndex, System::Path(path).find());
    }
}