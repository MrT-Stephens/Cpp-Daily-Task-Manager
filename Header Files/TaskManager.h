#pragma once

#include "../Header Files/Subject.h"
#include "../Header Files/Observer.h"
#include "../Header Files/Vector.h"
#include "../Header Files/Algorithm.h"

class TaskManager : public Subject {
private:
    mrt::Vector<Observer*> m_Observers;
    mrt::Vector<Task> m_Tasks;

public:
    void Attach(Observer* observer) override 
    {
        m_Observers.PushBack(observer);
    }

    void Detach(Observer* observer) override 
    {
        m_Observers.Erase(mrt::Find(m_Observers.begin(), m_Observers.end(), observer));
    }

    void Notify() override 
    {
        for (Observer* observer : m_Observers) 
        {
            observer->Update(this->m_Tasks);
        }
    }

    void AddTask(const Task& task) 
	{
		m_Tasks.PushBack(task);
		Notify();
	}

    void RemoveTask(const std::string& task_name) 
	{
        m_Tasks.Erase(mrt::FindIf(m_Tasks.begin(), m_Tasks.end(), [task_name](const Task& task)->bool
            {
                return task.title == task_name;
            }));

		Notify();
	}

    void CompleteTask(const std::string& task_name)
    {
        auto task = mrt::FindIf(m_Tasks.begin(), m_Tasks.end(), [task_name](const Task& task)->bool
			{
				return task.title == task_name;
			});

        if (task != m_Tasks.end())
		{
			task->is_done = true;
			Notify();
		}
    }
};