#include "../Header Files/View.h"

View::View(std::shared_ptr<cycfi::elements::window> main_window, const cycfi::elements::color& background_color)
	: cycfi::elements::view(*main_window.get()), m_BackgroundColor(background_color), m_MainWindow(main_window)
{

}

void View::InitView()
{
	auto add_button = cycfi::elements::button("Add Task");

	add_button.on_click = [this](bool)
		{
			auto title_input = cycfi::elements::input_box();
			auto description_input = cycfi::elements::input_box();
			auto start_time_input = cycfi::elements::input_box();
			auto end_time_input = cycfi::elements::input_box();

			title_input.second->on_text = [this](std::string_view str)
				{
					m_NewTaskTitle = str;
				};

			description_input.second->on_text = [this](std::string_view str)
				{
					m_NewTaskDescription = str;
				};

			start_time_input.second->on_text = [this](std::string_view str)
				{
					m_NewTaskStartTime = str;
				};

			end_time_input.second->on_text = [this](std::string_view str)
				{
					m_NewTaskEndTime = str;
				};

			auto popup = cycfi::elements::dialog1(*this,
				cycfi::elements::htile(
					cycfi::elements::vtile(
						cycfi::elements::margin({ 10, 10, 20, 10 },
							cycfi::elements::vtile(
								cycfi::elements::align_left(cycfi::elements::label("Task Title")),
								cycfi::elements::hsize(200.0f,
									title_input.first
								)
							)
						),
						cycfi::elements::margin({ 10, 10, 20, 10 },
							cycfi::elements::vtile(
								cycfi::elements::align_left(cycfi::elements::label("Task Description")),
								cycfi::elements::hsize(200.0f,
									description_input.first
								)
							)
						),
						cycfi::elements::margin({ 10, 10, 20, 10 },
							cycfi::elements::vtile(
								cycfi::elements::align_left(cycfi::elements::label("Task Start Time")),
								cycfi::elements::hsize(200.0f,
									start_time_input.first
								)
							)
						),
						cycfi::elements::margin({ 10, 10, 20, 10 },
							cycfi::elements::vtile(
								cycfi::elements::align_left(cycfi::elements::label("Task End Time")),
								cycfi::elements::hsize(200.0f,
									end_time_input.first
								)
							)
						)
					)
				), [this]()
				{
					if (!m_NewTaskTitle.empty() && !m_NewTaskDescription.empty())
					{
						OnAddTaskClick({ m_NewTaskTitle, m_NewTaskDescription, m_NewTaskStartTime, m_NewTaskEndTime, false });
					}
				}, "Add Task"
			);

			cycfi::elements::open_popup(popup, *this);
		};

	this->content(
		cycfi::elements::pane(
			cycfi::elements::htile(
				cycfi::elements::align_left(
					cycfi::elements::label("Hello!")
				),
				cycfi::elements::align_right(
					cycfi::elements::hstretch(0.2f,
						add_button
					)
				)
			),
			cycfi::elements::vtile(
				cycfi::elements::margin({ 10, 10, 10, 10 },
					cycfi::elements::htile(
						cycfi::elements::align_center_top(
							cycfi::elements::vscroller(
								cycfi::elements::link(m_TasksElements)
							)
						)
					)
				)
			), false
		),
		cycfi::elements::box(m_BackgroundColor)
	);
}

void View::Update(const mrt::Vector<Task>& tasks)
{
	auto&& cell = [this, &tasks](uint64_t index)
		{
			auto check_box = cycfi::elements::check_box("");

			check_box.on_click = [this, title = tasks[index].title](bool checked)
				{
					OnCheckTaskClick(title, checked);
				};

			auto remove_button = cycfi::elements::button("Remove");

			remove_button.on_click = [this, title = tasks[index].title](bool)
				{
					OnRemoveTaskClick(title);
				};

			return cycfi::elements::share(
				cycfi::elements::margin({ 10, 5, 20, 5 },
					cycfi::elements::layer(
						cycfi::elements::margin({ 20, 5, 20, 5 },
							cycfi::elements::align_center(
								cycfi::elements::vtile(
									cycfi::elements::htile(
										cycfi::elements::align_middle(
											check_box
										),
										cycfi::elements::align_left_middle(
											cycfi::elements::label(tasks[index].title)
										),
										cycfi::elements::hspace(15),
										cycfi::elements::align_center_middle(
											cycfi::elements::htile(
												cycfi::elements::label(tasks[index].start_time),
												cycfi::elements::label(" to "),
												cycfi::elements::label(tasks[index].end_time)
											)
										),
										cycfi::elements::hspace(15),
										cycfi::elements::align_right_middle(
											cycfi::elements::hstretch(0.15f,
												remove_button
											)
										)
									),
									cycfi::elements::vspace(5),
									cycfi::elements::layer(
										cycfi::elements::align_center(
											cycfi::elements::margin({ 5, 5, 5, 5 },
												cycfi::elements::htile(
													cycfi::elements::label("Description:  "),
													cycfi::elements::label(tasks[index].description)
												)
											)
										),
										cycfi::elements::rbox(m_BackgroundColor.level(0.60f))
									)
								)
							)
						),
						cycfi::elements::rbox(m_BackgroundColor.level(0.75f))
					)
				)
			);
		};

	m_TasksElements = cycfi::elements::share(
		cycfi::elements::selection_list(
			cycfi::elements::list(
				cycfi::elements::basic_cell_composer(
					tasks.Size(),
					cell
				),
				false
			)
		)
	);

	this->layout(m_TasksElements);
}