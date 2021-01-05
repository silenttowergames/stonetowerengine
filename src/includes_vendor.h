#pragma once

// STB Image
#define STB_IMAGE_IMPLEMENTATION
#ifdef __MINGW32__
#define STBI_NO_THREAD_LOCALS
#endif
#include "vendor/stb_image.h"
// FontStash
#define FONTSTASH_IMPLEMENTATION
#include "vendor/fontstash/fontstash.h"
// lookup3 for hashing strings
#include "vendor/lookup3.c"
// Ini
#include "vendor/rxi/ini/ini.c"
