#pragma once

#include <flecs.h>
#include <json.h>
#include "../Rendering/Animation.h"
#include "../Utilities/int2d.h"

typedef struct ASEpriteJSON
{
	const char* key;
	char* filename;
	int2d size;
    Animation* animations;
    int animationsCount;
    Frame* frames;
    int framesCount;
    bool loaded;
    //
    json_object* parsed_json;
    json_object* meta;
    json_object* animationsJSON;
    json_object* framesJSON;
    json_object* obj;
    json_object* objEx;
    json_object* objExEx;
} ASEpriteJSON;
