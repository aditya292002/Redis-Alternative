#include "Test.h"
void Test::asyncHandleHttpRequest(const HttpRequestPtr &req,
                                      std::function<void (const HttpResponsePtr &)> &&callback)
{
    if (req->method() == Post) {
        std::cout << "POST request" << std::endl;
        // Parse the JSON request body
        auto json = req->getJsonObject();
        if (!json) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k400BadRequest);
            resp->setBody("Invalid JSON");
            callback(resp);
            return;
        }

        // Extract key-value pair from JSON
        std::string key = json->get("key", "").asString();
        std::string value = json->get("value", "").asString();

        std::cout << "Key: " << key << std::endl;
        std::cout << "Value: " << value << std::endl;

        if (key.empty()) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k400BadRequest);
            resp->setBody("Key cannot be empty");
            callback(resp);
            return;
        }

        // Store the key-value pair in the unordered_map
        keyValueStore[key] = value;

        // Return a success response
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        resp->setBody("Key-Value pair stored successfully");
        callback(resp);
    }

    else {
        // Extract the key from the request path
        std::cout << "GET request" << std::endl;
        keyValueStore["father"] = "gopal"; // Add a sample key-value pair
        for(auto it = keyValueStore.begin(); it != keyValueStore.end(); ++it) {
            std::cout << it->first << " => " << it->second << std::endl;
        }


        auto key = req->getParameter("key");
        std::cout << "Key: " << key << std::endl;


        // Look for the key in the unordered_map
        auto it = keyValueStore.find(key);
        if (it != keyValueStore.end()) {
            // Return the value as JSON
            Json::Value json;
            json["key"] = key;
            json["value"] = it->second;

            auto resp = HttpResponse::newHttpJsonResponse(json);
            resp->setStatusCode(k200OK);
            callback(resp);
        } else {
            // Key not found
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k404NotFound);
            resp->setBody("Key not found");
            callback(resp);
        }
    }
}
