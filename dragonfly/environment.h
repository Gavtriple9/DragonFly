#pragma once

#ifndef BUILD_ENV_NAME
#error "BUILD_ENV_NAME preprocessor macro must be defined. Add -D BUILD_ENV_NAME=<environment> to your build flags."
#else
#define native_env 100
#define teensy41 101
#endif
