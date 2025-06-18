#include <project_defines.h>
#include "app/init.hpp"

int main(void)
{
	// Initialize the application
	df::Application app = df::Application();
	app.init();
	app.main_loop(); // blocking call

	// Return success code
	return EXIT_SUCCESS;
}
