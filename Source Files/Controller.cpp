#include "../Header Files/Controller.h"

Controller::Controller(int argc, char* argv[], std::string name, std::string id)
	: cycfi::elements::app(argc, argv, name, id)
{
	m_Window = std::make_unique<cycfi::elements::window>();
	m_TaskManager = std::make_unique<TaskManager>();

	m_CurrentView = std::make_unique<View>(m_Window, cycfi::artist::rgba(35, 35, 37, 255));

	m_Window->on_close = [this] 
		{ 
			OnClose(); 
		};
}

void Controller::Init()
{
	m_TaskManager->Attach(m_CurrentView.get());

	m_CurrentView->OnAddTaskClick = [this](const Task& task) 
		{
			m_TaskManager->AddTask(task);
		};

	m_CurrentView->OnRemoveTaskClick = [this](const std::string& title)
		{
			m_TaskManager->RemoveTask(title);
		};

	m_CurrentView->OnCheckTaskClick = [this](const std::string& title, bool checked)
		{
			m_TaskManager->CompleteTask(title, checked);
		};

	m_CurrentView->InitView();

	this->run();
}

void Controller::OnClose()
{
	m_TaskManager->Detach(m_CurrentView.get());

	this->stop();
}