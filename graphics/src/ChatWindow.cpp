#include "ChatWindow.h"

/// @brief create the chat window
/// @param gui 
/// @param x position x
/// @param y position y
/// @param width width
/// @param height height
ChatWindow::ChatWindow(tgui::Gui& gui, float x, float y, float width, float height) {
    chatWindowContainer = tgui::ChildWindow::create();
    chatWindowContainer->setCloseBehavior(tgui::ChildWindow::CloseBehavior::Hide); 
    chatWindowContainer->setPosition(x, y);
    chatWindowContainer->setSize(width, height);
    chatWindowContainer->setTitle("AI Assistant");
    chatWindowContainer->setResizable(true);
    chatWindowContainer->setPositionLocked(false);
    chatWindowContainer->setTitleTextSize(16); 
    // styling the window                       // IMPORTANT: shared renderer is used to make changes to many individual different child windows (we are using one but its fine) SO EFFECTIVELY IT IS FOR SYNCING STYLE ACCROSS MULTIPLE DIFFERNET CHILD WINDOWS (containers)
    auto windowRenderer = chatWindowContainer->getSharedRenderer(); // get the shared renderer so that we can customize the appearance (colors, borders, background, titlebar, etc)
    windowRenderer->setBackgroundColor(tgui::Color(30, 30, 35));
    windowRenderer->setBorderColor(tgui::Color(60, 60, 70)); 
    windowRenderer->setTitleBarColor(tgui::Color(45, 45, 55)); 
    windowRenderer->setTitleColor(tgui::Color::White); 


    // create chat box for displaying messages (leave space for input box)
    chatBox = tgui::ChatBox::create();
    chatBox->setSize({"100%", "100% - 46"}); // {"sets width (so 100% of parent containers width in this case)", "sets the height (100% - 50 means 100% of parent containers height but -50 pixels)"} -> so the chat box will always be the full height and width of the parent container/childWindow (-50px on the height)
    chatBox->setPosition("0", "0");
    chatBox->setTextSize(15); 
    chatBox->setLineLimit(100); // PROLLY NEED TO TWEAK THIS AS WE FIGURE OUT A GOOD LIMIT
    // style the chat box
    auto chatRenderer = chatBox->getSharedRenderer();
    chatRenderer->setBackgroundColor(tgui::Color(25, 25, 30)); 
    chatRenderer->setBorderColor(tgui::Color(50, 50, 60)); 
    chatRenderer->setBorders({0, 0, 0, 1}); 
    chatRenderer->setPadding({10, 10, 10, 10}); 
    chatWindowContainer->add(chatBox); // add this chat box to the container 

    // create input box for typing messages
    inputBox = tgui::EditBox::create();
    inputBox->setSize({"100% - 20", 36});
    inputBox->setPosition(10, "100% - 36 - 4"); // POSITION IS SET RELATIVE TO TOP LEFT OF PARENT CONTAINER, so this sets 10 from left edge to basically the bottom of the parent container
    inputBox->setDefaultText("Ask me anything...");
    inputBox->setTextSize(14); 
    // style the input box 
    auto inputRenderer = inputBox->getSharedRenderer(); // get the renderer so we can edit appearance
    inputRenderer->setBackgroundColor(tgui::Color(40, 40, 50));
    inputRenderer->setBackgroundColorHover(tgui::Color(50, 50, 65));  
    inputRenderer->setBackgroundColorFocused(tgui::Color(55, 55, 70)); 
    inputRenderer->setTextColor(tgui::Color(230, 230, 240)); 
    inputRenderer->setDefaultTextColor(tgui::Color(tgui::Color(230, 230, 240)));
    inputRenderer->setCaretColor(tgui::Color(100, 180, 255));
    inputRenderer->setBorderColor(tgui::Color(70, 70, 90));
    inputRenderer->setBorderColorHover(tgui::Color(90, 90, 120));
    inputRenderer->setBorderColorFocused(tgui::Color(100, 150, 220));
    inputRenderer->setBorders({1, 1, 1, 1});
    inputRenderer->setPadding({10, 8, 10, 8});
    chatWindowContainer->add(inputBox); // add the now customized element into the parent container (which is really the child window data structure)

    // handle Enter key to send message
    inputBox->onReturnKeyPress([this]() {
        std::string text = inputBox->getText().toStdString();
        if (!text.empty()) {
            addMessage(text, "You: ");
            inputBox->setText("");

            if (llm.isConfigured()) {
                waitingForResponse = true;
                addMessage("Thinking...", "AI:"); 

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

    gui.add(chatWindowContainer);
}

/// @brief this puts messages in the chat window
/// @param message 
/// @param sender 
void ChatWindow::addMessage(const std::string& message, const std::string& sender) {

    if (sender != last_sender) {
        last_sender = sender; 
        changed = true; 
    }
    else {
        changed = false; 
    } 


    // color coding messages based on sender 
    tgui::Color color;
    if (sender == "You") {
        color = tgui::Color(130, 200, 255); // light blue 
    }
    else if (sender == "AI:") {
        color = tgui::Color(180, 230, 180); // green
    }
    else if (sender == "System:") {
        color = tgui::Color(255, 200, 130); // orange 
    }
    else {
        color = tgui::Color(200, 200, 215); // light grey for default 
    }

    // add spacing between messages 
    std::string formattedMsg = sender + " " + message; 
    if (changed) {
        chatBox->addLine(""); // empty line for space between messages         
    } 
    chatBox->addLine(formattedMsg, color);


}

// clears chat history 
void ChatWindow::clear() {
    chatBox->removeAllLines();
}

// toggle for setting visible 
void ChatWindow::toggle() {
    chatWindowContainer->setVisible(!chatWindowContainer->isVisible());
}

// sets visible true or false 
void ChatWindow::setVisible(bool visible) {
    chatWindowContainer->setVisible(visible);
}

// for focusing input on window and ingoring sim inputs 
bool ChatWindow::isInputFocused() const {
    return inputBox->isFocused();
}

void ChatWindow::setAPIKey(const std::string& key) {
    llm.setApiKey(key); 
    addMessage("Welcome to the chat!", "System:");
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
            addMessage(response, "AI:");

            pendingResponse.reset(); 
            waitingForResponse = false; 

        }
    }
}
