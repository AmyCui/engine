//
// engine
//
// Copyright © 2016 D.E. Goodman-Wilson.
//

#pragma once

#include <string>
#include <slack/set_option.h>
#include <slack/web/auth.test.h>
#include <slack/base/slack_delegate.h>

namespace slack
{

namespace containers
{
class auth
{
public:
    auth(slack_delegate *delegate) : delegate_{delegate}
    { }

    ::slack::auth::test test() const
    {
        return ::slack::auth::test{delegate_->token()};
    }

private:
    const slack_delegate *delegate_;
};
} //namespace endpoints
} //namespace slack