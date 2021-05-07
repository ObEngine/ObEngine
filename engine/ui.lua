local L = tgui.Layout;
local S = tgui.String;

local edit_box_username = tgui.EditBox.create();
edit_box_username:setSize(L"66.67%", L"12.5%");
edit_box_username:setPosition(L"parent.left + 20%", L"16.67%");
edit_box_username:setDefaultText(S"Username");
push_to_gui(gui, edit_box_username);

local edit_box_password = tgui.EditBox.create();
edit_box_password:setSize(L"66.67%", L"12.5%");
edit_box_password:setPosition(L"16.67%", L"41.6%");
edit_box_password:setPasswordCharacter("*");
edit_box_password:setDefaultText(S"Password");
push_to_gui(gui, edit_box_password);

local button = tgui.Button();
button:setText(S"Login");
button:setSize(L"50%", L"16.67%");
button:setPosition(L"25%", L"70%");
push_to_gui(gui, button);

function login(username, password)
    print(username:getText(), password:getText());
end

on_press(button, function() login(edit_box_username, edit_box_password) end);


--[[return ui.Module {
    id = "machin",
    position = "machin",
    ui.EditBox {
        id = "username",
        position = {"parent.left", "16.67%"},
        size = {"66.67%", "12.5%"},
        default_text = "Username",
    },
    ui.EditBox {
        id = "password",
        position = {"16.67%", "41.6%"},
        size = {"66.67%", "12.5%"},
        default_text = "Password",
        password_character = "*"
    },
    ui.Button {
        text = "Login",
        position = {"50%", "16.67%"},
        size = {"50%", "16.67%"},
        on_press = function(self, event)
            local username = self.parent.children.username;
            local password = self.parent.children.password;
            print(username.text, password.text);
        end
    }
}]]