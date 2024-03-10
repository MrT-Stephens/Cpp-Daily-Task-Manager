#include <elements.hpp>

#include "../Header Files/NoCopy.h"
#include "../Header Files/Observer.h"

class View : public cycfi::elements::view, private NoCopy, public Observer
{
public:
	using add_task_click_func = std::function<void(const Task&)>;
	using remove_task_click_func = std::function<void(const std::string&)>;
	using check_task_click_func = std::function<void(const std::string&, bool)>;

	add_task_click_func OnAddTaskClick;
	remove_task_click_func OnRemoveTaskClick;
	check_task_click_func OnCheckTaskClick;

private:
    std::shared_ptr<cycfi::elements::window> m_MainWindow;
	cycfi::elements::color m_BackgroundColor;
	cycfi::elements::indirect<cycfi::elements::shared_element<cycfi::elements::element>> m_TasksElements{ cycfi::elements::share(cycfi::elements::label("No Tasks Added.")) };

	std::string m_NewTaskTitle;
	std::string m_NewTaskDescription;
	std::string m_NewTaskStartTime;
	std::string m_NewTaskEndTime;
public:
	View(std::shared_ptr<cycfi::elements::window> main_window, const cycfi::elements::color& background_color);

	void InitView();

	void Update(const mrt::Vector<Task>& tasks) override;
};