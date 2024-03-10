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
	m_CurrentView->InitView();

	this->run();
}

void Controller::OnClose()
{
	this->stop();
}