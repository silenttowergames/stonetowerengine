#include <flecs.h>
#include "../../Application/ApplicationState.h"

void DrawSystem(ecs_iter_t* it)
{
	ApplicationState* app = (ApplicationState*)ecs_get_context(it->world);
	
	FNA3D_SetViewport(app->renderState.device, &app->renderState.viewport);
	
	/*
	for (int i = 0; i < spriteBatch->shader.effectData->param_count; i++)
	{
		if (strcmp("MatrixTransform", spriteBatch->shader.effectData->params[i].value.name) == 0)
		{
			// OrthographicOffCenter Matrix - value copied from XNA project
			// todo: Do I need to worry about row-major/column-major?
			float projectionMatrix[16];
			
			Matrix matrix = MatrixCreateFromCamera(camera);
			
			MatrixToTransform(&matrix, projectionMatrix);
			
			memcpy(spriteBatch->shader.effectData->params[i].value.values, projectionMatrix, sizeof(float) * 16);
			
			break;
		}
	}
	//*/
	
	FNA3D_SetRenderTargets(
		app->renderState.device,
		NULL,
		0,
		NULL,
		FNA3D_DEPTHFORMAT_NONE
	);
	
	FNA3D_BeginFrame(app->renderState.device);
	
	FNA3D_Vec4 color = { 1, 0, 0, 1, };
	FNA3D_Clear(
		app->renderState.device,
		FNA3D_CLEAROPTIONS_TARGET,
		&color,
		0,
		0
	);
}
