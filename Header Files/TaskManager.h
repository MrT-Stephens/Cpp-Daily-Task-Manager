#pragma once

#include "../Header Files/Subject.h"
#include "../Header Files/Observer.h"
#include "../Header Files/Vector.h"
#include "../Header Files/Algorithm.h"
#include "../Header Files/StorageEncrypted.h"

class TaskManager : public Subject, private NoCopy 
{
private:
    mrt::Vector<Observer*> m_Observers;
    mrt::Vector<Task> m_Tasks;
public:
    TaskManager()
    {
        StorageEncrypted s(std::make_shared<Storage>());
        s.Read(std::to_string(typeid(this).hash_code()), m_Tasks);
    }

    ~TaskManager()
	{
        StorageEncrypted s(std::make_shared<Storage>());
		s.Write(std::to_string(typeid(this).hash_code()), m_Tasks);
	}

    void Attach(Observer* observer) override 
    {
        m_Observers.PushBack(observer);
        Notify();
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

    void CompleteTask(const std::string& task_name, bool completed)
    {
        auto task = mrt::FindIf(m_Tasks.begin(), m_Tasks.end(), [task_name](const Task& task)->bool
			{
				return task.title == task_name;
			});

        if (task != m_Tasks.end())
		{
			task->is_done = completed;
			Notify();
		}
    }
};