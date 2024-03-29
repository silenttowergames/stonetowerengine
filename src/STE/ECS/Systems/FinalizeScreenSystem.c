#include <flecs.h>
#include <FNA3D.h>
#include "FinalizeScreenSystem.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Rendering/CameraFunctions.h"
#include "../../Rendering/RenderTargetFunctions.h"
#include "../../Rendering/SpriteBatchFunctions.h"
#include "../../Utilities/float4d.h"
#include "../../Utilities/quadFunctions.h"

static char FinalizeScreenSystem_UI_FPS[14];

static void FinalizeScreenSystem_ToMainRT(ApplicationState* app)
{
	RenderTarget_Start(app, RENDERTARGET_MAIN);
	
	for(int i = 0; i < app->renderState.targetsCount; i++)
	{
		RenderTarget* renderTarget = &app->renderState.targets[i];
		
		int2d size = (int2d){
			//*
			renderTarget->drawResolution.X / 2,
			renderTarget->drawResolution.Y / 2,
			//*/
			/*
			renderTarget->camera.resolution.X / 2,
			renderTarget->camera.resolution.Y / 2,
			//*/
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
	
	// Main RT shaders
	
	Texture swap;
	MOJOSHADER_effectStateChanges stateChanges;
	Shader* shader = NULL;
	for(int i = 0; i < app->renderState.mainRenderTarget.shadersCount; i++)
	{
		swap = app->renderState.mainRenderTarget.backupTexture;
		app->renderState.mainRenderTarget.backupTexture = app->renderState.mainRenderTarget.texture;
		app->renderState.mainRenderTarget.texture = swap;
		app->renderState.mainRenderTarget.binding.texture = swap.asset;
		
		stateChanges = RenderTarget_Start(app, RENDERTARGET_MAIN);
		
		shader = app->renderState.mainRenderTarget.shaders[i];
		
		if(shader->update != NULL)
		{
			shader->update(app, &app->renderState.mainRenderTarget, shader);
		}
		
		if(!shader->disabled)
		{
			FNA3D_ApplyEffect(app->renderState.device, shader->effect, 0, &stateChanges);
		}
		
		int2d size = (int2d){
			app->renderState.mainRenderTarget.drawResolution.X / 2,
			app->renderState.mainRenderTarget.drawResolution.Y / 2,
		};
		quad pos = (quad){
			{ -size.X + app->renderState.mainRenderTarget.position.X, -size.Y + app->renderState.mainRenderTarget.position.Y, },
			{ size.X + app->renderState.mainRenderTarget.position.X, -size.Y + app->renderState.mainRenderTarget.position.Y, },
			{ -size.X + app->renderState.mainRenderTarget.position.X, size.Y + app->renderState.mainRenderTarget.position.Y, },
			{ size.X + app->renderState.mainRenderTarget.position.X, size.Y + app->renderState.mainRenderTarget.position.Y, },
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
			app->renderState.mainRenderTarget.backupTexture.asset,
			pos,
			src,
			0xFFFFFFFF
		);
		
		RenderTarget_Stop(app);
	}
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
	fonsSetFont(app->fons, (*mapGet(app->assetManager.mapFont, "PressStart2P/PressStart2P.ttf", Font*))->fonsID);
	fonsSetColor(app->fons, colorU(255, 255, 255, 255));
	
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
		
		fonsSetSize(app->fons, 8.0f);
		fonsDrawText(app->fons, -((app->renderState.resolution.X / 2) * app->renderState.windowZoom.X) + 2, -((app->renderState.resolution.Y / 2) * app->renderState.windowZoom.Y) + 10, app->console.line, NULL);
	}
	
	// Render FPS
	if(app->showFPS)
	{
		sprintf(FinalizeScreenSystem_UI_FPS, "%1.5f FPS", app->averageFPS);
		fonsSetSize(app->fons, 16.0f);
		fonsDrawText(
			app->fons,
			-((app->renderState.resolution.X / 2) * app->renderState.windowZoom.X) + 2,
			((app->renderState.resolution.Y / 2) * app->renderState.windowZoom.Y),
			FinalizeScreenSystem_UI_FPS,
			NULL
		);
	}
}

void FinalizeScreenSystem(ecs_iter_t* it)
{
	fctx();
	
	RenderTarget_Stop(app);
	
	FinalizeScreenSystem_ToMainRT(app);
	FinalizeScreenSystem_ToWindow(app);
}
