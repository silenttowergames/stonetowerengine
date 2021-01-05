#include "ConsoleStateSystem.h"
#include "../../Input/KeyboardStateFunctions.h"

static bool didAllowTyping = false;

void ConsoleStateSystem(ApplicationState* app)
{
    if(keys(Pressed, BACKQUOTE))
    {
        app->console.active = !app->console.active;
        
        printf("%d\n", app->console.active);
        
        if(app->console.active)
        {
            didAllowTyping = app->inputManager.keyboardState.acceptingTyping;
            
            app->inputManager.keyboardState.acceptingTyping = true;
        }
        else
        {
            app->inputManager.keyboardState.acceptingTyping = didAllowTyping;
        }
    }
    
    if(!app->console.active)
    {
        return;
    }
    
    int lineLength = strlen(app->console.line);
    int queueLength = strlen(app->inputManager.keyboardState.letterQueue);
    
    if(lineLength + queueLength < CONSOLESTATE_LINE_LENGTH)
    {
        sprintf(app->console.line, "%s%s", app->console.line, app->inputManager.keyboardState.letterQueue);
    }
    
    app->console.length = strlen(app->console.line);
    
    if(keys(Held, BACKSPACE))
    {
        app->console.length--;
        app->console.line[app->console.length] = '\0';
    }
}
