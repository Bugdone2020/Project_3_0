#include "UtilsFunc.h"
#include <iostream>
void print_url_vector(const std::vector<std::string>& input_vector)
{
	for (auto current_item : input_vector)
		std::cout << current_item << std::endl;
}

void form_url_data(std::vector<std::pair<std::string, size_t>>& url_data, const size_t& deep_recursion, size_t& counter, struct_sorted_urls& sorted_urls)
{
	std::cout << "Function \"form_url_data\" in progress ..." << std::endl;

	for (size_t pos_https_same_domen_url_vector = sorted_urls.last_size_https_same_domen_url_vector; pos_https_same_domen_url_vector < sorted_urls.https_same_domen_url_vector.size(); pos_https_same_domen_url_vector++)
	{
		bool same_url = false;
		for (size_t pos_url_data_first = 0; pos_url_data_first < url_data.size(); pos_url_data_first++)
		{
			if (sorted_urls.https_same_domen_url_vector[pos_https_same_domen_url_vector] == url_data[pos_url_data_first].first)
				same_url = true;
		}
		if (!same_url)
			url_data.push_back(std::make_pair(sorted_urls.https_same_domen_url_vector[pos_https_same_domen_url_vector], url_data[counter].second + 1));
	}

	sorted_urls.last_size_https_same_domen_url_vector = sorted_urls.https_same_domen_url_vector.size();

	for (size_t pos_https_other_domen_url_vector = sorted_urls.last_size_https_other_domen_url_vector; pos_https_other_domen_url_vector < sorted_urls.https_other_domen_url_vector.size(); pos_https_other_domen_url_vector++)
	{
		bool same_url = false;
		for (size_t pos_url_data_first = 0; pos_url_data_first < url_data.size(); pos_url_data_first++)
		{
			if (sorted_urls.https_other_domen_url_vector[pos_https_other_domen_url_vector] == url_data[pos_url_data_first].first)
				same_url = true;
		}
		if (!same_url)
			url_data.push_back(std::make_pair(sorted_urls.https_other_domen_url_vector[pos_https_other_domen_url_vector], url_data[counter].second + 1));
	}

	sorted_urls.last_size_https_other_domen_url_vector = sorted_urls.https_other_domen_url_vector.size();
}
