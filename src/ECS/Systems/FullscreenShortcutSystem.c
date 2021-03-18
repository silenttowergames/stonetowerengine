#include "FullscreenShortcutSystem.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Input/KeyboardStateFunctions.h"

void FullscreenShortcutSystem(ecs_iter_t* it)
{
    fctx();
    
    if(
		((keys(Down, LALT) || keys(Down, RALT)) && keys(Pressed, RETURN))
		||
		((keys(Down, LCTRL) || keys(Down, RCTRL)) && keys(Pressed, f))
	)
	{
		if(app->config.fullscreen)
		{
			Config_Resize(app, 1280, 720, false);
		}
		else
		{
			Config_Resize(app, -1, -1, true);
		}
	}
}
