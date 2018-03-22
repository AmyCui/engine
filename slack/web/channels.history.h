
#pragma once

#include <slack/types.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <string>
#include <vector>
#include <slack/optional.hpp>

namespace slack { namespace channels
{
    class history:
      public slack::base::response
      {
      public:
        //public interface
        template<class TOKEN, class CHANNEL>
        history(TOKEN &&token, CHANNEL &&channel) :
          response{std::forward<TOKEN>(token)},
          channel_{std::forward<CHANNEL>(channel)}
        {
            initialize_();
        }

        template<class TOKEN, class CHANNEL, typename ...Os>
        history(TOKEN &&token, CHANNEL &&channel, Os &&...os) :
            response{ std::forward<TOKEN>(token) },
            channel_{ std::forward<CHANNEL>(channel) }
        {
            slack::set_option<history>(*this, std::forward<Os>(os)...);
            initialize_();
        }


        //parameters
        struct parameter
        {
            SLACK_MAKE_STRING_LIKE(count);
            SLACK_MAKE_STRING_LIKE(latest);
            SLACK_MAKE_STRING_LIKE(oldest);
            SLACK_MAKE_STRING_LIKE(unreads);
        };

        // response
        std::vector<slack::message> messages;
        std::experimental::optional<slack::channel_id> channel;

        // parameter setters
        void set_option(const parameter::count &count)
        {count_ = count;}

        void set_option(parameter::count &&count)
        {count_ = std::move(count);}

        void set_option(const parameter::latest &latest)
        {latest_ = latest;}

        void set_option(parameter::latest &&latest)
        {latest_ = std::move(latest);}

        void set_option(const parameter::oldest &oldest)
        {oldest_ = oldest;}

        void set_option(parameter::oldest &&oldest)
        {oldest_ = std::move(oldest);}

        void set_option(const parameter::unreads &unreads)
        {unreads_ = unreads;}

        void set_option(parameter::unreads &&unreads)
        {unreads_ = std::move(unreads);}

      private:
        void initialize_();

        channel_id channel_;
        std::experimental::optional<parameter::count> count_;
        std::experimental::optional<parameter::latest> latest_;
        std::experimental::optional<parameter::oldest> oldest_;
        std::experimental::optional<parameter::unreads> unreads_;

      }; // class history
} // namespace channels
} // namespace slack
