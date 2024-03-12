#pragma once

#include "../Header Files/Subject.h"
#include "../Header Files/Observer.h"
#include "../Header Files/Vector.h"
#include "../Header Files/Algorithm.h"
#include "../Header Files/StorageEncrypted.h"

/// <summary>
/// TaskManager class is a concrete subject class that inherits from the Subject interface.
/// It is responsible for managing the tasks and notifying the observers when a task is added, removed or completed.
/// </summary>
class TaskManager : public Subject, private NoCopy 
{
private:
    mrt::Vector<Observer*> m_Observers;
    mrt::Vector<Task> m_Tasks;
public:
    /// <summary>
    /// Initializes a new instance of the <see cref="TaskManager"/> class.
    /// Will read the tasks from the storage and initialize the tasks vector.
    /// </summary>
    TaskManager()
    {
        StorageEncrypted s(std::make_shared<Storage>());
        s.Read(std::to_string(typeid(this).hash_code()), m_Tasks);
    }

    /// <summary>
    /// Finalizes an instance of the <see cref="TaskManager"/> class.
    /// Will write the tasks to the storage, when the object is destroyed.
    /// </summary>
    ~TaskManager()
	{
        StorageEncrypted s(std::make_shared<Storage>());
		s.Write(std::to_string(typeid(this).hash_code()), m_Tasks);
	}

    /// <summary>
    /// Attaches the specified observer to the subject.
    /// </summary>
    /// <param name="observer"> The observer. </param>
    void Attach(Observer* observer) override 
    {
        m_Observers.PushBack(observer);
        Notify();
    }

    /// <summary>
    /// Detaches the specified observer from the subject.
    /// </summary>
    /// <param name="observer"> The observer. </param>
    void Detach(Observer* observer) override 
    {
        m_Observers.Erase(mrt::Find(m_Observers.begin(), m_Observers.end(), observer));
    }

    /// <summary>
    /// Notifies the observers when a task is added, removed or completed.
    /// </summary>
    void Notify() override 
    {
        for (Observer* observer : m_Observers) 
        {
            observer->Update(this->m_Tasks);
        }
    }

    /// <summary>
    /// Adds the task to the tasks vector and notifies the observers.
    /// </summary>
    /// <param name="task"> The task. </param>
    void AddTask(const Task& task) 
	{
		m_Tasks.PushBack(task);
		Notify();
	}

    /// <summary>
    /// Removes the task from the tasks vector and notifies the observers.
    /// </summary>
    /// <param name="task_name"> Name of the task. </param>
    void RemoveTask(const std::string& task_name) 
	{
        m_Tasks.Erase(mrt::FindIf(m_Tasks.begin(), m_Tasks.end(), [task_name](const Task& task)->bool
            {
                return task.title == task_name;
            }));

		Notify();
	}

    /// <summary>
    /// Completes the task and notifies the observers.
    /// </summary>
    /// <param name="task_name"> Name of the task. </param>
    /// <param name="completed"> if set to <c>true</c> the task is completed. </param>
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