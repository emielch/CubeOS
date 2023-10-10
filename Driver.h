#pragma once

#include "Driver/CubeDriver.h"

#if CUBE8
#include "Driver/CubeDriver_8x8x8.h"
CubeDriver* cube = new CubeDriver_8x8x8();
#elif CUBE16
#include "Driver/CubeDriver_OK16.h"
CubeDriver* cube = new CubeDriver_OK16();
#endif