#include <flecs.h>
#include "ConsoleCommandFunctions.h"

ConsoleCommand ConsoleCommand_Create(const char* key, void (*callable)(ApplicationState* app, int argc, char** argv))
{
    ConsoleCommand cmd;
    
    cmd.key = key;
    cmd.callable = callable;
    
    return cmd;
}

void ConsoleCommand_AddAll(ApplicationState* app, int count, ...)
{
    va_list args;
    ConsoleCommand cmd;
    
    app->console.commands = ecs_map_new(ConsoleCommand, count);
    
    va_start(args, count);
    
    for(int i = 0; i < count; i++)
    {
        cmd = va_arg(args, ConsoleCommand);
        
        mapSet(app->console.commands, cmd.key, &cmd);
    }
    
    va_end(args);
}

