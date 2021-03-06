// Export Header Created by Amy Cui for:
//      engine Copyright © 2016 D.E. Goodman-Wilson.

#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include <string>
#include <vector>

namespace slack
{
  class functions
  {
  public:
    static ENGINE_API const char* PostMessage(const unsigned char* token, const unsigned char* channel, const unsigned char* message);

    static ENGINE_API const char* PostImageMessage(const unsigned char* token, const unsigned char* channel,const unsigned char* message, const unsigned char* image_url);

    static ENGINE_API const char* functions::UploadFile(const unsigned char* token, const unsigned char* channel, const unsigned char* comment, const unsigned char* filepath);

    struct slack_message {
        char* user;
        char* text;
        char* ts;
        slack_message* Next;
    };

    ENGINE_API slack_message functions::GetChannelMessages(const unsigned char* token, const unsigned char* channel, const unsigned char* oldestTs, const unsigned char* msCount);
    
    ENGINE_API slack_message* functions::SearchMesages(const unsigned char* token, const unsigned char* query, const unsigned char* count, const unsigned char* page);

    ENGINE_API const char* GetUserDisplayName(const unsigned char* token, const unsigned char* userid);
  };

}
