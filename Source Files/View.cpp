#include "../Header Files/View.h"

View::View(std::shared_ptr<cycfi::elements::window> main_window, const cycfi::elements::color& background_color)
	: cycfi::elements::view(*main_window.get()), m_BackgroundColor(background_color)
{

}

void View::InitView()
{
	auto add_button = cycfi::elements::button("Add Task", 1.2f);

	add_button.on_click = [this](bool)
		{
			auto title_input = cycfi::elements::input_box();
			auto description_input = cycfi::elements::input_box();
			auto start_time_input = cycfi::elements::input_box();
			auto end_time_input = cycfi::elements::input_box();

			title_input.second->on_text = [this, title_ptr = title_input.second.get()](std::string_view str)
				{
					m_NewTaskTitle = str;
					title_ptr->value(cycfi::to_utf32(str));
				};

			description_input.second->on_text = [this, description_ptr = description_input.second.get()](std::string_view str)
				{
					m_NewTaskDescription = str;
					description_ptr->value(cycfi::to_utf32(str));
				};

			start_time_input.second->on_text = [this, start_time_ptr = start_time_input.second.get()](std::string_view str)
				{
					m_NewTaskStartTime = str;
					start_time_ptr->value(cycfi::to_utf32(str));
				};

			end_time_input.second->on_text = [this, end_time_ptr = end_time_input.second.get()](std::string_view str)
				{
					m_NewTaskEndTime = str;
					end_time_ptr->value(cycfi::to_utf32(str));
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
					cycfi::elements::label_with_font_size(
						cycfi::elements::label("Hello!"), 20.0f
					)
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
	auto&& cell_composer_func = [this, &tasks](uint64_t index)
		{
			auto check_box = cycfi::elements::check_box("");

			check_box.value(tasks[index].is_done);

			check_box.on_click = [this, title = tasks[index].title](bool checked)
				{
					OnCheckTaskClick(title, checked);
				};

			auto remove_button = cycfi::elements::button("Remove", 1.15f);

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
											cycfi::elements::label_with_font_size(
												cycfi::elements::label(tasks[index].title), 15.0f
											)
										),
										cycfi::elements::hspace(15),
										cycfi::elements::align_center_middle(
											cycfi::elements::htile(
												cycfi::elements::label_with_font_size(
													cycfi::elements::label(tasks[index].start_time), 15.0f
												),
												cycfi::elements::label_with_font_size(
													cycfi::elements::label(" to "), 15.0f
												),
												cycfi::elements::label_with_font_size(
													cycfi::elements::label(tasks[index].end_time), 15.0f
												)
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
													cycfi::elements::label_with_font_size(
														cycfi::elements::label("Description:  "), 15.0f
													),
													cycfi::elements::label_with_font_size(
														cycfi::elements::label(tasks[index].description), 15.0f
													)
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

	if (tasks.Empty())
	{
		m_TasksElements =
			cycfi::elements::share(
				cycfi::elements::label_with_font_size(
					cycfi::elements::label("No Tasks are added!"), 25.0f
				)
			);
	}
	else
	{
		m_TasksElements = cycfi::elements::share(
			cycfi::elements::selection_list(
				cycfi::elements::list(
					cycfi::elements::basic_cell_composer(
						tasks.Size(),
						cell_composer_func
					),
					false
				)
			)
		);
	}

	this->layout(m_TasksElements);
}