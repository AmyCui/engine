#pragma once


#include <slack/optional.hpp>
#include <slack/types.h>
#include <slack/set_option.h>
#include <slack/base/response.h>
#include <slack/event/message.h>
#include <string>
#include <vector>

namespace slack 
{
    namespace search
    {
        class messages : public slack::base::response
        {
        public:
            template<class TOKEN, class QUERY>
            messages(TOKEN&& token, QUERY&& query)
                :response{ std::forward<TOKEN>(token) }, query_{ std::forward<QUERY>(query) }
            {
                initialize_();
            }

            template<class TOKEN, class QUERY, typename ...Os>
            messages(TOKEN&& token, QUERY&& query, Os &&... os)
                : response{ std::forward<TOKEN>(token) }, query_{ std::forward<QUERY>(query) }
            {
                slack::set_option<messages>(*this, std::forward<Os>(os)...);
                initialize_();
            }

            // parameters
            struct parameter
            {
                SLACK_MAKE_STRING_LIKE(query);
                SLACK_MAKE_STRING_LIKE(count);
                SLACK_MAKE_STRING_LIKE(page);
                enum class sort
                {
                    score = 0,
                    timestamp
                };
                enum class sort_dir
                {
                    desc = 0,
                    asc
                };
            };

            //errors
            struct error : public slack::base::error
            {
                static const std::string NOT_AUTHED;
                static const std::string INVALID_AUTH;
                static const std::string NO_PERMISSION;
            };

            //response
            std::vector<slack::message> matches;

            //parameter setters
            void set_option(const parameter::query &query)
            {
                query_ = query;
            }
            void set_option(parameter::query &&query)
            {
                query_ = std::move(query);
            }

            void set_option(const parameter::count &count)
            {
                count_ = count;
            }
            void set_option(parameter::count &&count)
            {
                count_ = std::move(count);
            }

            void set_option(const parameter::page &page)
            {
                page_ = page;
            }
            void set_option(parameter::page &&page)
            {
                page_ = std::move(page);
            }

            void set_option(const parameter::sort &sort)
            {
                sort_ = sort;
            }
            void set_option(parameter::sort &&sort)
            {
                sort_ = std::move(sort);
            }

            void set_option(const parameter::sort_dir &sort_dir)
            {
                sort_dir_ = sort_dir;
            }
            void set_option(parameter::sort_dir &&sort_dir)
            {
                sort_dir_ = std::move(sort_dir);
            }

        private:
            void initialize_();

            std::string query_;
            std::experimental::optional<parameter::count> count_;
            std::experimental::optional<parameter::page> page_;
            std::experimental::optional<parameter::sort> sort_;
            std::experimental::optional<parameter::sort_dir> sort_dir_;
        };
    }
}