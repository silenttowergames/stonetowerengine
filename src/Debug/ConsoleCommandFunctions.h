#pragma once

#include "ConsoleCommand.h"

ConsoleCommand ConsoleCommand_Create(const char* key, void (*callable)(ApplicationState* app, int argc, char** argv));
void ConsoleCommand_AddAll(ApplicationState* app, int count, ...);
