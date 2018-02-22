//
// engine
//
// Copyright © 2015–2016 D.E. Goodman-Wilson. All rights reserved.
//

#include "private.h"
#include "web_client.h"
#include <cpr/cpr.h>
#include <filesystem>

namespace slack_private
{


Json::Value parse(slack::base::response *obj, const std::string &json)
{
    obj->raw_json = json;

    Json::Value result_ob;

    Json::Reader reader;
    bool parsed_success = reader.parse(json, result_ob, false);
    if (!parsed_success)
    {
        obj->error_message = std::string{"json_parse_failure"};
        return result_ob;
    }

    if (!result_ob["ok"].isBool())
    {
        obj->error_message = std::string{"invalid_response"};
        return result_ob;
    }

    auto ok = result_ob["ok"].asBool();

    if (!ok)
    {
        obj->error_message = result_ob["error"].asString();
        return result_ob;
    }

    return result_ob;
}

Json::Value get(slack::base::response *obj, const std::string &endpoint, const slack::http::params &params, bool auth)
{
    Json::Value result_ob;

    cpr::Parameters p;
    for (auto &kv : params)
    {
        p.AddParameter({kv.first, kv.second});
    }

    auto response = cpr::Get(cpr::Url{slack::web_client::get_uri() + endpoint}, p);

    if (response.status_code != 200)
    {
        //TODO do something!
        obj->error_message = std::string{std::to_string(response.status_code)};
        return result_ob;
    }

    return parse(obj, response.text);
}

Json::Value post(slack::base::response *obj, const std::string &endpoint, const slack::http::params &params, const std::string &filepath)
{
    Json::Value result_ob;
    // use multipart/form-data
    cpr::Multipart mp{};
    // add a File part if filepath exists
    if (!filepath.empty())
    {
        // make sure the path is the correct format
        std::string path_formatted = std::experimental::filesystem::path(filepath).string();
        mp.parts.push_back(cpr::Part{ "file", cpr::File{ path_formatted } });
    }
    for (auto &kv : params)
    {
        mp.parts.push_back(cpr::Part{ kv.first, kv.second });
    }

    auto response = cpr::Post(cpr::Url{ slack::web_client::get_uri() + endpoint }, mp);

    if (response.status_code != 200)
    {
        obj->error_message = std::string{ std::to_string(response.status_code) };
        return result_ob;
    }

    return parse(obj, response.text);
}

// TODO should this be static instead of a singleton?
factory<slack::base::event> events_factory;

} //namespace slack_private