#pragma once

#include "Driver/CubeDriver.h"

#if CUBE8
#include "Driver/CubeDriver_8x8x8.h"
#elif CUBE16
#include "Driver/CubeDriver_OK16.h"
#endif

extern CubeDriver* cube;