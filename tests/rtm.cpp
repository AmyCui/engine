//
// Copyright © 2015 D.E. Goodman-Wilson. All rights reserved.
//

#include <gtest/gtest.h>
#include <slack/slack.h>

TEST(rtm_start, rtm_start_basic)
{
    auto result = slack::rtm::start();
    ASSERT_TRUE(result);
    ASSERT_GT(result.url->length(), 0);
}
