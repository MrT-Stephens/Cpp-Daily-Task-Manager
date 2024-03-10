#pragma once

#include <string>

struct Task
{
	std::string title{ "" };
	std::string description{ "" };
	std::string start_time{ "" };
	std::string end_time{ "" };
	bool is_done{ false };
};