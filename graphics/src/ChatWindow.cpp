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
