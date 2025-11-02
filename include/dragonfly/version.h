#pragma once
#include <array>
#include <cstdio>

namespace df
{
    const int MAJOR_VERSION = 0;
    const int MINOR_VERSION = 1;
    const int PATCH_VERSION = 0;

    inline const char *version_string()
    {
        // Build the version string once in static storage
        static const std::array<char, 20> version = []()
        {
            std::array<char, 20> buffer{};
            std::snprintf(buffer.data(), buffer.size(), "%d.%d.%d", MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION);
            return buffer;
        }();

        return version.data();
    }
}

#define DRAGONFLY_VERSION df::version_string()
