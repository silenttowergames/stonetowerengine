#include <flecs.h>
#include "CameraFollowSystem.h"
#include "../../Application/ApplicationStateFunctions.h"

void CameraFollowSystem(ecs_iter_t* it)
{
	fctx();
	
	Body* b = ecs_column(it, Body, 1);
	CameraFollow* c = ecs_column(it, CameraFollow, 2);
	Renderable* r = ecs_column(it, Renderable, 3);
	int rt;
	
	for(int i = 0; i < it->count; i++)
	{
		app->renderState.targets[r[i].renderTargetID].camera.position.X = b[i].position.X + c[i].offset.X;
		app->renderState.targets[r[i].renderTargetID].camera.position.Y = b[i].position.Y + c[i].offset.Y;
		
		rt = r[i].renderTargetID;
	}
	
	if(rt != 2)
	{
		app->renderState.targets[2].camera.position = app->renderState.targets[1].camera.position;
	}
	
	//app->renderState.targets[0].camera.position.Y = -16;
}
