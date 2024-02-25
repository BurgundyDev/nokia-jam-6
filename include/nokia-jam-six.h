
#pragma once
#include "raylib.h"
#include <vector>

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

#define NOKIA_BUILD
inline Color BACKGROUND = {173,204,96,255};
inline Color FOREGROUND = {43,51,24,255};
inline int WINDOW_WIDTH = 1280;
inline int WINDOW_HEIGHT = 960;
inline int NOKIA_WIDTH = 320;
inline int NOKIA_HEIGHT = 240;
inline int PIXEL_SCALE = WINDOW_WIDTH/NOKIA_WIDTH;
inline int PIXEL_PER_CELL = 10;
#ifndef NOKIA_BUILD
inline int CELL_SIZE = 80;
#else
inline int CELL_SIZE = 20;
#endif
inline int CELL_COUNT = 12;