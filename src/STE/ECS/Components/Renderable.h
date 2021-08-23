#pragma once

#include <flecs.h>
#include "../../Application/ApplicationState.h"
#include "../../Assets/Texture.h"
#include "../../Rendering/Camera.h"
#include "../../Rendering/SpriteBatch.h"
#include "../../Utilities/float2d.h"
#include "../../Utilities/int2d.h"

typedef struct Renderable
{
	Texture* texture;
	int2d frame;
	float2d offset;
	float2d scale;
	bool flipX;
	bool flipY;
	float rotation;
	void* data;
	void (*render)(ApplicationState*, SpriteBatch*, Camera*, void*, float2d);
	int layer;
	float depth;
	float parallax;
	uint32_t color;
	float2d (*renderOffset)(int, int);
	int duration;
	int renderTargetID;
	bool active;
} Renderable;

#define RenderableBox(width, height, color, layer, depth, parallax, renTarID) \
{\
	NULL,\
	{ 0, 0, },\
	{ 0, 0, },\
	{ width, height, },\
	false,\
	false,\
	0.0f,\
	NULL,\
	Renderable_Box_Render,\
	layer,\
	depth,\
	parallax,\
	color,\
	NULL,\
	0,\
	renTarID,\
	true,\
}

#define RenderableSprite(tex, frame, layer, depth, parallax, color, renTarID) \
{\
	tex,\
	frame,\
	{ 0, 0, },\
	{ 1, 1, },\
	false,\
	false,\
	0.0f,\
	NULL,\
	Renderable_Sprite_Render,\
	layer,\
	depth,\
	parallax,\
	color,\
	NULL,\
	0,\
	renTarID,\
	true,\
}

#define RenderableText(fontName, size, layer, depth, parallax, color, renTarID, string, active) \
{\
	NULL,\
	{ 0, 0, },\
	{ 0, 0, },\
	{ (*mapGet(app->assetManager.mapFont, fontName, Font*))->fonsID, size, },\
	false,\
	false,\
	0.0f,\
	(void*)string,\
	Renderable_TextBox_Render,\
	layer,\
	depth,\
	parallax,\
	color,\
	NULL,\
	0,\
	renTarID,\
	active,\
}
