#include "UtilsParsingInputData.h"
#include "UtilsRegularExpressions.h"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

namespace 
{
	const char* cDepth{ "depth" };
	const char* cHelp{ "help" };
	const char* cUrl{ "url" };
	const char* cLogPath{ "logpath" };
}

enum Bitset 
{
	NO_ARGUMENT = 0UL,
	RECURSION_DEEP= 1UL << 0,	// set first bit ...000001
	URL = 1UL << 1,				// set second bit ...000010
	LOG_PATH = 1UL << 2,		// set third bit ......000100
	HELP = 1UL << 3				// set fourth bit ......001000
};

static void set_input_arduments_status(const po::options_description& desc, 
									   const po::variables_map& vm, 
									   std::string& input_url, 
									   Bitset& input_arduments_status)
{
	if (vm.count(cHelp))
	{
		std::cout << desc << std::endl;
		input_arduments_status = static_cast<Bitset>(input_arduments_status | Bitset::HELP);
	}

	if (vm.count(cDepth))
	{
		if ((vm[cDepth].as<int>()) > 0)
		{
			std::cout << "Recursion depth: " << vm[cDepth].as<int>() << std::endl;
			input_arduments_status = static_cast<Bitset>(input_arduments_status | Bitset::RECURSION_DEEP);
		}
		else
		{
			std::cout << "ERROR : recursion depth is not corect " << std::endl;
		}
	}

	if (vm.count(cUrl))
	{
		if (check_one_url_from_cmd(input_url))
		{
			std::cout << "Input url: " << vm[cUrl].as<std::string>() << std::endl;
			input_arduments_status = static_cast<Bitset>(input_arduments_status | Bitset::URL);
		}
		else
		{
			std::cout << "ERROR : input url is not corect " << std::endl;
		}
	}

	if (vm.count(cLogPath))
	{
		std::cout << "path to log file: " << vm[cLogPath].as<std::string>() << std::endl;
		input_arduments_status = static_cast<Bitset>(input_arduments_status | Bitset::LOG_PATH);
	}
}

static bool CheckSetBit(Bitset value, Bitset bit)
{
	switch (value & bit)
	{
	case NO_ARGUMENT:
		return false;
	case RECURSION_DEEP:
		std::cout << "Set RECURSION_DEEP\n";
		return true;
	case URL:
		std::cout << "Set URL\n";
		return true;
	case LOG_PATH:
		std::cout << "Set LOG_PATH\n";
		return true;
	case HELP:
		std::cout << "Set HELP\n";
		return true;
	default:
		std::cout << "ERROR : Default \n";
		return false;
	}
}

static bool parse_param(int argc, char* argv[], UserInputData& InputData, Bitset& input_arduments_status)
{
	po::options_description desc("Short description");
	desc.add_options()
		("help,h", "help me")
		("depth,d", po::value<int>(&InputData.recursion_depth)->default_value(1), "recursion depth")
		("url", po::value<std::string>(&InputData.input_url), "input url")
		//("url", po::value<std::string>(&InputData.input_url)->default_value("https://curl.haxx.se/libcurl/c/anyauthput.html"), "input url") 
		("logpath,l", po::value<std::string>(&InputData.path_log_file), "path to log file");

	po::positional_options_description p;
	po::variables_map vm;
	
	try
	{
		po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
		po::notify(vm);
		set_input_arduments_status(desc, vm, InputData.input_url, input_arduments_status);
	}

	catch (po::error& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << desc << std::endl;
		return false;
	}
	return true;
}

bool input_processing(int argc, char* argv[], UserInputData& InputData)
{
	std::cout << std::endl << "Function \"input_processing\" in progress ..." << std::endl;
	Bitset input_arduments_status = NO_ARGUMENT;

	if (!parse_param(argc, argv, InputData, input_arduments_status)) 
	{
		std::cout << "Can't parse user input data\n";
		return false;
	}

	if (CheckSetBit(input_arduments_status, Bitset::HELP))
		return false;

	if (!CheckSetBit(input_arduments_status,Bitset::RECURSION_DEEP))
	{
		std::cout << std::endl << "ERROR input_processing" << std::endl
						       << "invalid recursion depth" << std::endl;
		return false;
	}

	if (!CheckSetBit(input_arduments_status,Bitset::URL))
	{
		std::cout << std::endl << "ERROR input_processing" << std::endl
							   << "invalid input url" << std::endl;
		return false;
	}

	return true;
}