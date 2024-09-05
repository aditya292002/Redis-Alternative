#include "Test.h"
#include "Data.h"
#include <json/json.h>
#include <iostream>

void Test::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback)
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

        // Store the key-value pair in the Data class
        Data::getInstance().storeKeyValue(key, value);

        // Return a success response
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        resp->setBody("Key-Value pair stored successfully");
        callback(resp);
    } else if (req->method() == Get) {
        std::cout << "GET request" << std::endl;

        // Extract the key from the request parameters
        auto key = req->getParameter("key");
        std::cout << "Key: " << key << std::endl;

        // Look for the key in the Data class
        auto value = Data::getInstance().getValue(key);
        if (!value.empty()) {
            // Return the value as JSON
            Json::Value json;
            json["key"] = key;
            json["value"] = value;

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
    } else if (req->method() == Delete) {
        std::cout << "DELETE request" << std::endl;

        // Extract the key from the request parameters
        auto key = req->getParameter("key");
        std::cout << "Key: " << key << std::endl;

        // Delete the key from the Data class
        bool deleted = Data::getInstance().deleteKey(key);
        if (deleted) {
            // Return a success response
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k200OK);
            resp->setBody("Key deleted successfully");
            callback(resp);
        } else {
            // Key not found
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k404NotFound);
            resp->setBody("Key not found");
            callback(resp);
        }
    } else if (req->method() == Patch) {
        std::cout << "PATCH request" << std::endl;

        // Extract the key and new value from the request parameters
        auto key = req->getParameter("key");
        auto newValue = req->getParameter("value");
        std::cout << "Key: " << key << std::endl;
        std::cout << "New Value: " << newValue << std::endl;

        // Update the key-value pair in the Data class
        if (Data::getInstance().getValue(key).empty()) {
            // Key not found
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k404NotFound);
            resp->setBody("Key not found");
            callback(resp);
        } else {
            Data::getInstance().storeKeyValue(key, newValue);
            // Return a success response
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k200OK);
            resp->setBody("Key-Value pair updated successfully");
            callback(resp);
        }
    } else if (req->method() == Options) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        resp->addHeader("Access-Control-Allow-Origin", "*");
        resp->addHeader("Access-Control-Allow-Methods", "POST, GET, DELETE, PATCH, OPTIONS");
        resp->addHeader("Access-Control-Allow-Headers", "Content-Type");
        callback(resp);
    }
}