#pragma once
#include<SFML/Graphics.hpp>
#include<TGUI/TGUI.hpp> // ui 
#include<TGUI/Backend/SFML-Graphics.hpp>
#include"LLM.h"
#include<future>
#include<optional> 

class ChatWindow {
    
public:
    ChatWindow(tgui::Gui& gui, float x, float y, float width, float height);
    void addMessage(const std::string& message, const std::string& sender = "User");
    void clear();
    void toggle();
    void setVisible(bool visible);
    bool isInputFocused() const;

    // LLM stuff 
    void setAPIKey(const std::string& key); 
    void setSystemPrompt(const std::string& prompt); 
    void setGraphContext(const std::string& context); 
    void clearGraphContext(); 
    void update(); // we call this in the main loop to check for async responses 

private:
    tgui::ChildWindow::Ptr childWindow;
    tgui::ChatBox::Ptr chatBox;
    tgui::EditBox::Ptr inputBox;

    // LLM
    LLM llm;
    std::optional<std::future<std::string>> pendingResponse; 
    bool waitingForResponse = false; 

    // graph context for llm 
    std::string graphContext; 
};
