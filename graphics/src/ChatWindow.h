#pragma once
#include <SFML/Graphics.hpp>
#include<TGUI/TGUI.hpp> // ui 
#include <TGUI/Backend/SFML-Graphics.hpp>

class ChatWindow {
    
public:
    ChatWindow(tgui::Gui& gui, float x, float y, float width, float height);
    void addMessage(const std::string& message, const std::string& sender = "User");
    void clear();
    void toggle();
    void setVisible(bool visible);
    bool isInputFocused() const;

private:
    tgui::ChildWindow::Ptr childWindow;
    tgui::ChatBox::Ptr chatBox;
    tgui::EditBox::Ptr inputBox;
};
