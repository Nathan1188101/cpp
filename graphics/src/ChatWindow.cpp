#include "ChatWindow.h"

/// @brief create the chat window
/// @param gui 
/// @param x position x
/// @param y position y
/// @param width width
/// @param height height
ChatWindow::ChatWindow(tgui::Gui& gui, float x, float y, float width, float height) {
    childWindow = tgui::ChildWindow::create();
    childWindow->setPosition(x, y);
    childWindow->setSize(width, height);
    childWindow->setTitle("Chat");
    childWindow->setResizable(true);
    childWindow->setPositionLocked(false);

    // Create chat box for displaying messages (leave space for input box)
    chatBox = tgui::ChatBox::create();
    chatBox->setSize({"100%", "100% - 30"});
    chatBox->setPosition(0, 0);
    childWindow->add(chatBox);

    // Create input box for typing messages
    inputBox = tgui::EditBox::create();
    inputBox->setSize({"100%", 30});
    inputBox->setPosition(0, chatBox->getSize().y);
    inputBox->setDefaultText("Type a message...");
    childWindow->add(inputBox);

    // Handle Enter key to send message
    inputBox->onReturnKeyPress([this]() {
        std::string text = inputBox->getText().toStdString();
        if (!text.empty()) {
            addMessage(text, "You");
            inputBox->setText("");

            if (llm.isConfigured()) {
                waitingForResponse = true;
                addMessage("Thinking...", "AI"); 

                // prepend graph context if avilable 
                std::string fullMessage = text; 
                if (!graphContext.empty()) {
                    // if there is graph context, include it 
                    fullMessage = "[Current Graph State]\n" + graphContext + "\n\n[User Question]\n" + text; 
                }

                pendingResponse = llm.chatAsync(fullMessage); // send message asynchronosly so rest of sim still runs while waiting for response

            } else {
                addMessage("LLM was unable to configure. Check API key."); 
            }

        }
    });

    gui.add(childWindow);
}

/// @brief this puts messages in the chat window
/// @param message 
/// @param sender 
void ChatWindow::addMessage(const std::string& message, const std::string& sender) {
    chatBox->addLine(sender + ": " + message);
}

// clears chat history 
void ChatWindow::clear() {
    chatBox->removeAllLines();
}

// toggle for setting visible 
void ChatWindow::toggle() {
    childWindow->setVisible(!childWindow->isVisible());
}

// sets visible true or false 
void ChatWindow::setVisible(bool visible) {
    childWindow->setVisible(visible);
}

// for focusing input on window and ingoring sim inputs 
bool ChatWindow::isInputFocused() const {
    return inputBox->isFocused();
}

void ChatWindow::setAPIKey(const std::string& key) {
    llm.setApiKey(key); 
    addMessage("API key configured", "System") ;
}

void ChatWindow::setSystemPrompt(const std::string& prompt) {
    llm.setSystemPrompt(prompt);
}

void ChatWindow::setGraphContext(const std::string& context) {
    graphContext = context; 
}

/// @brief clears graph context 
void ChatWindow::clearGraphContext() {
    graphContext.clear(); 
}

void ChatWindow::update() {
    if (waitingForResponse && pendingResponse.has_value()) {
        // check if fugure is ready 
        auto status = pendingResponse->wait_for(std::chrono::milliseconds(0)); 

        // if async call is ready/done
        if (status == std::future_status::ready) {

            // get the response message from llm API 
            std::string response = pendingResponse->get(); 

            // display the response in the window 
            addMessage(response, "AI");

            pendingResponse.reset(); 
            waitingForResponse = false; 

        }
    }
}
