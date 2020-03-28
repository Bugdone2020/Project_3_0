#include "UtilsCurl.h"
#include <iostream>
#include <curl/curl.h>

// function called by cURL to write received data to the buffer
static size_t curlWriteFunc(char* data, size_t size, size_t nmemb, std::string* buffer)
{
	size_t result = 0;

	if (buffer != nullptr && data != nullptr)
	{
		//places data from "data" in a memory block of size size * nmemb (apparently)
		buffer->append(data, size * nmemb);
		result = size * nmemb;
	}

	return result;//error
}

std::pair<bool, std::string> get_content_from_input_url(const std::string& test_string) //input url
{
	std::cout << "Function \"get_content_from_input_url\" in progress ..." << std::endl;
	std::string curlBuffer;

	char curlErrorBuffer[CURL_ERROR_SIZE]; // buffer for saving text errors
	CURL* curl = curl_easy_init(); // create a pointer to an object, easy initialization
	//std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> curl { curl_easy_init(), curl_easy_cleanup }; // add this !!!???
	if (curl) 
	{
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curlErrorBuffer);
		// set URL 
		curl_easy_setopt(curl, CURLOPT_URL, test_string.c_str());

		// function called by cURL to write received data
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteFunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);

		// fulfill the request
		CURLcode curlResult = curl_easy_perform(curl);

		// session end 
		curl_easy_cleanup(curl);

		if (curlResult == CURLE_OK)
		{
			return{ true, std::move(curlBuffer) };
		}
		else 
		{
			return{ false, std::move(curlBuffer) };
		}
	}
	std::cout << "ERROR : curl = false" << std::endl;
	return { false, std::move(curlBuffer) };
}