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
     slack::web_client web_client{token_str};
	 auto response = web_client.chat.postMessage(channel_str, message_str);
     return (response.message->text).c_str();
  }

  const char* functions::PostImageMessage(const unsigned char* token, const unsigned char* channel, const unsigned char* message, const unsigned char* image_url)
  {
	  const char* token_str = reinterpret_cast<const char *>(token);
	  const char* image_url_str = reinterpret_cast<const char *>(image_url);
	  const char* message_str = reinterpret_cast<const char *>(message);
	  const char* channel_str = reinterpret_cast<const char *>(channel);

      std::string image_url_text = std::string(image_url_str);
      std::string fallback_text = std::string("This is fallback text");

	
	  const slack::attachment::parameter::fallback fb {message_str};
	  const slack::attachment::parameter::image_url iu { image_url_str };
	  const slack::attachment attach{ fb, iu };

      const slack::chat::postMessage::parameter::attachments attachs{ attach };


      slack::web_client web_client{token_str};

	auto response = web_client.chat.postMessage(channel_str, message_str, attachs);
	return (response.message->text).c_str();
  }
}
