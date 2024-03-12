#pragma once

#include "../Header Files/Xml.h"
#include "../Header Files/NoCopy.h"
#include "../Header Files/Vector.h"
#include "../Header Files/Task.h"
#include "../Header Files/Time.h"

#include <filesystem>

/// <summary>
/// Storage class is responsible for reading and writing tasks to a file.
/// It uses the XML library to read and write tasks to a file.
/// </summary>
class Storage : private NoCopy
{
private:
	std::string m_CurrentDirectory;
public:
	/// <summary>
	/// Default constructor that sets the current directory to the current working directory.
	/// </summary>
	Storage() 
		: m_CurrentDirectory(std::filesystem::current_path().string())
	{
	}

	/// <summary>
	/// Writes the tasks to a file.
	/// Uses the XML library to write the tasks to a file.
	/// </summary>
	/// <param name="file_name"> The name of the file to write to. </param>
	/// <param name="tasks"> The tasks to write to the file. </param>
	/// <returns> True if the tasks were written to the file, false otherwise. </returns>
	virtual bool Write(const std::string& file_name, const mrt::Vector<Task>& tasks)
	{
		mrt::XML_Node root("daily-tasks");

		root.AddAttribute("date", mrt::time::FormatTime(mrt::time::Read(), "%d-%m-%Y"));

		for (Task& task : tasks)
		{
			mrt::XML_Node task_node("task");

			task_node.AddChild(mrt::XML_Node("name", task.title));
			task_node.AddChild(mrt::XML_Node("description", task.description));
			task_node.AddChild(mrt::XML_Node("start_time", task.start_time));
			task_node.AddChild(mrt::XML_Node("end_time", task.end_time));
			task_node.AddChild(mrt::XML_Node("completed", task.is_done ? "true" : "false"));

			root.AddChild(task_node);
		}

		mrt::XML_Document doc(root, "1.0");

		return (doc.WriteDocument(m_CurrentDirectory + "\\" + file_name + ".xml", doc) == mrt::XML_Document_FileError::SUCCESS) ? true : false;
	}

	/// <summary>
	/// Reads the tasks from a file.
	/// Uses the XML library to read the tasks from a file.
	/// </summary>
	/// <param name="file_name"> The name of the file to read from. </param>
	/// <param name="tasks"> The tasks to read from the file. </param>
	/// <returns> True if the tasks were read from the file, false otherwise. </returns>
	virtual bool Read(const std::string& file_name, mrt::Vector<Task>& tasks)
	{
		mrt::XML_Document doc;

		if (doc.ReadDocument(m_CurrentDirectory + "\\" + file_name + ".xml", doc) != mrt::XML_Document_FileError::SUCCESS)
			return false;

		mrt::XML_Node root = doc.GetRoot();

		for (mrt::XML_Node& task_node : root.GetAllChildren())
		{
			tasks.EmplaceBack(
				task_node.GetChild(0).GetValue(),
				task_node.GetChild(1).GetValue(),
				task_node.GetChild(2).GetValue(),
				task_node.GetChild(3).GetValue(),
				task_node.GetChild(4).GetValue() == "true" ? true : false
			);
		}

		return true;
	}
};