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
    tgui::ChildWindow::Ptr chatWindowContainer;                     // main container for widgets, create this first and then add widgets to it, this groups related elements together (this can contain chat boxes, buttons, inputs) -> can be dragged, resized minimzed or closed (just depends on settings)
    tgui::ChatBox::Ptr chatBox;                                     // chat box element/widget we are going to put in the child window
    tgui::EditBox::Ptr inputBox;                                    // input box element/widget used for chat input in child

    // LLM
    LLM llm;
    std::optional<std::future<std::string>> pendingResponse; 
    bool waitingForResponse = false; 

    // graph context for llm 
    std::string graphContext; 

    std::string last_sender = "";
    bool changed = false;  
};
