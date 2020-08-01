#include <flecs.h>
#include "../../Application/ApplicationState.h"
#include "../../Rendering/CameraFunctions.h"

void DrawSystem(ecs_iter_t* it)
{
	ApplicationState* app = (ApplicationState*)ecs_get_context(it->world);
	
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
	
	for (int i = 0; i < app->renderState.shaderSpriteEffect.effectData->param_count; i++)
	{
		if (strcmp("MatrixTransform", app->renderState.shaderSpriteEffect.effectData->params[i].value.name) == 0)
		{
			// OrthographicOffCenter Matrix - value copied from XNA project
			// todo: Do I need to worry about row-major/column-major?
			
			Camera_LoadInto(&app->renderState.camera, app->renderState.shaderSpriteEffect.effectData->params[i].value.values);
			
			break;
		}
	}
	
	MOJOSHADER_effectStateChanges stateChanges;
	memset(&stateChanges, 0, sizeof(stateChanges));
	FNA3D_ApplyEffect(app->renderState.device, app->renderState.shaderSpriteEffect.effect, 0, &stateChanges);
	
	FNA3D_SwapBuffers(app->renderState.device, NULL, NULL, app->renderState.window);
}
