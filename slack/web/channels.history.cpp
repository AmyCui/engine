#include "slack/web/channels.history.h"
#include "private.h"

namespace slack {namespace channels
{

    void history::initialize_()
    {
      // required paramters
      auto params = default_params({
        {"channel", channel_}
      });

      // optional parameters
      if(count_)
      {
        params.emplace("count", *count_);
      }
      if(latest_)
      {
        params.emplace("latest", *latest_);
      }
      if(oldest_)
      {
        params.emplace("oldest", *oldest_);
      }
      if(unreads_)
      {
        params.emplace("unreads", *unreads_);
      }

      // http get
      auto result_ob = slack_private::get(this, "channels.history", params);
      if (result_ob["messages"].isArray())
      {
          auto numOfMessages = result_ob["messages"].size();
          for (int i = 0; i < numOfMessages; i++)
          {
              slack::message ms = slack::message{};
              auto message = result_ob["messages"][i];
              //check if is sent from an app/bot
              if (message["bot_id"].isString())
              {
                  //get the attachment instead if its from a bot
                  if (message["attachments"].isArray())
                  {
                      int size = message["attachments"].size();
                      if (size > 0)
                      {
                          auto attach = message["attachments"][0];
                          // populate message text
                          if (attach["text"].isString())
                              ms.text = attach["text"].asString();
                          //otherwise use the fallback text. fallback is a required field.
                          else
                              ms.text = attach["fallback"].asString();
                          // populate user
                          if (attach["author_name"].isString())
                              ms.user = attach["author_name"].asString();
                          else if (message["username"].isString())
                              ms.user = message["username"].asString();
                          else if (message["user"].isString())
                              ms.user = message["user"].asString();
                          // populate timestamp
                          ms.ts = message["ts"].asString();
                      }
                  }
              }
              // if is a user message 
              else
              {
                  ms.user = message["user"].asString();
                  ms.text = message["text"].asString();
                  ms.ts = message["ts"].asString();
              }
              messages.push_back(ms);
          }
      }
    }

}} // namespace channels slack
