#include "../Header Files/View.h"

View::View(std::shared_ptr<cycfi::elements::window> main_window, const cycfi::elements::color& background_color)
	: cycfi::elements::view(*main_window.get()), m_BackgroundColor(background_color)
{

}

void View::InitView()
{
	this->content(
		cycfi::elements::pane(
			cycfi::elements::htile(
				cycfi::elements::align_left(
					cycfi::elements::label("Hello!")
				),
				cycfi::elements::align_right(
					cycfi::elements::button(
						"Add Task"
					)
				)
			),
			cycfi::elements::vtile(
				cycfi::elements::align_top(
					cycfi::elements::label("Hello!")
				)
			), false
		),
		cycfi::elements::box(m_BackgroundColor)
	);
}

void View::Update(const mrt::Vector<Task>& tasks)
{

}