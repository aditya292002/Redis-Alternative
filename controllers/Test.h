#pragma once
#include <drogon/HttpSimpleController.h>
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <jsoncpp/json/json.h>
#include <unordered_map>
using namespace drogon;
class Test:public drogon::HttpSimpleController<Test>
{
public:
    virtual void asyncHandleHttpRequest(const HttpRequestPtr &req,
                                        std::function<void (const HttpResponsePtr &)> &&callback)override;
    PATH_LIST_BEGIN
    //list path definitions here

    //example
    //PATH_ADD("/path","filter1","filter2",HttpMethod1,HttpMethod2...);

    // PATH_ADD("/",Get,Post);
    PATH_ADD("/set",Post);
    PATH_ADD("/get", Get);  // Route for GET /get/{key}
    PATH_LIST_END
private:
    std::unordered_map<std::string, std::string> keyValueStore;
};