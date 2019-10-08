#pragma once

#include <memory>
#include <unordered_map>

#include <Input/InputButton.hpp>

namespace obe::Input
{
    extern std::unordered_map<std::string, std::unique_ptr<InputButton>>
        AllKeys;
    /**
     * \brief Initialize the list of all the keys
     */
    void InitKeyList();
    /**
     * \brief Initialize (or reinitialize) the list of all gamepad buttons and
     * axis
     */
    void SetGamepadList();
    /**
     * \brief Get a InputButton that is inside the AllKeys Map
     * \param keyId Id of the InputButton to retrieve
     * \return A pointer to the InputButton if found
     * @Bind
     */
    InputButton* GetKey(const std::string& keyId);

    /**
     * \brief Return all currently pressed InputButton in a std::vector
     * \return Returns a std::vector of InputButton pointers being currently
     * pressed
     */
    std::vector<InputButton*> GetAllPressedButtons();
} // namespace obe::Input