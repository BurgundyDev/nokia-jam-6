
#pragma once

#include <iostream>

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif


int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;
