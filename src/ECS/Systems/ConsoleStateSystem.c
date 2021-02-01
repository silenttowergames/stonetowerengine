#include "ConsoleStateSystem.h"
#include "../../Input/KeyboardStateFunctions.h"

static bool didAllowTyping = false;

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
        if(app->console.lines[app->console.history] == NULL)
        {
            app->console.lines[app->console.history] = malloc(sizeof(char) * (app->console.length + 1));
            sprintf(app->console.lines[app->console.history], "%s", app->console.line);
            
            app->console.history++;
            
            app->console.historyMemory = -1;
            
            printf("%d\n", app->console.history);
        }
        
        app->console.line[0] = '\0';
    }
    
    if(keys(Pressed, UP) && app->console.historyMemory < app->console.history && app->console.lines[app->console.historyMemory + 1] != NULL)
    {
        app->console.historyMemory++;
        
        printf("%d\n", app->console.historyMemory);
        
        sprintf(app->console.line, "%s", app->console.lines[app->console.history - app->console.historyMemory - 1]);
    }
    
    if(keys(Pressed, DOWN) && app->console.historyMemory >= 0)
    {
        if(app->console.lines[app->console.historyMemory - 1] == NULL)
        {
            app->console.historyMemory = -1;
            
            sprintf(app->console.line, "");
            
            printf("done\n");
        }
        else
        {
            app->console.historyMemory--;
            
            printf("%d\n", app->console.historyMemory);
            
            sprintf(app->console.line, "%s", app->console.lines[app->console.history - app->console.historyMemory - 1]);
        }
    }
}
