#include "UtilsJSON.h"
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/rapidjson.h"

static void serializeVectorToJson(std::ostream& os, const std::vector<std::string>& url_vector, std::string mark) {
	rapidjson::Document jsonDoc;
	jsonDoc.SetObject();
	rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();

	if (mark == "http")
		for (auto& obj : url_vector) {
			rapidjson::Value objValue;
		
			objValue.SetString(obj.c_str(), allocator);
		
			jsonDoc.AddMember("http", objValue, allocator);
		}

	if (mark == "https_same_domen")
		for (auto& obj : url_vector) {
			rapidjson::Value objValue;

			objValue.SetString(obj.c_str(), allocator);

			jsonDoc.AddMember("https_same_domen", objValue, allocator);
		}

	if (mark == "https_other_domen")
		for (auto& obj : url_vector) {
			rapidjson::Value objValue;

			objValue.SetString(obj.c_str(), allocator);

			jsonDoc.AddMember("https_other_domen", objValue, allocator);
		}

	rapidjson::StringBuffer strbuf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
	jsonDoc.Accept(writer);

	os << strbuf.GetString();
}

void serializeToJson(const struct_sorted_urls& sorted_urls)
{
	std::cout << "Function \"serializeToJson\" in progress ..." << std::endl;

	std::ofstream file;
	std::string filePath("MyDoc.json");
	file.open(filePath, std::ios_base::out | std::ios_base::binary);
	if (!file.is_open()) {
		std::cout << "ERR: can't open '" << filePath << "'." << std::endl;
	}

	serializeVectorToJson(file, sorted_urls.http_url_vector, "http");
	serializeVectorToJson(file, sorted_urls.https_same_domen_url_vector, "https_same_domen");
	serializeVectorToJson(file, sorted_urls.https_other_domen_url_vector, "https_other_domen");
}
