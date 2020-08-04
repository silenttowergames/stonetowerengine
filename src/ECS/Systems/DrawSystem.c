#include <assert.h>
#include <flecs.h>
#include "../../Application/ApplicationState.h"
#include "../../Rendering/CameraFunctions.h"
#include "../../Rendering/SpriteBatchFunctions.h"
#include "../../Utilities/float4d.h"
#include "../../Utilities/quadFunctions.h"

void DrawSystem(ecs_iter_t* it)
{
	ApplicationState* app = (ApplicationState*)ecs_get_context(it->world);
	
	// TODO: Draw all render targets, then to the window
	
	SpriteBatch_Begin(&app->renderState.spriteBatch);
	
	/*
	quad pos = quad_Easy(-8, -8, 16, 16);
	quad src = quad_Frame(&app->renderState.texture, 1, 0);
	SpriteBatch_AddQuad(&app->renderState.spriteBatch, pos, src);
	*/
	
	Body* body = ecs_column(it, Body, 1);
	Renderable* renderable = ecs_column(it, Renderable, 2);
	quad pos, src;
	float2d size;
	for(int i = 0; i < it->count; i++)
	{
		body[i].position.X += 0.67f;
		body[i].position.Y += 0.67f;
		
		if(body[i].position.X >= 160)
		{
			body[i].position.X -= 320;
		}
		
		if(body[i].position.Y >= 90)
		{
			body[i].position.Y -= 180;
		}
		
		renderable[i].render(&app->renderState.spriteBatch, &renderable[i], &body[i]);
	}
	
	FNA3D_SetViewport(app->renderState.device, &app->renderState.viewport);
	
	FNA3D_SetRenderTargets(
		app->renderState.device,
		NULL,
		0,
		NULL,
		FNA3D_DEPTHFORMAT_NONE
	);
	
	FNA3D_BeginFrame(app->renderState.device);
	
	FNA3D_Vec4 color = { 1, 0.5f, 1, 1, };
	FNA3D_Clear(
		app->renderState.device,
		FNA3D_CLEAROPTIONS_TARGET,
		&color,
		0,
		0
	);
	
	MOJOSHADER_effectParam* shaderMatrix = Shader_ParamGet(&app->renderState.shaderSpriteEffect, "MatrixTransform");
	assert(shaderMatrix != NULL);
	Camera_LoadInto(&app->renderState.camera, shaderMatrix->value.values);
	
	MOJOSHADER_effectStateChanges stateChanges;
	memset(&stateChanges, 0, sizeof(stateChanges));
	FNA3D_ApplyEffect(app->renderState.device, app->renderState.shaderSpriteEffect.effect, 0, &stateChanges);
	
	SpriteBatch_Flush(&app->renderState);
	
	FNA3D_SwapBuffers(app->renderState.device, NULL, NULL, app->renderState.window);
	
	SpriteBatch_End(&app->renderState.spriteBatch);
}
