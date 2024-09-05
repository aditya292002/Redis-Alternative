#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class Flush : public drogon::HttpSimpleController<Flush>
{
public:
    void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    // Add path definitions here
    PATH_ADD("/flush", "drogon::GetFilter", HttpMethod::Delete);
    PATH_ADD("/expire", HttpMethod::Post); // New path for setting key expiration
    PATH_LIST_END
};