#include "../Header Files/Controller.h"


int main(int argc, char* argv[])
{
	Controller ctrl(argc, argv, "Daily Task Manager", "com.MrT-Stephens.Daily-Task-Manager");

	ctrl.Init();

	return 0;
}
