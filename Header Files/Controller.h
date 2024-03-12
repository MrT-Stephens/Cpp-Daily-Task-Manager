#include <elements.hpp>

#include "../Header Files/NoCopy.h"
#include "../Header Files/View.h"
#include "../Header Files/TaskManager.h"

/// <summary>
/// The Controller class is the main class for the application. 
/// It is responsible for managing the application's views and tasks.
/// </summary>
class Controller : public cycfi::elements::app, private NoCopy
{
private:
	// Modal Items
	std::unique_ptr<TaskManager> m_TaskManager;

	// Window Items
	std::shared_ptr<cycfi::elements::window> m_Window;

	// View Items
	std::unique_ptr<View> m_CurrentView;
public:
	Controller(int argc, char* argv[], std::string name, std::string id);

	void Init();

	void OnClose();
};