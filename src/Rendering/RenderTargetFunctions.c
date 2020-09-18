#include <flecs.h>
#include "RenderTargetFunctions.h"
#include "../Assets/TextureFunctions.h"

void RenderTarget_Create(FNA3D_Device* device, int2d size, int2d position)
{
	RenderTarget renderTarget;
	memset(&renderTarget, 0, sizeof(renderTarget));
	
	Texture texture = Texture_NewBlank(device, size.X, size.Y, 4, true); // RenderTarget.texture allocate
	
	renderTarget.binding.type = FNA3D_RENDERTARGET_TYPE_2D;
	renderTarget.binding.texture = texture.asset;
	
	renderTarget.camera.resolution = size;
	renderTarget.camera.zoom.X = 1.0f;
	renderTarget.camera.zoom.Y = 1.0f;
	
	return renderTarget;
}

void RenderTarget_Destroy(RenderTarget* renderTarget, FNA3D_Device* device)
{
	FNA3D_AddDisposeTexture(device, renderTarget->binding.texture); // RenderTarget.texture free
}
