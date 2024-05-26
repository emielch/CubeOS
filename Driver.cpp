#include "Driver.h"

#if CUBE8
CubeDriver* cube = new CubeDriver_8x8x8();
#elif CUBE16
CubeDriver* cube = new CubeDriver_OK16();
#elif CUBE25
CubeDriver* cube = new CubeDriver_Q25();
#endif