#include "ConsoleStateSystem.h"
#include "../../Debug/ConsoleCommand.h"
#include "../../Input/KeyboardStateFunctions.h"
#include "../../Utilities/split.h"

static bool didAllowTyping = false;
static char lineCmd[CONSOLESTATE_LINE_LENGTH + 2];
static char* paramName;
static ConsoleCommand* cmd;
static char* paramsList;
static char** params;
static int paramsCount;

void ConsoleStateSystem(ApplicationState* app)
{
    if(keys(Down, LCTRL) && keys(Pressed, BACKQUOTE))
    {
        app->console.active = !app->console.active;
        
        if(app->console.active)
        {
            didAllowTyping = app->inputManager.keyboardState.acceptingTyping;
            
            app->inputManager.keyboardState.acceptingTyping = true;
        }
        else
        {
            app->inputManager.keyboardState.acceptingTyping = didAllowTyping;
        }
        
        return;
    }
    
    if(!app->console.active)
    {
        return;
    }
    
    int lineLength = strlen(app->console.line);
    int queueLength = strlen(app->inputManager.keyboardState.letterQueue);
    
    if(queueLength && lineLength + queueLength < CONSOLESTATE_LINE_LENGTH)
    {
        sprintf(app->console.line, "%s%s", app->console.line, app->inputManager.keyboardState.letterQueue);
        
        app->console.historyMemory = -1;
    }
    
    app->console.length = strlen(app->console.line);
    
    if(keys(Held, BACKSPACE) && app->console.length > 0)
    {
        app->console.length--;
        app->console.line[app->console.length] = '\0';
        
        app->console.historyMemory = -1;
    }
    
    if(keys(Pressed, RETURN) && app->console.line[0] != '\0')
    {
        if(app->console.history <= 0 || strcmp(app->console.line, app->console.lines[app->console.history - 1]))
        {
            if(app->console.lines[app->console.history] == NULL)
            {
                app->console.lines[app->console.history] = malloc(sizeof(char) * (app->console.length + 1));
                sprintf(app->console.lines[app->console.history], "%s", app->console.line);
                
                if(app->console.history < CONSOLESTATE_HISTORY_LENGTH - 1)
                {
                    app->console.history++;
                }
            }
            else
            {
                for(int i = 0; i < CONSOLESTATE_HISTORY_LENGTH - 1; i++)
                {
                    strcpy(app->console.lines[i], app->console.lines[i + 1]);
                }
                
                sprintf(app->console.lines[app->console.history], "%s", app->console.line);
            }
        }
        
        app->console.historyMemory = -1;
        
        strcpy(lineCmd, app->console.line);
        
        paramName = strtok(lineCmd, " ");
        
        if(paramName != NULL)
        {
            paramsList = &lineCmd[strlen(paramName) + 1];
            
            cmd = mapGet(app->console.commands, paramName, ConsoleCommand);
            
            if(cmd != NULL)
            {
                params = split(paramsList, strlen(paramsList), ' ', &paramsCount);
                
                cmd->callable(app, paramsCount, params);
            }
        }
        
        app->console.line[0] = '\0';
    }
    
    if(keys(Pressed, UP) && app->console.historyMemory < app->console.history && app->console.lines[app->console.historyMemory + 1] != NULL)
    {
        app->console.historyMemory++;
        
        sprintf(app->console.line, "%s", app->console.lines[app->console.history - app->console.historyMemory - 1]);
    }
    
    if(keys(Pressed, DOWN) && app->console.historyMemory >= 0)
    {
        if(app->console.lines[app->console.historyMemory - 1] == NULL)
        {
            app->console.historyMemory = -1;
            
            sprintf(app->console.line, "");
        }
        else
        {
            app->console.historyMemory--;
            
            sprintf(app->console.line, "%s", app->console.lines[app->console.history - app->console.historyMemory - 1]);
        }
    }
}