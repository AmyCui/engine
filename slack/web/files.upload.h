#pragma once

#include <slack/types.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <slack/event/message.h>
#include <string>
#include <vector>
#include <slack/optional.hpp>

namespace slack { namespace files
  {
    class upload : public slack::base::response
    {
    public:
      template<class TOKEN, class CHANNEL, class FILEPATH, typename ...Os>
      upload(TOKEN&& token, CHANNEL&& channel, FILEPATH&& filepath)
          : response{ std::forward<TOKEN>(token) }, channel_{ std::forward<CHANNEL>(channel) }, filepath_{ std::forward<FILEPATH>(filepath) }
      {
        initialize_();
      }

      template<class TOKEN, class CHANNEL, class FILEPATH, typename ...Os>
      upload(TOKEN&& token, CHANNEL&& channel, FILEPATH&& filepath, Os &&...os)
          : response{ std::forward<TOKEN>(token) }, channel_{ std::forward<CHANNEL>(channel) }, filepath_{ std::forward<FILEPATH>(filepath) }
      {
          slack::set_option<upload>(*this, std::forward<Os>(os)...);
          initialize_();
      }


      // parameters
      struct parameter
      {
         SLACK_MAKE_STRING_LIKE(filename);
         SLACK_MAKE_STRING_LIKE(initial_comment);
         SLACK_MAKE_STRING_LIKE(title);
      };

      // errors
      struct error : public slack::base::error
      {
        static const std::string CHANNEL_NOT_FOUND;
        static const std::string NOT_AUTHED;
        static const std::string INVALID_AUTH;
        static const std::string ACCOUNT_INACTIVE;
      };

      // response
      std::experimental::optional<slack::channel_id> channel;
      std::experimental::optional<slack::ts> ts;
      std::experimental::optional<slack::message> message;

      // parameter setters
      void set_option(const parameter::filename &filename)
      { filename_ = filename;}

      void set_option(parameter::filename &&filename)
      { filename_ = std::move(filename);}

      void set_option(const parameter::initial_comment &initial_comment)
      { initial_comment_ = initial_comment;}

      void set_option(parameter::initial_comment &&initial_comment)
      { initial_comment_ = std::move(initial_comment);}

      void set_option(const parameter::title &title)
      { title_ = title;}

      void set_option(parameter::title &&title)
      { title_ = std::move(title);}

    private:
        void initialize_();

        std::string filepath_;
        channel_id channel_;
        std::experimental::optional<parameter::filename> filename_;
        std::experimental::optional<parameter::initial_comment> initial_comment_;
        std::experimental::optional<parameter::title> title_;
      };
} } // namespace files slack
