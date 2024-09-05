#include "Flush.h"
#include "Data.h"
#include <json/json.h>
#include <iostream>

void Flush::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    if (req->method() == Delete) {
        std::cout << "DELETE request to flush all keys" << std::endl;

        // Delete all keys from the Data class
        Data::getInstance().deleteAllKeys();

        // Return a success response
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        resp->setBody("All keys deleted successfully");
        callback(resp);
    } else if (req->method() == Post && req->path() == "/expire") {
        std::cout << "POST request to set key expiration" << std::endl;

        // Parse the JSON request body
        auto json = req->getJsonObject();
        std::cout << "JSON: " << std::endl;

        if (!json) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k400BadRequest);
            resp->setBody("Invalid JSON");
            callback(resp);
            return;
        }


        // Extract key and expiration time from JSON
        std::string key = json->get("key", "").asString();
        auto seconds_ = json->get("seconds", 0);

        std::cout << "Key: " << key << std::endl;
        std::cout << "Seconds: " << seconds_ << std::endl;
        int seconds = seconds_.asInt();

        if (key.empty() || seconds <= 0) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k400BadRequest);
            resp->setBody("Invalid key or expiration time");
            callback(resp);
            return;
        }

        // Set the expiration time for the key
        Data::getInstance().setKeyExpiration(key, seconds);

        // Return a success response
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        resp->setBody("Key expiration set successfully");
        callback(resp);
    } else {
        // Method not allowed
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k405MethodNotAllowed);
        resp->setBody("Method not allowed");
        callback(resp);
    }
}