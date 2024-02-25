
#pragma once
#include "raylib.h"
#include <vector>
#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

inline std::vector<Color> const DARK_COLORS = {
    { 67, 82, 61,255 },
    { 43, 63, 9, 255 },
    { 26, 25, 20,  255 }
};

inline std::vector<Color> const LIGHT_COLORS = {
    { 199, 240, 216, 255 },
    { 155, 199, 0, 255 },
    { 135, 145, 136,  255 }
};

inline int currentColorScheme = 0;
inline int WINDOW_WIDTH = 840;
inline int WINDOW_HEIGHT = 480;
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