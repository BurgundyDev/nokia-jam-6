
#pragma once
#include "raylib.h"
#include <iostream>

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

inline Color BACKGROUND = {173,204,96,255};
inline Color FOREGROUND = {43,51,24,255};
inline int WINDOW_WIDTH = 1280;
inline int WINDOW_HEIGHT = 960;
inline int NOKIA_WIDTH = 84;
inline int NOKIA_HEIGHT = 48;
inline int PIXEL_SCALE = WINDOW_WIDTH/NOKIA_WIDTH;
inline int PIXEL_PER_CELL = 10;
#ifndef NOKIA_BUILD
inline int CELL_SIZE = 10;
#else
inline int CELL_SIZE = 1;
#endif
inline int CELL_COUNT = 12;
inline int CELL_COUNT_WIDTH = 48;
inline int CELL_COUNT_HEIGHT = 84;