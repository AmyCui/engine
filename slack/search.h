
#pragma once

#include <string>
#include <slack/set_option.h>
#include <slack/web/search.messages.h>
#include <slack/base/slack_delegate.h>

namespace slack
{
    namespace containers
    {
        class search
        {
        public:
            search(slack_delegate *delegate) : delegate_{ delegate }
            {}

            template<class QUERY>
            ::slack::search::messages messages(QUERY &&query) const
            {
                return ::slack::search::messages{ delegate_->token(), std::forward<QUERY>(query) };
            }

            template<class QUERY, typename ...Os>
            ::slack::search::messages messages(QUERY &&query, Os &&...os) const
            {
                return ::slack::search::messages{ delegate_->token(), std::forward<QUERY>(query), std::forward<Os>(os)... };
            }


        private:
            const slack_delegate *delegate_;
        };
    }
}
