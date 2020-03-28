#pragma once
#include "UtilsStruct.h"

bool check_one_url_from_cmd(const std::string& input_url_f);

bool search_all_url_in_content(const std::string& buffer, std::vector<std::string>& url_vector);

bool sort_urls(const std::vector<std::string>& url_vector_f, struct_sorted_urls& sorted_urls, const std::string& input_user_url);