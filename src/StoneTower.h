#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

// Dependencies
// MojoShader
#define MOJOSHADER_NO_VERSION_INCLUDE
#define MOJOSHADER_EFFECT_SUPPORT
#include <mojoshader.h>
#include <mojoshader_effects.h>
// SDL
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
// FNA3D
#include <FNA3D.h>
// C standards
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Flecs
#include <flecs.h>
// SoLoud
#define WITH_SDL2
#include <soloud_c.h>
// JSON-C
#include <json.h>
// Lua
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

// Vendor
// STB Image
#ifdef __MINGW32__
#define STBI_NO_THREAD_LOCALS
#endif
//#include "vendor/stb_image.h"
// FontStash
#define FONTSTASH_IMPLEMENTATION
//#include "vendor/fontstash/fontstash.h"
