#include "UtilsRegularExpressions.h"
#include <iostream>
#include <regex>

enum url_parts
{
	Protocol = 1,
	Domain = 3
};

bool check_one_url_from_cmd(const std::string& input_url_f) //checks the correctness of the input url
{
	std::cmatch result;
	std::regex ex("(https)""(://)""([\\w\\-?=%.&;]+\\.\\w+)([\\w/\\-?=%.&;]+)");

	if (std::regex_match(input_url_f.c_str(), result, ex))
	{
		return true;
	}
	return false;
}

bool search_all_url_in_content(const std::string& buffer, std::vector<std::string>& url_vector)
{
	std::cout << "Function \"search_all_url_in_content\" in progress ..." << std::endl;

	try {
		std::regex re("(https|http)""(://)""([\\w\\-?=%.&;]+\\.\\w+)([\\w/\\-?=%.&;]+)");
		std::sregex_iterator next(buffer.begin(), buffer.end(), re);
		std::sregex_iterator end;
		url_vector.reserve(std::distance(next, end));
		while (next != end) {
			std::smatch match = *next++;
			url_vector.push_back(match.str());// put the current url into the vector  
		}
	}
	catch (std::regex_error& e) {
		// Syntax error in the regular expression
		return false;
	}

	return true;
}

bool sort_urls(const std::vector<std::string>& url_vector_f, struct_sorted_urls& sorted_urls, const std::string& input_user_url)
{
	std::cout << "Function \"sort_urls\" in progress ..." << std::endl;
	
	std::cmatch parts_of_current_url;
	std::cmatch parts_of_input_user_url;
	std::regex ex("(https|http)""(://)""([\\w\\-?=%.&;]+\\.\\w+)([\\w/\\-?=%.&;]+)");

	if (!std::regex_match(input_user_url.c_str(), parts_of_input_user_url, ex))
	{
		std::cout << " ERROR func regex_match() for parts_of_input_user_url" << std::endl;
		return false;
	}

	for (size_t pos = 0; pos < url_vector_f.size(); pos++)
	{
		if (std::regex_match(url_vector_f[pos].c_str(), parts_of_current_url, ex))
		{
			if (parts_of_current_url[Protocol] != parts_of_input_user_url[Protocol])
			{
				sorted_urls.http_url_vector.push_back(url_vector_f[pos]);
			}
			else
			{
				if (parts_of_current_url[Domain] == parts_of_input_user_url[Domain])
				{
					sorted_urls.https_same_domen_url_vector.push_back(url_vector_f[pos]);
				}
				else
				{
					sorted_urls.https_other_domen_url_vector.push_back(url_vector_f[pos]);
				}
			}
		}
	}
	return true;
}
