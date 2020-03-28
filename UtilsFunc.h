#pragma once
#include "UtilsStruct.h"

void print_url_vector(const std::vector<std::string>& input_vector);

void form_url_data(std::vector<std::pair<std::string, size_t>>& url_data, const size_t& deep_recursion, size_t& counter, struct_sorted_urls& sorted_urls);
