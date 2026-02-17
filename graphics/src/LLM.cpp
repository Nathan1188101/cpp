#include"LLM.h" 

// by default this lib only support plain HTTP (unencrypted and unauthenticated method for transmitting web data), so this enables the code
// from the lib we need in order to handle secure HTTPS connections
// need to define this before including httplib to correctly enable it 
#define CPPHTTPLIB_OPENSSL_SUPPORT 
#include"httplib.h"         // for http requests 
#include<iostream> 
#include<nlohmann/json.hpp> // for json 



LLM::LLM() 
: apiEndPoint("end_point_here"), 
  systemPrompt("You are a helpful assistant for a evolutionary dynamics on graphs simulator. Keep responses concise."),
  CLIENT("https://api.groq.com")
{    
}

/// @brief set the API key for the connection to the LLM 
/// @param key the key 
void LLM::setApiKey(const std::string& key) {
    apiKey = key; 
}

/// @brief sets the system prompt that defines the AI behaviour
/// @param prompt is the prompt 
void LLM::setSystemPrompt(const std::string& prompt) {
    systemPrompt = prompt; 
}

/// @brief bool for if the API key is set or not 
/// @return true/false
bool LLM::isConfigured() const {
    return !apiKey.empty(); // true if not empty, false if empty 
}

/// @brief returns the last error 
/// @return 
std::string LLM::getLastError() const {
    return lastError; 
}

/// @brief spawns a new thread to perform the httplib request that uses blocking, if we didn't do this it would stop 
///        the entire program until we recieve a message back from the source
/// @param userMessage 
/// @return 
std::future<std::string> LLM::chatAsync(const std::string& userMessage) {
    // std::launch::async spawns a new thread to run the blocking HTTP request, so the rest of the program can keep running while this does it's thing
    return std::async(std::launch::async, [this, userMessage]() {
        return makeRequest(userMessage); 
    });
}

std::string LLM::makeRequest(const std::string& userMessage) {
    if (!isConfigured()) {
        lastError = "API key not set";
        return "[Error: API key not configured]"; 
    }

    try {
        httplib::Client client(CLIENT);     // create a HTTPS client (right now we're using Groq API) 
        client.set_connection_timeout(30);  // sets connection to timeout after 30 seconds, if the client cannot establish a connection
        client.set_read_timeout(60);        // this sets max time client will wait for server response AFTER connection is established (server reply)

        // build json requeset body using nlohmann 
        nlohmann::json requestBody = {
            {"model", "llama-3.3-70b-versatile"},
            {"messages", {
                {{"role", "system"}, {"content", systemPrompt}},
                {{"role", "user"}, {"content", userMessage}}
            }},
            {"max_tokens", 500}, // might need to change idk 
            {"temperature", 0.7} // I remember doing this in python, temperature controls the randomness/creativity of the AI's response 
            // low temp = 0.0 - 0.3 = more focused and technical 
            // medium = balanced response 
            // high temp = 0.8 - 1.0+ = more creative and varied, can be less accurate 
        };

        // converts requestBody into a string in standard JSON format, the other end will deserialize it (needed because HTTP APIs expect a string and not a c++ object)
        std::string body = requestBody.dump(); 

        // form that Groq needs 
        httplib::Headers headers = {
            {"Authorization", "Bearer " + apiKey}
        };

        // make POST request 
        auto response = client.Post("/openai/v1/chat/completions", headers, body, "application/json");

        if (!response) {
            lastError = "Error: no response";
            return "[Error: Post didn't work, network error]"; 
        }

        // if request wasn't successful 
        if (response->status != 200) {

            // set last error to include the status of the raw response body 
            lastError = "API error (HTTP " + std::to_string(response->status) + "): " + response->body; 

            // then try and to parse the response body as JSON to see if it contains more specific info 
            try {

                // parse the response 
                nlohmann::json errorJson = nlohmann::json::parse(response->body); 

                // checking (key value pairs of json), so looking for "error" key, and if that error key contains a "message" field
                // so if there an error message we return it 
                if (errorJson.contains("error") && errorJson["error"].contains("message")) {
                    return "[Error: " + errorJson["error"]["message"].get<std::string>() + "]"; // return the error message if one exists 
                }
                // if it fails we print an error msg to console 
            } catch (const nlohmann::json::exception& e) {std::cout << "ERROR parsing error message from server: " << std::endl;}

            // return a generic error message with HTTP status if nothing was found 
            return "[Error: API returned status " + std::to_string(response->status) + "]"; 

        }

        // parse response 
        nlohmann::json responseJson = nlohmann::json::parse(response->body); 

        // this is how Groq and OpenAI structure their API responses 
        if (responseJson.contains("choices") && !responseJson["choices"].empty()) {
            return responseJson["choices"][0]["message"]["content"].get<std::string>(); 
        } else {
            lastError = "Unexpected API response format"; 
            return "[Error: Unexpected response format]"; 
        }

    } catch (const nlohmann::json::exception& e) {
        lastError = std::string("JSON error: ") + e.what(); 
        return "[Error: failed to parse response]"; 
    } catch (const std::exception& e) {
        lastError = std::string("Error") + e.what(); 
        return "[Error: " + std::string(e.what()) + "]"; 
    }
}