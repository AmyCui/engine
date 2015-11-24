//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>

class Environment : public ::testing::Environment
{
    virtual void SetUp() override
    {
    }

    virtual void TearDown() override
    {
    }

};

int main(int argc, char **argv) {
    if (argc != 2)
    {
        std::cout << "USAGE: " << argv[0] << " xoxb-token-here" << std::endl;
        exit(-1);
    }

    std::string token = argv[1];

    slack::set_token(token);


    ::testing::InitGoogleTest(&argc, argv);

    ::testing::AddGlobalTestEnvironment(new Environment());

    return RUN_ALL_TESTS();
}

/***
#include <iostream>
#include <slack/slack.h>
#include <cpr.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "USAGE: " << argv[0] << " xoxb-token-here" << std::endl;
        exit(-1);
    }

    std::string token = argv[1];

    slack::set_token(token);

    std::cout << slack::api::test().raw_json << std::endl;
    slack::api::parameter::test::error e{"my error"};
    slack::api::parameter::test::foo f{"bar"};
    std::cout << slack::api::test(e).raw_json << std::endl;
    std::cout << slack::api::test(slack::api::parameter::test::error{"your error"}, slack::api::parameter::test::foo{"bar"}).raw_json << std::endl;
    std::cout << slack::api::test(e, slack::api::parameter::test::foo{"bar"}).raw_json << std::endl;


    auto auth_test = slack::auth::test();
    std::cout << auth_test.raw_json << std::endl;
    std::cout << auth_test.team_id.value() << std::endl;

    auto channels = slack::channels::list();
    ::slack::channel_id chan;
    for(const auto c : channels.channels)
    {
        std::cout << c.name << " " << c.id << std::endl;
        if(c.name == "donbot-messages")
        {
            chan = c.id;
            break;
        }
    }
    std::cout << channels.raw_json << std::endl;



    auto mesg = slack::chat::post_message(chan, "I LIVE!", slack::chat::parameter::post_message::username{"donbot"}, slack::chat::parameter::post_message::link_names{true});
    std::cout << mesg.message.text << std::endl;

    auto ts = mesg.ts;

    auto delete_it = slack::chat::delete_it(ts, chan);
    std::cout << delete_it.raw_json << std::endl;

    return 0;
}
 */