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
			app,
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
		/*
		{ -size.X, -size.Y - (app->renderState.viewport.y / (app->renderState.windowZoom.Y / 2)), },
		{ size.X, -size.Y - (app->renderState.viewport.y / (app->renderState.windowZoom.Y / 2)), },
		{ -size.X, size.Y - (app->renderState.viewport.y / (app->renderState.windowZoom.Y / 2)), },
		{ size.X, size.Y - (app->renderState.viewport.y / (app->renderState.windowZoom.Y / 2)), },
		*/
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
		app,
		&app->renderState.spriteBatch,
		&app->renderState.camera,
		app->renderState.mainRenderTarget.texture.asset,
		pos,
		src,
		0xFFFFFFFF
	);
	
	RenderTarget_Stop(app);
	
	app->renderState.camera.zoom.X /= app->renderState.windowZoom.X;
	app->renderState.camera.zoom.Y /= app->renderState.windowZoom.Y;
	RenderTarget_Start(app, RENDERTARGET_WINDOW);
	FinalizeScreenSystem_UI(app);
	RenderTarget_Stop(app);
	app->renderState.camera.zoom.X *= app->renderState.windowZoom.X;
	app->renderState.camera.zoom.Y *= app->renderState.windowZoom.Y;
	
	FNA3D_SwapBuffers(app->renderState.device, NULL, NULL, app->renderState.window);
}

static void FinalizeScreenSystem_UI(ApplicationState* app)
{
	if(app->console.active)
	{
		quad qPos = {
			{ -(app->renderState.resolution.X / 2) * app->renderState.windowZoom.X, -(app->renderState.resolution.Y / 2) * app->renderState.windowZoom.Y, },
			{ (app->renderState.resolution.X / 2) * app->renderState.windowZoom.X, -(app->renderState.resolution.Y / 2) * app->renderState.windowZoom.Y, },
			{ -(app->renderState.resolution.X / 2) * app->renderState.windowZoom.X, -((app->renderState.resolution.Y / 2) * app->renderState.windowZoom.Y) + 12, },
			{ (app->renderState.resolution.X / 2) * app->renderState.windowZoom.X, -((app->renderState.resolution.Y / 2) * app->renderState.windowZoom.Y) + 12, },
		};
		quad qSrc = quad_Frame(&app->renderState.blankTexture, 0, 0);
		
		SpriteBatch_AddQuad(
			app,
			&app->renderState.spriteBatch,
			&app->renderState.windowCamera,
			app->renderState.blankTexture.asset,
			qPos,
			qSrc,
			colorU(0, 0, 0, 150)
		);
		
		qPos = (quad){
			{ -((app->renderState.resolution.X / 2) * app->renderState.windowZoom.X) + (app->console.length * 8) + 2, -((app->renderState.resolution.Y / 2) * app->renderState.windowZoom.Y) + 2, },
			{ -((app->renderState.resolution.X / 2) * app->renderState.windowZoom.X) + (app->console.length * 8) + 10, -((app->renderState.resolution.Y / 2) * app->renderState.windowZoom.Y) + 2, },
			{ -((app->renderState.resolution.X / 2) * app->renderState.windowZoom.X) + (app->console.length * 8) + 2, -((app->renderState.resolution.Y / 2) * app->renderState.windowZoom.Y) + 10, },
			{ -((app->renderState.resolution.X / 2) * app->renderState.windowZoom.X) + (app->console.length * 8) + 10, -((app->renderState.resolution.Y / 2) * app->renderState.windowZoom.Y) + 10, },
		};
		SpriteBatch_AddQuad(
			app,
			&app->renderState.spriteBatch,
			&app->renderState.windowCamera,
			app->renderState.blankTexture.asset,
			qPos,
			qSrc,
			colorU(255, 255, 255, 255)
		);
		
		fonsSetColor(app->fons, colorU(255, 255, 255, 255));
		fonsDrawText(app->fons, -((app->renderState.resolution.X / 2) * app->renderState.windowZoom.X) + 2, -((app->renderState.resolution.Y / 2) * app->renderState.windowZoom.Y) + 10, app->console.line, NULL);
	}
}

void FinalizeScreenSystem(ecs_iter_t* it)
{
	fctx();
	
	RenderTarget_Stop(app);
	
	FinalizeScreenSystem_ToMainRT(app);
	FinalizeScreenSystem_ToWindow(app);
}
