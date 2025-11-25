#include <dragonfly/config.h>
#include <dragonfly/version.h>
#include <dragonfly/environment.h>
#include <dragonfly/logging.h>

#include <dragonfly/dragonfly.h>

// ------------------------------ Public methods ----------------------------- //

void df::Dragonfly::main_loop()
{
    INFO("Entering main application loop");

    for (int i = 0;; i++)
    {

// Simulate some work
#if BUILD_ENV_NAME == teensy41
        delay(1);
#endif

        update_state();
    }
}

// ------------------------------ Private methods ---------------------------- //

void df::Dragonfly::init()
{
    setup_logging();
    setup_sensors();
    INFO("DragonFly v{} successfully initialized", DRAGONFLY_VERSION);
}

void df::Dragonfly::setup_sensors()
{
    // Orientation Sensor
    switch (ORIENTATION_SENSOR)
    {
    case MPU9250:
        // Unimplemented
        break;
    case SYNTHETIC_SENSOR:
    default:
        orientation_sensor_ = std::make_unique<df::SyntheticIMU>();
        INFO("Orientation sensor: Mock");
        break;
    }

    // Altitude Sensor
    switch (ALTITUDE_SENSOR)
    {
    case BMP388:
        // Unimplemented
        break;
    case SYNTHETIC_SENSOR:
    default:
        altitude_sensor_ = std::make_unique<df::SyntheticBarometer>();
        INFO("Altitude sensor: Mock");
        break;
    }

    // Arm Sensor
    switch (ARM_SENSOR)
    {
    case GPIO_PIN:
        // Unimplemented
        break;
    case SYNTHETIC_SENSOR:
    default:
        arm_sensor_ = std::make_unique<df::SyntheticInput>();
        INFO("Arm sensor: Mock");
        break;
    }
}

void df::Dragonfly::update_state()
{

    scope::Quaternion_f orientation = orientation_sensor_->get_orientation();
    float altitude;
    if (altitude_sensor_.has_value())
    {
        altitude = altitude_sensor_.value()->get_altitude();
    }
    else
    {
        altitude = 0.0f;
    }
    bool armed = arm_sensor_->is_armed();

    INFO("Orientation: w: {:.3f}, x: {:.3f}, y: {:.3f}, z: {:.3f}", orientation.w, orientation.x, orientation.y, orientation.z);
    INFO("Altitude: {:.3f}", altitude);
    INFO("Armed: {}", armed);
}

void df::Dragonfly::setup_logging()
{
    init_logger();
    DEBUG("Logging system initialized...");
}
// ---------------------------------------------------------------------------- //
