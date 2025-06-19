#include <logging.h>
#include <config.h>

#if BUILD_ENV_NAME == native_env
#include <filesystem>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

// Native environment implementation
std::shared_ptr<spdlog::logger> g_logger;

void init_logger()
{
    try
    {
        // Create logs directory if it doesn't exist
        std::filesystem::create_directories("logs");

        // Create console logger
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::trace);

        // Create file logger
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/dragonfly.log", true);
        file_sink->set_level(spdlog::level::trace);

        // Combine both sinks
        std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};

        // Create a daily logger
        g_logger = std::make_shared<spdlog::logger>("dragonfly", sinks.begin(), sinks.end());

        // Set pattern: [timestamp] [level] message
        g_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");

#if defined(DEBUG_VERBOSE)
        g_logger->set_level(spdlog::level::debug);
#else
        g_logger->set_level(spdlog::level::info);
#endif

        // Enable automatic flushing
        g_logger->flush_on(spdlog::level::warn);
    }

    catch (const std::exception &ex)
    {
        // Fallback to console if file logging fails
        g_logger = spdlog::stdout_color_mt("console");
        g_logger->error("Failed to initialize file logger: {}", ex.what());
    }
}

#elif BUILD_ENV_NAME == teensy41
// Teensy41 environment implementation
void init_logger()
{
    Serial.begin(BAUD_RATE);
    // Wait for serial port to connect
    while (!Serial)
    {
        delay(10);
    }
    Serial.println("[INFO] Logger initialized for Teensy41 environment");
}

void serial_log(const char *level, const char *message)
{
    Serial.print("[");
    Serial.print(level);
    Serial.print("] ");
    Serial.println(message);
}

#endif
