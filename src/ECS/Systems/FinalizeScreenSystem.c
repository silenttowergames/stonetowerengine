#include <flecs.h>
#include <FNA3D.h>
#include "FinalizeScreenSystem.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Rendering/CameraFunctions.h"
#include "../../Rendering/RenderTargetFunctions.h"
#include "../../Rendering/SpriteBatchFunctions.h"
#include "../../Utilities/float4d.h"
#include "../../Utilities/quadFunctions.h"

static void FinalizeScreenSystem_ToMainRT(ApplicationState* app)
{
	RenderTarget_Start(app, RENDERTARGET_MAIN);
	
	for(int i = 0; i < app->renderState.targetsCount; i++)
	{
		RenderTarget* renderTarget = &app->renderState.targets[i];
		
		int2d size = (int2d){
			renderTarget->camera.resolution.X / 2,
			renderTarget->camera.resolution.Y / 2,
		};
		quad pos = (quad){
			{ -size.X + renderTarget->position.X, -size.Y + renderTarget->position.Y, },
			{ size.X + renderTarget->position.X, -size.Y + renderTarget->position.Y, },
			{ -size.X + renderTarget->position.X, size.Y + renderTarget->position.Y, },
			{ size.X + renderTarget->position.X, size.Y + renderTarget->position.Y, },
		};
		quad src = (quad){
			{ 0, 0, },
			{ 1, 0, },
			{ 0, 1, },
			{ 1, 1, },
		};
		
		SpriteBatch_AddQuad(
			&app->renderState.spriteBatch,
			&app->renderState.camera,
			renderTarget->texture.asset,
			pos,
			src,
			0xFFFFFFFF
		);
	}
	
	RenderTarget_Stop(app);
}

static void FinalizeScreenSystem_ToWindow(ApplicationState* app)
{
	RenderTarget_Start(app, RENDERTARGET_NONE);
	
	int2d size = (int2d){
		app->renderState.resolution.X / 2,
		app->renderState.resolution.Y / 2,
	};
	quad pos = (quad){
		{ -size.X, -size.Y, },
		{ size.X, -size.Y, },
		{ -size.X, size.Y, },
		{ size.X, size.Y, },
	};
	quad src = (quad){
		{ 0, 0, },
		{ 1, 0, },
		{ 0, 1, },
		{ 1, 1, },
	};
	
	SpriteBatch_AddQuad(
		&app->renderState.spriteBatch,
		&app->renderState.camera,
		app->renderState.mainRenderTarget.texture.asset,
		pos,
		src,
		0xFFFFFFFF
	);
	
	RenderTarget_Stop(app);
	
	FNA3D_SwapBuffers(app->renderState.device, NULL, NULL, app->renderState.window);
}

void FinalizeScreenSystem(ecs_iter_t* it)
{
	fctx();
	
	RenderTarget_Stop(app);
	
	FinalizeScreenSystem_ToMainRT(app);
	FinalizeScreenSystem_ToWindow(app);
}
