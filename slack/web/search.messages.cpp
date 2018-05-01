#include "slack/web/search.messages.h"
#include "private.h"

namespace slack
{
    namespace search
    {
        void messages::initialize_()
        {
            auto params = default_params({
                {"query", query_}
            });

            // optional parameters
            if (count_)
            {
                params.emplace("count", *count_);
            }
            if (page_)
            {
                params.emplace("page", *page_);
            }
            if (sort_)
            {
                std::string sort_val{ "score" };
                switch (*sort_)
                {
                case parameter::sort::score:
                    sort_val = "score";
                    break;
                case parameter::sort::timestamp:
                    sort_val = "timestamp";
                    break;
                }
                params.emplace("sort", sort_val);
            }
            if (sort_dir_)
            {
                std::string sort_dir_val{ "desc" };
                switch (*sort_dir_)
                {
                case parameter::sort_dir::desc:
                    sort_dir_val = "desc";
                    break;
                case parameter::sort_dir::asc:
                    sort_dir_val = "asc";
                    break;
                }
                params.emplace("sort_dir", sort_dir_val);
            }

            // http get
            auto result_ob = slack_private::get(this, "search.messages", params);
            // process response result
            // look for array of matching messages 
            if (result_ob["messages"]["matches"].isArray())
            {
                int numOfMatches = result_ob["messages"]["matches"].size();
                for (int i = 0; i < numOfMatches; i++)
                {
                    // create a new slack message object
                    // extract out the message text/username/timestamp from the matches
                    slack::message ms = slack::message{};
                    auto match_item = result_ob["messages"]["matches"][i];
                    if (match_item["text"].isString())
                    {
                        ms.text = match_item["text"].asString();
                        ms.user = match_item["username"].asString();
                        ms.ts = match_item["ts"].asString();
                    }
                    matches.push_back(ms);
                }// end of looping through match results
            }
        }// end of initialize_ method


    }//namespace search
}//namespace slack