#pragma once

#include "../Header Files/Xml.h"
#include "../Header Files/NoCopy.h"
#include "../Header Files/Vector.h"
#include "../Header Files/Task.h"
#include "../Header Files/Time.h"

#include <filesystem>

class Storage : private NoCopy
{
private:
	std::string m_CurrentDirectory;
public:
	Storage() 
		: m_CurrentDirectory(std::filesystem::current_path().string())
	{
	}

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