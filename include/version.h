#pragma once

namespace df
{
    const int MAJOR_VERSION = 0;
    const int MINOR_VERSION = 1;
    const int PATCH_VERSION = 0;

    inline const char *version_string()
    {
        return "0.1.0";
    }
}

#define DRAGONFLY_VERSION df::version_string()