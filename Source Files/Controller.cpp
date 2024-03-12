#include "../Header Files/Controller.h"

/// <summary>
/// Initializes a new instance of the <see cref="Controller"/> class.
/// Will initialize all the necessary components for the application to run.
/// </summary>
/// <param name="argc"> The argc. </param>
/// <param name="argv"> The argv. </param>
/// <param name="name"> The name. </param>
/// <param name="id"> The identifier. </param>
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

/// <summary>
/// Initializes everything for the application to run.
/// Will attach the view to the task manager and initialize the view.
/// Will also set the event handlers for the view.
/// </summary>
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

/// <summary>
/// Called when the window is closed.
/// Will detach the view from the task manager and stop the application.
/// Will also call the base class stop method.
/// </summary>
void Controller::OnClose()
{
	m_TaskManager->Detach(m_CurrentView.get());

	this->stop();
}