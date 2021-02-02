#pragma once

#include <flecs.h>

#define CONSOLESTATE_LINE_LENGTH 256
#define CONSOLESTATE_HISTORY_LENGTH 1024

typedef struct ConsoleState
{
    bool active;
    char line[CONSOLESTATE_LINE_LENGTH];
    char* lines[CONSOLESTATE_HISTORY_LENGTH];
    int length;
    int history;
    int historyMemory;
    ecs_map_t* commands;
} ConsoleState;
