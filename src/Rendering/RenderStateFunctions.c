#include <FNA3D.h>
#include <SDL2/SDL.h>
#include "RenderStateFunctions.h"
#include "SpriteBatchFunctions.h"
#include "../Application/ApplicationState.h"
#include "../Assets/ShaderFunctions.h"

void RenderState_New(ApplicationState* app, int sizeX, int sizeY, int resX, int resY)
{
	memset(&app->renderState, 0, sizeof(RenderState));
	
	app->renderState.size.X = sizeX;
	app->renderState.size.Y = sizeY;
	
	app->renderState.resolution.X = resX;
	app->renderState.resolution.Y = resY;
	
	app->renderState.windowTitle = malloc(sizeof(char) * (strlen(app->gameTitle) + 1 + strlen(app->gameVersion) + 1)); // RenderState.windowTitle.allocate
	sprintf(app->renderState.windowTitle, "%s %s", app->gameTitle, app->gameVersion);
	
	app->renderState.window = SDL_CreateWindow(app->renderState.windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, FNA3D_PrepareWindowAttributes()); // RenderState.window allocate
	
	FNA3D_PresentationParameters presentationParameters;
	memset(&presentationParameters, 0, sizeof(presentationParameters));
	presentationParameters.backBufferWidth = app->renderState.size.X;
	presentationParameters.backBufferHeight = app->renderState.size.Y;
	presentationParameters.deviceWindowHandle = app->renderState.window;
	presentationParameters.backBufferFormat = FNA3D_SURFACEFORMAT_COLOR;
	app->renderState.presentationParameters = presentationParameters;
	
	FNA3D_Viewport viewport;
	memset(&viewport, 0, sizeof(FNA3D_Viewport));
	viewport.w = sizeX;
	viewport.h = sizeY;
	app->renderState.viewport = viewport;
	
	app->renderState.camera = Camera_Create(resX, resY);
	
	app->renderState.device = FNA3D_CreateDevice(&app->renderState.presentationParameters, STE_DEBUG);
	
	app->renderState.shaderSpriteEffect = Shader_Create(app->renderState.device, "SpriteEffect");
	
	app->renderState.vertexBuffer = FNA3D_GenVertexBuffer(app->renderState.device, 1, FNA3D_BUFFERUSAGE_WRITEONLY, MAX_INDICES * sizeof(Vertex)); // RenderState.vertexBuffer allocate
	
	FNA3D_BlendState blendState;
	memset(&blendState, 0, sizeof(blendState));
	blendState.alphaBlendFunction = FNA3D_BLENDFUNCTION_ADD;
	blendState.alphaDestinationBlend = FNA3D_BLEND_INVERSESOURCEALPHA;
	blendState.alphaSourceBlend = FNA3D_BLEND_ONE;
	FNA3D_Color blendFactor = { 0xff, 0xff, 0xff, 0xff };
	blendState.blendFactor = blendFactor;
	blendState.colorBlendFunction = FNA3D_BLENDFUNCTION_ADD;
	blendState.colorDestinationBlend = FNA3D_BLEND_INVERSESOURCEALPHA;
	blendState.colorSourceBlend = FNA3D_BLEND_ONE;
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
	FNA3D_AddDisposeVertexBuffer(renderState->device, renderState->vertexBuffer);
	free(renderState->windowTitle); // RenderState.windowTitle free
	SDL_DestroyWindow(renderState->window); // RenderState.window free
	Shader_Free(&renderState->shaderSpriteEffect);
}
