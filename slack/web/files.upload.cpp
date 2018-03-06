#include "slack/web/files.upload.h"
#include "private.h"
#include <sstream>

namespace slack { namespace files
  {
    // errors
    const std::string upload::error::CHANNEL_NOT_FOUND = std::string{"channel_not_found"};
    const std::string upload::error::NOT_AUTHED = std::string{"not_authed"};
    const std::string upload::error::INVALID_AUTH = std::string{"invalid_auth"};
    const std::string upload::error::ACCOUNT_INACTIVE = std::string{"account_inactive"};


    void upload::initialize_()
    {
      auto params = default_params({
              {"channels", channel_}
      });

      //optional parameters
      if(filename_)
      {
        params.emplace("filename", *filename_);
      }
      if(initial_comment_)
      {
        params.emplace("initial_comment", *initial_comment_);
      }
      if(title_)
      {
        params.emplace("title", *title_);
      }

      auto result_ob = slack_private::post(this, "files.upload", params, filepath_);
      if (this->success())
      {
          if (result_ob["channel"].isString()) channel = slack::channel_id{ result_ob["channel"].asString() };
          if (result_ob["ts"].isString()) ts = slack::ts{ result_ob["ts"].asString() };
          
        message = slack::message{};
        message->text = "ok";
        if (result_ob["channel"].isString())
            message->channel = slack::channel_id{ result_ob["channel"].asString() };
        if (result_ob["ts"].isString())
            message->ts = slack::ts{ result_ob["ts"].asString() };

      }
      else
      {
          if (result_ob["error"].isString())
          {
              message = slack::message{};
              message->text = result_ob["error"].asString();
              if (result_ob["channel"].isString())
                  message->channel = slack::channel_id{ result_ob["channel"].asString() };
              if (result_ob["ts"].isString()) 
                  message->ts = slack::ts{ result_ob["ts"].asString() };
          }
      }
    }
  }

}
