#pragma once
#include <string>
#include <vector>

struct UserInputData
{
	int recursion_depth;		//recursion_depth
	std::string input_url;		//input url
	std::string path_log_file;	//file for logs (not implemented)
};

struct struct_sorted_urls
{
	std::vector<std::string> http_url_vector;
	size_t last_size_http_url_vector = 0;
	std::vector<std::string> https_same_domen_url_vector;
	size_t last_size_https_same_domen_url_vector = 0;
	std::vector<std::string> https_other_domen_url_vector;
	size_t last_size_https_other_domen_url_vector = 0;
};
