
#pragma once

#include <string>
#include <slack/set_option.h>
#include <slack/web/files.upload.h>
#include <slack/base/slack_delegate.h>

namespace slack
{
    namespace containers
    {
      class files
      {
      public:
        files(slack_delegate *delegate) : delegate_{delegate}
        {}

        template<class CHANNEL, class FILEPATH, typename ...Os>
        ::slack::files::upload upload(CHANNEL &&channel, FILEPATH &&filepath, Os &&...os) const
        {
            return ::slack::files::upload{delegate_->token(), std::forward<CHANNEL>(channel),  std::forward<FILEPATH>(filepath),
                                              std::forward<Os>(os)...};
        }

        template<class CHANNEL, class FILEPATH, typename ...Os>
        ::slack::files::upload upload(CHANNEL &&channel, FILEPATH &&filepath) const
        {
            return ::slack::files::upload{ delegate_->token(), std::forward<CHANNEL>(channel),  std::forward<FILEPATH>(filepath) };
        }

      private:
          const slack_delegate *delegate_;
      };
    }
}
