#pragma once

#include <ctime>
#include <string>

namespace mrt 
{
	namespace time
	{
		/// <summary>
		/// Reads the current time and date.
		/// </summary>
		/// <returns> The current time and date. </returns>
		inline std::tm Read()
		{
			time_t now = std::time(0);
			std::tm current = *std::localtime(&now);
			return current;
		}

		/// <summary>
		/// A static function that formats a time and date according to a format code.
		/// </summary>
		/// <param name="time"> The time and date to format. </param>
		/// <param name="format_code"> The format code. </param>
		/// <returns> The formatted time and date. </returns>
		inline std::string FormatTime(const std::tm& time, const std::string& format_code)
		{
			char buffer[100];

			strftime(buffer, 80, format_code.c_str(), &time);

			return std::string(buffer);
		}
	}
};