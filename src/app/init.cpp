#include <dragonfly/config.h>
#include <dragonfly/version.h>

#include "init.hpp"

df::State df::Application::state;

// ------------------------------ Public methods ----------------------------- //

void df::Application::init()
{
    setup_logging();
    setup_hardware();
    INFO("DragonFly v{} successfully initialized", DRAGONFLY_VERSION);
}

void df::Application::main_loop()
{
    INFO("Entering main application loop");

    for (int i = 0;; i++)
    {
        // INFO("Main loop iteration: {}", i);

// Simulate some work
#if BUILD_ENV_NAME == teensy41
        delay(1);
#endif
    }
}

// ------------------------------ Private methods ---------------------------- //

void df::Application::setup_hardware()
{
}

void df::Application::setup_logging()
{
    init_logger();
    DEBUG("Logging system initialized...");
}
// ---------------------------------------------------------------------------- //
