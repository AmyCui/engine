//
// Copyright © 2015 Slack Technologies, Inc. All rights reserved.
//

#include "config.h"
#include <string>

namespace slack_config
{
    std::string token_ = "";
}

namespace slack
{
    void set_token(std::string token)
    {
        ::slack_config::token_ = token;
    }
}