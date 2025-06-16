#include "init.hpp"
#include <config.h>

// Define static member variable
usb_serial_class df::Application::logger;
df::State df::Application::state;

// ------------------------------ Public methods ----------------------------- //

void df::Application::init()
{
    setup_logging();
    setup_hardware();
}

void df::Application::main_loop()
{
    for (int i = 0;; i++)
    {
        logger.printf("Hello %d\n", i);
        delay(1000);
    }
}

// ------------------------------ Private methods ---------------------------- //

void df::Application::setup_hardware()
{
    // !TODO: Implement hardware setup logic
}

void df::Application::setup_logging()
{
    logger = Serial;
    logger.begin(BAUD_RATE);
    while (!this->logger)
    {
    }
}
// ---------------------------------------------------------------------------- //