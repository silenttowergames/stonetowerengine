#include <assert.h>
#include <flecs.h>
#include "DrawSystem.h"
#include "../Components/Body.h"
#include "../Components/Renderable.h"
#include "../../Application/ApplicationState.h"
#include "../../Rendering/CameraFunctions.h"
#include "../../Rendering/SpriteBatchFunctions.h"
#include "../../Utilities/float4d.h"
#include "../../Utilities/quadFunctions.h"
#include "../../Rendering/RenderTargetFunctions.h"

void DrawSystem(ecs_iter_t* it)
{
	ApplicationState* app = (ApplicationState*)ecs_get_context(it->world);
	
	Body* body = ecs_column(it, Body, 1);
	Renderable* renderable = ecs_column(it, Renderable, 2);
	quad pos, src;
	float2d size;
	for(int i = 0; i < it->count; i++)
	{
		if(app->renderState.currentRenderTargetID != renderable[i].renderTargetID)
		{
			if(app->renderState.currentRenderTargetID >= 0)
			{
				RenderTarget_Stop(app);
			}
			
			RenderTarget_Start(app, renderable[i].renderTargetID);
		}
		
		renderable[i].render(app, &app->renderState.spriteBatch, &app->renderState.targets[app->renderState.currentRenderTargetID].camera, &renderable[i], body[i].position);
	}
}
