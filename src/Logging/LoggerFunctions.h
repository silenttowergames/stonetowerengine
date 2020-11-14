#pragma once

#include <flecs.h>
#include "Logger.h"

bool Logger_Log(Logger* logger, const char* type, const char* message);
