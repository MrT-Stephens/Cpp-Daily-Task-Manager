#pragma once

#include <string>

struct Task
{
	Task() = default;
	Task(const std::string& title, const std::string& description, const std::string& start_time, const std::string& end_time, bool is_done)
		: title{ title }, description{ description }, start_time{ start_time }, end_time{ end_time }, is_done{ is_done }
	{
	}

	std::string title{ "" };
	std::string description{ "" };
	std::string start_time{ "" };
	std::string end_time{ "" };
	bool is_done{ false };
};