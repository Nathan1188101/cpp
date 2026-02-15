#pragma once 
#include<string> 
#include<future> 
#include<optional> 

// TO DO: 
/*
I want to see if it's worth building context/memory and passing that with every message as it grows. 
gives the LLM some memory about the current session, instead of each message being independent. 

*/

class LLM {
    public:
        LLM(); 

        void setApiKey(const std::string& key);                                     // set API key, required before making requests 
        void setSystemPrompt(const std::string& prompt);                            // defines the AI's behaviour (for example you can tell it its purpose here)
        std::string chat(const std::string& userMessage);                           // send message from user and get a response from AI (remember httplib is I/O blocking so we need to do this asynchronosly)
        std::future<std::string> chatAsync(const std::string& userMessage);         // send message and get response asynchronously (httplib uses blocking, so this is our way around it. I belive this spawns a seperate thread for this work to be done and when the message is ready we recieve it all while not stopping the rest of the program (simulation from running))
        bool isConfigured() const;                                                  // for checking if API key is set (will be used when checking if connection is set up before sending messages from chat box UI)
        std::string getLastError() const;                                           // gets last error message 

    private: 
        std::string apiKey; 
        std::string systemPrompt;
        std::string apiEndPoint;
        std::string lastError; 
        std::string CLIENT;                                                         // url connection (eg. https://api.groq.com)

        std::string makeRequest(const std::string& userMessage); 

}; 