// Stone Tower Engine
// Silent Tower Games LLC

// OS
// Windows
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

// Engine Code
// Application
#include "Application/ApplicationState.h"
// ECS
#include "ECS/Systems/SystemPrintHelloWorld.c"
#include "ECS/Systems/Test1System.c"
#include "ECS/Systems/Test2System.c"
#include "ECS/Systems/Test3System.c"
// Logger
#include "Logging/Logger.h"
#include "Logging/LoggerFunctions.c"
// Utilities
//
