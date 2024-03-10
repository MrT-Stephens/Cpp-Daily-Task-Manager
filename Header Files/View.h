#include <elements.hpp>

#include "../Header Files/NoCopy.h"
#include "../Header Files/Observer.h"

class View : public cycfi::elements::view, private NoCopy, public Observer
{
private:
	cycfi::elements::color m_BackgroundColor;
public:
	View(std::shared_ptr<cycfi::elements::window> main_window, const cycfi::elements::color& background_color);

	void InitView();

	void Update(const mrt::Vector<Task>& tasks) override;
};