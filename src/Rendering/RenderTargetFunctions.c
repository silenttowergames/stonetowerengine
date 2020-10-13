#include <flecs.h>
#include "RenderTargetFunctions.h"
#include "../Application/ApplicationState.h"
#include "../Assets/TextureFunctions.h"
#include "../Utilities/colorFunctions.h"

RenderTarget RenderTarget_Create(ApplicationState* app, int2d resolution, int2d position, bool scale, FNA3D_Vec4 backgroundColor)
{
	RenderTarget renderTarget;
	memset(&renderTarget, 0, sizeof(renderTarget));
	
	renderTarget.scale = scale;
	
	int2d size = {
		resolution.X * (scale ? app->renderState.windowZoom.X : 1),
		resolution.Y * (scale ? app->renderState.windowZoom.Y : 1),
	};
	
	renderTarget.texture = Texture_NewBlank(app->renderState.device, size.X, size.Y, 4, true); // RenderTarget.texture allocate
	renderTarget.texture.tilesize.X = size.X;
	renderTarget.texture.tilesize.Y = size.Y;
	
	renderTarget.binding.type = FNA3D_RENDERTARGET_TYPE_2D;
	renderTarget.binding.texture = renderTarget.texture.asset;
	
	renderTarget.camera.resolution = resolution;
	renderTarget.camera.zoom.X = 1.0f;
	renderTarget.camera.zoom.Y = 1.0f;
	
	renderTarget.size = size;
	renderTarget.position = position;
	
	renderTarget.viewport.w = size.X;
	renderTarget.viewport.h = size.Y;
	
	if(renderTarget.scale)
	{
		renderTarget.viewport.y = app->renderState.viewport.y * 2;
	}
	else
	{
		renderTarget.viewport.y = app->renderState.size.Y - renderTarget.size.Y;
	}
	
	renderTarget.viewport.y = 0;
	
	renderTarget.backgroundColor = backgroundColor;
	
	return renderTarget;
}

RenderTarget RenderTarget_Refresh(ApplicationState* app, RenderTarget* renderTarget)
{
	RenderTarget ret = RenderTarget_Create(app, renderTarget->camera.resolution, renderTarget->position, renderTarget->scale, renderTarget->backgroundColor);
	
	size_t shadersSize = sizeof(Shader*) * renderTarget->shadersCount;
	ret.shadersCount = renderTarget->shadersCount;
	ret.shaders = malloc(shadersSize);
	memcpy(ret.shaders, renderTarget->shaders, shadersSize);
	
	RenderTarget_Destroy(renderTarget, app->renderState.device);
	
	return ret;
}

void RenderTarget_Start(ApplicationState* app, int renderTargetID)
{
	// Sort out which RenderTarget we're using
	
	app->renderState.currentRenderTargetID = renderTargetID;
	
	RenderTarget* renderTarget;
	
	switch(renderTargetID)
	{
		case RENDERTARGET_MAIN:
		{
			renderTarget = &app->renderState.mainRenderTarget;
			
			break;
		}
		
		case RENDERTARGET_NONE:
		{
			renderTarget = NULL;
			
			break;
		}
		
		default:
		{
			renderTarget = &app->renderState.targets[renderTargetID];
			
			break;
		}
	}
	
	// Open the SpriteBatch
	
	if(!app->renderState.spriteBatch.opened)
	{
		SpriteBatch_Begin(&app->renderState.spriteBatch);
	}
	
	// Set up the screen
	
	if(renderTarget == NULL)
	{
		FNA3D_SetViewport(app->renderState.device, &app->renderState.viewport);
		
		FNA3D_SetRenderTargets(
			app->renderState.device,
			NULL,
			0,
			NULL,
			FNA3D_DEPTHFORMAT_NONE,
			0
		);
	}
	else
	{
		FNA3D_SetViewport(app->renderState.device, &renderTarget->viewport);
		
		FNA3D_SetRenderTargets(
			app->renderState.device,
			&renderTarget->binding,
			1,
			NULL,
			FNA3D_DEPTHFORMAT_NONE,
			0
		);
	}
	
	// Clear the screen with this color
	
	// TODO: Use RenderTarget color
	FNA3D_Vec4 color;
	
	if(renderTarget == NULL)
	{
		color = (FNA3D_Vec4){ 0, 0, 0, 1, };
	}
	else
	{
		color = renderTarget->backgroundColor;
	}
	
	
	FNA3D_Clear(
		app->renderState.device,
		FNA3D_CLEAROPTIONS_TARGET,
		&color,
		0,
		0
	);
	
	// Use RenderTarget camera
	
	MOJOSHADER_effectParam* shaderMatrix = Shader_ParamGet(&app->renderState.shaderSpriteEffect, "MatrixTransform");
	assert(shaderMatrix != NULL);
	if(renderTarget == NULL)
	{
		Camera_LoadInto(&app->renderState.camera, shaderMatrix->value.values);
	}
	else
	{
		Camera_LoadInto(&renderTarget->camera, shaderMatrix->value.values);
	}
	
	// Activate shaders
	
	// First the SpriteEffect shader, which we always use
	MOJOSHADER_effectStateChanges stateChanges;
	memset(&stateChanges, 0, sizeof(stateChanges));
	FNA3D_ApplyEffect(app->renderState.device, app->renderState.shaderSpriteEffect.effect, 0, &stateChanges);
	
	// Then, the optional shaders
	// TODO: Swap back & forth between shaders here!
	if(renderTarget != NULL)
	{
		Shader* shader = NULL;
		for(int i = 0; i < renderTarget->shadersCount; i++)
		{
			shader = renderTarget->shaders[i];
			
			if(shader->update != NULL)
			{
				shader->update(app, renderTarget, shader);
			}
			
			if(!shader->disabled)
			{
				FNA3D_ApplyEffect(app->renderState.device, shader->effect, 0, &stateChanges);
			}
		}
	}
}

void RenderTarget_Stop(ApplicationState* app)
{
	SpriteBatch_Flush(&app->renderState);
	
	SpriteBatch_End(&app->renderState.spriteBatch);
}

void RenderTarget_Destroy(RenderTarget* renderTarget, FNA3D_Device* device)
{
	FNA3D_AddDisposeTexture(device, renderTarget->binding.texture); // RenderTarget.texture free
	
	free(renderTarget->shaders); // RenderTarget.shaders free
}
