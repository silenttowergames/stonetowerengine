#include <FNA3D.h>
#include <SDL2/SDL.h>
#include "CameraFunctions.h"
#include "RenderStateFunctions.h"
#include "RenderTargetFunctions.h"
#include "SpriteBatchFunctions.h"
#include "../Application/ApplicationState.h"
#include "../Assets/ShaderFunctions.h"

void RenderState_New(ApplicationState* app, int sizeX, int sizeY, int resX, int resY, RenderState_Zoom windowZoomType)
{
	memset(&app->renderState, 0, sizeof(RenderState));
	
	app->renderState.resolution.X = resX;
	app->renderState.resolution.Y = resY;
	
	app->renderState.windowTitle = malloc(sizeof(char) * (strlen(app->gameTitle) + 1 + strlen(app->gameVersion) + 1)); // RenderState.windowTitle.allocate
	sprintf(app->renderState.windowTitle, "%s %s", app->gameTitle, app->gameVersion);
	
	app->renderState.windowZoomType = windowZoomType;
	
	RenderState_Resize(app, sizeX, sizeY);
	
	FNA3D_BlendState blendState;
	memset(&blendState, 0, sizeof(blendState));
	blendState.alphaBlendFunction = FNA3D_BLENDFUNCTION_ADD;
	blendState.alphaDestinationBlend = FNA3D_BLEND_INVERSESOURCEALPHA;
	blendState.alphaSourceBlend = FNA3D_BLEND_ONE;
	FNA3D_Color blendFactor = { 0xff, 0xff, 0xff, 0xff };
	blendState.blendFactor = blendFactor;
	blendState.colorBlendFunction = FNA3D_BLENDFUNCTION_ADD;
	blendState.colorDestinationBlend = FNA3D_BLEND_INVERSESOURCEALPHA;
	blendState.colorSourceBlend = FNA3D_BLEND_SOURCEALPHA;
	blendState.colorWriteEnable = FNA3D_COLORWRITECHANNELS_ALL;
	blendState.colorWriteEnable1 = FNA3D_COLORWRITECHANNELS_ALL;
	blendState.colorWriteEnable2 = FNA3D_COLORWRITECHANNELS_ALL;
	blendState.colorWriteEnable3 = FNA3D_COLORWRITECHANNELS_ALL;
	blendState.multiSampleMask = -1;
	FNA3D_SetBlendState(app->renderState.device, &blendState);
	
	FNA3D_VertexElement* vertexElements = app->renderState.vertexElements;
	vertexElements[0].offset = 0;
	vertexElements[0].usageIndex = 0;
	vertexElements[0].vertexElementFormat = FNA3D_VERTEXELEMENTFORMAT_VECTOR2;
	vertexElements[0].vertexElementUsage = FNA3D_VERTEXELEMENTUSAGE_POSITION;
	vertexElements[1].offset = sizeof(float) * 2;
	vertexElements[1].usageIndex = 0;
	vertexElements[1].vertexElementFormat = FNA3D_VERTEXELEMENTFORMAT_VECTOR2;
	vertexElements[1].vertexElementUsage = FNA3D_VERTEXELEMENTUSAGE_TEXTURECOORDINATE;
	vertexElements[2].offset = sizeof(float) * 4;
	vertexElements[2].usageIndex = 0;
	vertexElements[2].vertexElementFormat = FNA3D_VERTEXELEMENTFORMAT_COLOR;
	vertexElements[2].vertexElementUsage = FNA3D_VERTEXELEMENTUSAGE_COLOR;
	
	FNA3D_VertexDeclaration vertexDeclaration;
	memset(&vertexDeclaration, 0, sizeof(vertexDeclaration));
	vertexDeclaration.elementCount = 3;
	vertexDeclaration.vertexStride = sizeof(Vertex);
	vertexDeclaration.elements = vertexElements;
	
	app->renderState.vertexBufferBinding.vertexBuffer = app->renderState.vertexBuffer;
	app->renderState.vertexBufferBinding.vertexDeclaration = vertexDeclaration;
	
	SpriteBatch_Create(&app->renderState.spriteBatch);
}

void RenderState_Free(RenderState* renderState)
{
	for(int i = 0; i < renderState->targetsCount; i++)
	{
		RenderTarget_Destroy(&renderState->targets[i], renderState->device);
	}
	
	RenderTarget_Destroy(&renderState->mainRenderTarget, renderState->device);
	
	FNA3D_AddDisposeVertexBuffer(renderState->device, renderState->vertexBuffer); // RenderState.VertexBuffer free
	free(renderState->windowTitle); // RenderState.windowTitle free
	SDL_DestroyWindow(renderState->window); // RenderState.window free
	Shader_Free(renderState->device, &renderState->shaderSpriteEffect);
	FNA3D_DestroyDevice(renderState->device); // RenderState.device free
}

