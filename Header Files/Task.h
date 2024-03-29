#pragma once

#include <string>

/// <summary>
/// A struct that represents a task within the application.
/// </summary>
struct Task
{
	Task() = default;

	/// <summary>
	/// Constructor for the Task struct.
	/// </summary>
	/// <param name="title"> The title of the task. </param>
	/// <param name="description"> The description of the task. </param>
	/// <param name="start_time"> The start time of the task. </param>
	/// <param name="end_time"> The end time of the task. </param>
	/// <param name="is_done"> Whether the task is done or not. </param>
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