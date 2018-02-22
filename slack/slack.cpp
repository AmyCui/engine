#include <slack/slack.h>

#include <string>

#include <slack/web_client.h>
#include <slack/config.h>
#include <slack/types.h>
#include <slack/rtm_event_client.h>
#include <slack/http_event_client.h>

namespace slack
{
  const char* functions::PostMessage(const unsigned char* token, const unsigned char* channel, const unsigned char* message)
  {
     const char* token_str = reinterpret_cast<const char *>(token);
     const char* message_str = reinterpret_cast<const char *>(message);
     const char* channel_str = reinterpret_cast<const char *>(channel);
     // slack call
     slack::web_client web_client{token_str};
	 auto response = web_client.chat.postMessage(channel_str, message_str);
     // response message
     if (!response.message != NULL && !response.message->text.empty())
         return (response.message->text).c_str();
     else
         return "";
  }

  const char* functions::PostImageMessage(const unsigned char* token, const unsigned char* channel, const unsigned char* message, const unsigned char* image_url)
  {
    const char* token_str = reinterpret_cast<const char *>(token);
    const char* image_url_str = reinterpret_cast<const char *>(image_url);
    const char* message_str = reinterpret_cast<const char *>(message);
    const char* channel_str = reinterpret_cast<const char *>(channel);
    //create attachment
    const slack::attachment::parameter::fallback fb {message_str};
    const slack::attachment::parameter::image_url iu { image_url_str };
    const slack::attachment attach{ fb, iu };
    const slack::chat::postMessage::parameter::attachments attachs{ attach };
    //slack call
    slack::web_client web_client{token_str};
    auto response = web_client.chat.postMessage(channel_str, message_str, attachs);
    //response message
    if (!response.message != NULL && !response.message->text.empty())
        return (response.message->text).c_str();
    else
        return "";
  }

  const char* functions::UploadFile(const unsigned char* token, const unsigned char* channel, const unsigned char* comment, const unsigned char* filepath)
  {
      const char* token_str = reinterpret_cast<const char *>(token);
      const char* comment_str = reinterpret_cast<const char *>(comment);
      const char* filepath_str = reinterpret_cast<const char *>(filepath);
      const char* channel_str = reinterpret_cast<const char *>(channel);

      const slack::files::upload::parameter::initial_comment comment_para(comment_str);
      //slack call
      slack::web_client web_client{ token_str };
      auto response = web_client.files.upload(channel_str, filepath_str, comment_para);
      //response messsage
      if (!response.message != NULL && !response.message->text.empty())
          return (response.message->text).c_str();
      else
          return "";
  }
}
