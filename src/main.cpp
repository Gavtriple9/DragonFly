#include <dragonfly/dragonfly.h>
#include <dragonfly/errors/system.h>

int main(void)
{
	// Initialize the application
	df::Dragonfly dragonfly = df::Dragonfly();
	dragonfly.init();
	dragonfly.main_loop(); // blocking call

	// Return success code
	return EXIT_SUCCESS;
}
