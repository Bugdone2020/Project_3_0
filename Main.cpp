#include "UtilsCurl.h"
#include "UtilsParsingInputData.h"
#include "UtilsRegularExpressions.h"
#include "UtilsJSON.h"
#include "UtilsFunc.h"
#include <iostream>

bool recursion_func(std::vector<std::pair<std::string, size_t>>& url_data, 
					const size_t& deep_recursion, 
					size_t& counter, 
					struct_sorted_urls& sorted_urls)
{
	std::cout << std::endl << "Function \"recursion_func\" in progress ..." << std::endl;
	std::cout << "Current recursion counter : " << counter << std::endl 
			  << "Current url : " << url_data[counter].first << std::endl
			  << "Deep of current url : " << url_data[counter].second << std::endl;
	
	//get content from input url
	auto content = get_content_from_input_url(url_data[counter].first);
	if (!content.first)
	{
		std::cout << std::endl << "ERROR get_content_from_input_url" << std::endl;
		return false;
	}
	//get urls from content
	std::vector<std::string> url_vector; //vector of url
	if (!search_all_url_in_content(content.second, url_vector))
	{
		std::cout << std::endl << "ERROR search_all_url_in_content" << std::endl;
		return false;
	}
	
	//sort urls
	if (!sort_urls(url_vector, sorted_urls, url_data[0].first))
	{
		std::cout << std::endl << "ERROR sort_urls" << std::endl;
	}
	
	//form url_data - need for recursion
	form_url_data(url_data, deep_recursion, counter, sorted_urls);
	
	//recursion condition
	if ((url_data[counter + 1].second) < deep_recursion)
	{
		recursion_func(url_data, deep_recursion, ++counter, sorted_urls);
	}

	return true;
}

int main(int argc, char* argv[])
{
	std::cout << "Main program" << std::endl;

	//input processing
	UserInputData InputData;
	if (!input_processing(argc, argv, InputData))
		return -1;

	//form data for recursion function
	std::vector<std::pair<std::string, size_t>> url_data{ std::make_pair(InputData.input_url, size_t{0}) }; //vector of pair. Pair:(url, url_deep) - need for recursion function
	size_t counter = 0;//counter - need for recursion function
	struct_sorted_urls sorted_urls; // struct sorted urls
	
	//recurtion function
	if (!recursion_func(url_data, InputData.recursion_depth, counter, sorted_urls))
		return -2;

	// from JSON 
	serializeToJson(sorted_urls);

	//print vector
	print_url_vector(sorted_urls.http_url_vector);
	print_url_vector(sorted_urls.https_other_domen_url_vector);
	print_url_vector(sorted_urls.https_same_domen_url_vector);

	return 0;
}



