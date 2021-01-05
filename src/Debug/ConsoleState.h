#pragma once

#include <flecs.h>

#define CONSOLESTATE_LINE_LENGTH 256

typedef struct ConsoleState
{
    bool active;
    char line[CONSOLESTATE_LINE_LENGTH];
    int length;
} ConsoleState;
