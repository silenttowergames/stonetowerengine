#pragma once

#include "../Application/ApplicationState.h"

typedef struct ConsoleCommand
{
    const char* key;
    void (*callable)(ApplicationState* app, int argc, char** argv);
} ConsoleCommand;
