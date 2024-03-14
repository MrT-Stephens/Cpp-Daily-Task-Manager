#include "../Header Files/View.h"

/// <summary>
/// Initializes a new instance of the <see cref="View"/> class.
/// </summary>
/// <param name="main_window"> The main window. </param>
/// <param name="background_color"> The background color. </param>
View::View(std::shared_ptr<cycfi::elements::window> main_window, const cycfi::elements::color& background_color)
	: cycfi::elements::view(*main_window.get()), m_BackgroundColor(background_color)
{

}

/// <summary>
/// Initializes all the UI elements for the view.
/// </summary>
void View::InitView()
{
	auto add_button = cycfi::elements::button("Add Task", 1.2f);

	// Add task button click event
	add_button.on_click = [this](bool)
		{
			auto GenerateHoursDropdown = [](auto func)
				{
					auto Hours = {
						"00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11",
						"12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23"
					};

					auto button = cycfi::elements::button_menu("Hour");

					cycfi::elements::vtile_composite hours_dropdown;

					for (auto&& hour : Hours)
					{
						auto item = cycfi::elements::share(
							cycfi::elements::menu_item(hour)
						);

						item->on_click = [hr = hour, func]()
							{
								func(hr);
							};

						hours_dropdown.push_back(item);
					}

					button.menu(cycfi::elements::layer(
						cycfi::elements::vsize(150,
							cycfi::elements::vscroller(
								hours_dropdown
							)
						),
						cycfi::elements::panel{}
					));

					return button;
				};

			auto GenerateMinutesDropdown = [](auto func)
				{
					auto Minutes = {
						"00", "01", "02", "03", "04", "05", "06", "07", "08", "09",
						"10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
						"20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
						"30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
						"40", "41", "42", "43", "44", "45", "46", "47", "48", "49",
						"50", "51", "52", "53", "54", "55", "56", "57", "58", "59"
					};

					auto button = cycfi::elements::button_menu("Minute");

					cycfi::elements::vtile_composite minutes_dropdown;

					for (auto&& minute : Minutes)
					{
						auto item = cycfi::elements::share(
							cycfi::elements::menu_item(minute)
						);

						item->on_click = [min = minute, func]()
							{
								func(min);
							};

						minutes_dropdown.push_back(item);
					}

					button.menu(cycfi::elements::layer(
						cycfi::elements::vsize(150,
							cycfi::elements::vscroller(
								minutes_dropdown
							)
						),
						cycfi::elements::panel{}
					));

					return button;
				};

			// New task input fields
			auto title_input = cycfi::elements::input_box();
			auto description_input = cycfi::elements::input_box();

			// Text changed events for input fields
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

			// The UI elements for the popup
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
									cycfi::elements::htile(
										GenerateHoursDropdown([this](std::string hour)
											{
												m_NewTaskStartTime.first = hour.c_str();
											}),
										cycfi::elements::margin({ 5, 0, 5, 0 },
											cycfi::elements::label(":")
										),
										GenerateMinutesDropdown([this](std::string minute)
											{
												m_NewTaskStartTime.second = minute.c_str();
											})
									)
								)
							)
						),
						cycfi::elements::margin({ 10, 10, 20, 10 },
							cycfi::elements::vtile(
								cycfi::elements::align_left(cycfi::elements::label("Task End Time")),
								cycfi::elements::hsize(200.0f,
									cycfi::elements::htile(
										GenerateHoursDropdown([this](std::string hour)
											{
												m_NewTaskEndTime.first = hour.c_str();
											}),
										cycfi::elements::margin({ 5, 0, 5, 0 },
											cycfi::elements::label(":")
										),
										GenerateMinutesDropdown([this](std::string minute)
											{
												m_NewTaskEndTime.second = minute.c_str();
											})
									)
								)
							)
						)
					)
				), [this]()
				{
					if (!m_NewTaskTitle.empty() && !m_NewTaskDescription.empty())
					{
						OnAddTaskClick({ 
							m_NewTaskTitle, 
							m_NewTaskDescription, 
							m_NewTaskStartTime.first + ":" + m_NewTaskStartTime.second,
							m_NewTaskEndTime.first + ":" + m_NewTaskEndTime.second,
							false 
							});
					}
				}, "Add Task"
			);

			// Open the popup
			cycfi::elements::open_popup(popup, *this);
		};

	// The main UI elements of the view.
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

/// <summary>
/// Updates the view with the given tasks.
/// This is inherited from the observer interface.
/// </summary>
/// <param name="tasks"> The tasks. </param>
void View::Update(const mrt::Vector<Task>& tasks)
{
	// The task display works by creating a cell composer function for each task.
	// This will then be called internally by the vlist class.
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

	// If there are no tasks, display a message.
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

	// Update the view with the new tasks.
	this->layout(m_TasksElements);
}