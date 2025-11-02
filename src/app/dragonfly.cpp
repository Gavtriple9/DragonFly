#include <dragonfly/config.h>
#include <dragonfly/version.h>
#include <dragonfly/environment.h>
#include <dragonfly/logging.h>

#include <dragonfly/dragonfly.h>

// ------------------------------ Public methods ----------------------------- //

void df::Dragonfly::init()
{
    setup_logging();
    setup_hardware();
    INFO("DragonFly v{} successfully initialized", DRAGONFLY_VERSION);
}

void df::Dragonfly::main_loop()
{
    INFO("Entering main application loop");

    for (int i = 0;; i++)
    {
        INFO("Main loop iteration: {}", i);

// Simulate some work
#if BUILD_ENV_NAME == teensy41
        delay(1);
#endif
    }
}

// ------------------------------ Private methods ---------------------------- //

void df::Dragonfly::setup_hardware()
{
}

void df::Dragonfly::setup_logging()
{
    init_logger();
    DEBUG("Logging system initialized...");
}
// ---------------------------------------------------------------------------- //
