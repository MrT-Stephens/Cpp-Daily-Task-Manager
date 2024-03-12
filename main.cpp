#include "../Header Files/Controller.h"

/// <summary>
/// The starting point of the application
/// Will initialize the controller and start the application
/// </summary>
/// <param name="argc"> The number of arguments. </param>
/// <param name="argv"> The arguments. </param>
/// <returns> The exit code. </returns>
int main(int argc, char* argv[])
{
	Controller ctrl(argc, argv, "Daily Task Manager", "com.MrT-Stephens.Daily-Task-Manager");

	ctrl.Init();

	return 0;
}
