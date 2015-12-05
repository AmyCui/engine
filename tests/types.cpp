//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>
#include <json/json.h>


TEST(message, message_json_constructor)
{
    std::string raw_json = "{\"ok\":true,\"channel\":\"C01234567\",\"ts\":\"1448407807.000017\",\"message\":{\"text\":\"this is a api.test\",\"username\":\"bot\",\"type\":\"message\",\"subtype\":\"bot_message\",\"ts\":\"1448407807.000017\"}}";
    Json::Value result_ob;
    Json::Reader reader;
    bool parsed_success = reader.parse(raw_json, result_ob, false);
    ASSERT_TRUE(true);
    ASSERT_TRUE(parsed_success);
    auto ok = result_ob["ok"].asBool();
    ASSERT_TRUE(ok);
    slack::message m{result_ob["message"]};
    ASSERT_EQ(m.text, "this is a api.test");
}

TEST(incoming_webhooks, incoming_webhooks_basic)
{
    auto res = slack::incoming_webhook::payload::create_payload("foo", "bar").to_json();
    ASSERT_EQ("{\n\t\"channel_id\" : \"foo\",\n\t\"text\" : \"bar\"\n}", res); //TODO the whitespace makes this fragile!
}

TEST(incoming_webhooks, incoming_webhooks_advanced)
{
    auto res = slack::incoming_webhook::payload::create_payload("foo", "bar", slack::incoming_webhook::parameter::username{"baz"}).to_json();
    ASSERT_EQ("{\n\t\"channel_id\" : \"foo\",\n\t\"text\" : \"bar\",\n\t\"username\" : \"baz\"\n}", res); //TODO the ordering and whitespace makes this fragile!
}
