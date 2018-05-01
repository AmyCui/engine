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
     if (!response.message->text.empty())
     {
         std::string message_str = (response.message->text);
         const std::string::size_type size = message_str.size();
         char *buffer = new char[size + 1];   //we need extra char for NUL
         memcpy(buffer, message_str.c_str(), size + 1);
         return buffer;
     }
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
    if (!response.message->text.empty())
    {
        std::string message_str = (response.message->text);
        const std::string::size_type size = message_str.size();
        char *buffer = new char[size + 1];   //we need extra char for NUL
        memcpy(buffer, message_str.c_str(), size + 1);
        return buffer;
    }
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
      if (!response.message->text.empty())
      {
          std::string message_str = (response.message->text);
          const std::string::size_type size = message_str.size();
          char *buffer = new char[size + 1];   //we need extra char for NUL
          memcpy(buffer, message_str.c_str(), size + 1);
          return buffer;
      }
      else
          return "";
  }

  functions::slack_message functions::GetChannelMessages(const unsigned char* token, const unsigned char* channel, const unsigned char* oldestTs, const unsigned char* msCount)
  {
      const char* token_str = reinterpret_cast<const char *>(token);
      const char* channel_str = reinterpret_cast<const char *>(channel);
      const char* oldestTs_str = reinterpret_cast<const char *>(oldestTs);
      const char* msCount_str = reinterpret_cast<const char *>(msCount);

      const slack::channels::history::parameter::count count_para(msCount_str);
      const slack::channels::history::parameter::oldest oldest_para(oldestTs_str);

      slack::web_client web_client{ token_str };
      auto response = web_client.channels.history(channel_str, count_para, oldest_para);

      functions::slack_message result = functions::slack_message{};
      //TODO: only support returning one message for now
      if (response.messages.size() > 0)
      {
              auto ms = response.messages[0];

              std::string usr_str = (ms.user);
              const std::string::size_type usr_size = usr_str.size();
              char *usr_buffer = new char[usr_size + 1];   //we need extra char for NUL
              memcpy(usr_buffer, usr_str.c_str(), usr_size + 1);
              result.user = usr_buffer;

              std::string text_str = (ms.text);
              const std::string::size_type text_size = text_str.size();
              char *text_buffer = new char[text_size + 1];   //we need extra char for NUL
              memcpy(text_buffer, text_str.c_str(), text_size + 1);
              result.text = text_buffer;

              std::string ts_str = (ms.ts);
              const std::string::size_type ts_size = ts_str.size();
              char *ts_buffer = new char[ts_size + 1];   //we need extra char for NUL
              memcpy(ts_buffer, ts_str.c_str(), ts_size + 1);
              result.ts = ts_buffer;

      }

      return result;

  }


  functions::slack_message* functions::SearchMesages(const unsigned char* token, const unsigned char* query, const unsigned char* count, const unsigned char* page)
  {
      const char* token_str = reinterpret_cast<const char *>(token);
      const char* query_str = reinterpret_cast<const char *>(query);
      const char* count_str = reinterpret_cast<const char *>(count);
      const char* page_str = reinterpret_cast<const char *>(page);

      const slack::search::messages::parameter::count count_para(count_str);
      const slack::search::messages::parameter::page page_para(page_str);
      
      slack::web_client web_client{ token_str };
      auto response = web_client.search.messages(query_str, count_para, page_para);

      slack_message* resultMessage = nullptr;
      slack_message* iter = nullptr;
      if (response.matches.size() > 0)
      {
          for (int i = 0; i < response.matches.size(); i++)
          {
              auto ms = response.matches[i];
              functions::slack_message *result = new functions::slack_message{};

              std::string usr_str = (ms.user);
              const std::string::size_type usr_size = usr_str.size();
              char *usr_buffer = new char[usr_size + 1];   //we need extra char for NUL
              memcpy(usr_buffer, usr_str.c_str(), usr_size + 1);
              result->user = usr_buffer;

              std::string text_str = (ms.text);
              const std::string::size_type text_size = text_str.size();
              char *text_buffer = new char[text_size + 1];   //we need extra char for NUL
              memcpy(text_buffer, text_str.c_str(), text_size + 1);
              result->text = text_buffer;

              std::string ts_str = (ms.ts);
              const std::string::size_type ts_size = ts_str.size();
              char *ts_buffer = new char[ts_size + 1];   //we need extra char for NUL
              memcpy(ts_buffer, ts_str.c_str(), ts_size + 1);
              result->ts = ts_buffer;

              result->Next = nullptr;

              if (resultMessage == nullptr)
              {
                  resultMessage = new functions::slack_message{};
                  resultMessage = result;
                  iter = new functions::slack_message{};
                  iter = resultMessage;
              }
              else
              {
                  iter->Next = new functions::slack_message{};
                  iter->Next = result;
                  iter = iter->Next;
              }
          }
      }
      return resultMessage;
  }

}
