#include "app/init.hpp"
#include <project_defines.h>

int main(void)
{
	// Initialize the application
	df::Application app = df::Application();
	app.init();
	app.main_loop(); // blocking call

	// Return success code
	return EXIT_SUCCESS;
}