void RenderState_InitRenderTargets(RenderState* renderState, int count)
{
	renderState->targetsCount = count;
	renderState->targetsCountSoFar = 0;
	renderState->targets = malloc(sizeof(RenderTarget) * count);
}

void RenderState_AddRenderTarget(RenderState* renderState, RenderTarget renderTarget)
{
	renderState->targets[renderState->targetsCountSoFar] = renderTarget;
	renderState->targetsCountSoFar++;
}

void RenderState_AddRenderTargets(RenderState* renderState, int count, ...)
{
	va_list args;
	
	va_start(args, count);
	
	for(int i = 0; i < count; i++)
	{
		RenderState_AddRenderTarget(renderState, va_arg(args, RenderTarget));
	}
	
	va_end(args);
}

void RenderState_Resize(ApplicationState* app, int sizeX, int sizeY)
{
	if(app->renderState.window == NULL)
	{
		app->renderState.window = SDL_CreateWindow(app->renderState.windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sizeX, sizeY, FNA3D_PrepareWindowAttributes()); // RenderState.window allocate
		
		app->renderState.camera = Camera_Create(app->renderState.resolution.X, app->renderState.resolution.Y);
	}
	else
	{
		SDL_SetWindowSize(app->renderState.window, sizeX, sizeY);
	}
	
	FNA3D_GetDrawableSize(app->renderState.window, &app->renderState.size.X, &app->renderState.size.Y);
	
	FNA3D_PresentationParameters presentationParameters;
	memset(&presentationParameters, 0, sizeof(presentationParameters));
	presentationParameters.backBufferWidth = app->renderState.size.X;
	presentationParameters.backBufferHeight = app->renderState.size.Y;
	presentationParameters.deviceWindowHandle = app->renderState.window;
	presentationParameters.backBufferFormat = FNA3D_SURFACEFORMAT_COLOR;
	app->renderState.presentationParameters = presentationParameters;
	
	if(app->renderState.device == NULL)
	{
		app->renderState.device = FNA3D_CreateDevice(&app->renderState.presentationParameters, STE_DEBUG); // ApplicationState.RenderState.device allocate
	}
	else
	{
		FNA3D_ResetBackbuffer(app->renderState.device, &app->renderState.presentationParameters);
	}
	
	if(app->renderState.shaderSpriteEffect.effect == NULL)
	{
		app->renderState.shaderSpriteEffect = Shader_Create(app->renderState.device, "SpriteEffect", NULL);
	}
	
	app->renderState.vertexBuffer = FNA3D_GenVertexBuffer(app->renderState.device, 1, FNA3D_BUFFERUSAGE_WRITEONLY, MAX_INDICES * sizeof(Vertex)); // RenderState.vertexBuffer allocate
	
	app->renderState.windowZoom.X = app->renderState.size.X / app->renderState.resolution.X;
	app->renderState.windowZoom.Y = app->renderState.size.Y / app->renderState.resolution.Y;
	
	switch(app->renderState.windowZoomType)
	{
		case RSZ_Floor:
		{
			float windowZoom = fmin(app->renderState.windowZoom.X, app->renderState.windowZoom.Y);
			
			app->renderState.windowZoom.X = windowZoom;
			app->renderState.windowZoom.Y = windowZoom;
			
			break;
		}
		
		case RSZ_Fill:
		{
			float windowZoom = fmin(app->renderState.windowZoom.X, app->renderState.windowZoom.Y);
			
			app->renderState.windowZoom.X = floor(windowZoom);
			app->renderState.windowZoom.Y = floor(windowZoom);
			
			break;
		}
	}
	
	FNA3D_Viewport viewport;
	memset(&viewport, 0, sizeof(FNA3D_Viewport));
	viewport.w = app->renderState.resolution.X * app->renderState.windowZoom.X;
	viewport.h = app->renderState.resolution.Y * app->renderState.windowZoom.Y;
	viewport.x = (app->renderState.size.X - viewport.w) / 2;
	viewport.y = (app->renderState.size.Y - viewport.h) / 2;
	app->renderState.viewport = viewport;
	
	if(app->renderState.mainRenderTarget.texture.asset != NULL)
	{
		app->renderState.mainRenderTarget = RenderTarget_Refresh(app, &app->renderState.mainRenderTarget);
	}
	else
	{
		app->renderState.mainRenderTarget = RenderTarget_Create(app, app->renderState.resolution, (int2d){ 0, 0, }, true, (FNA3D_Vec4){ 0, 0, 0, 1, });
	}
	
	app->renderState.currentRenderTargetID = -1;
	
	if(app->renderState.targets != NULL)
	{
		for(int i = 0; i < app->renderState.targetsCount; i++)
		{
			app->renderState.targets[i] = RenderTarget_Refresh(app, &app->renderState.targets[i]);
		}
	}
}
