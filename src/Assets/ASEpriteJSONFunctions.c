#include <stdio.h>
#include <json.h>
#include "ASEpriteJSONFunctions.h"
#include "../Utilities/int2d.h"

ASEpriteJSON ASEpriteJSON_Load(const char* key)
{
	ASEpriteJSON aseprite;
    memset(&aseprite, 0, sizeof(ASEpriteJSON));
    aseprite.key = key;
    
	const char* format = "assets/sprites/%s.json";
    aseprite.filename = malloc(sizeof(char) * (strlen(format) - 2 + 1 + strlen(key)));
    sprintf(aseprite.filename, format, key);
    
    FILE* f;
    char* buffer;
    json_object* parsed_json;
    json_object* meta;
    json_object* animations;
    json_object* frames;
    json_object* obj;
    json_object* objEx;
    json_object* objExEx;
    size_t n_frames, n_anims;
    int2d size = { -1, };
    
    f = fopen(aseprite.filename, "r");
    fseek(f, 0, SEEK_END);
    int length = ftell(f);
    buffer = malloc(length);
    fseek(f, 0, SEEK_SET);
    fread(buffer, length, 1, f);
    fclose(f);
    
    parsed_json = json_tokener_parse(buffer);
    
    json_object_object_get_ex(parsed_json, "meta", &meta);
    json_object_object_get_ex(meta, "frameTags", &animations);
    json_object_object_get_ex(parsed_json, "frames", &frames);
    
    n_frames = json_object_array_length(frames);
    aseprite.frames = malloc(sizeof(Frame) * n_frames);
    aseprite.framesCount = n_frames;
    for(int i = 0; i < n_frames; i++)
    {
        Frame f;
        
        obj = json_object_array_get_idx(frames, i);
        
        json_object_object_get_ex(obj, "duration", &objEx);
        f.duration = json_object_get_int(objEx);
        
        json_object_object_get_ex(obj, "frame", &objEx);
        
        if(size.X == -1)
        {
            json_object_object_get_ex(objEx, "w", &objExEx);
            size.X = json_object_get_int(objExEx);
            json_object_object_get_ex(objEx, "h", &objExEx);
            size.Y = json_object_get_int(objExEx);
        }
        
        json_object_object_get_ex(objEx, "x", &objExEx);
        f.position.X = json_object_get_int(objExEx);
        f.position.X /= size.X;
        
        json_object_object_get_ex(objEx, "y", &objExEx);
        f.position.Y = json_object_get_int(objExEx);
        f.position.Y /= size.Y;
        
        aseprite.frames[i] = f;
    }
    
    n_anims = json_object_array_length(animations);
    aseprite.animations = malloc(sizeof(Animation) * n_anims);
    aseprite.animationsCount = n_anims;
    for(int i = 0; i < n_anims; i++)
    {
        Animation a;
        
        obj = json_object_array_get_idx(animations, i);
        
        json_object_object_get_ex(obj, "direction", &objEx);
        a.direction = json_object_get_string(objEx);
        
        json_object_object_get_ex(obj, "name", &objEx);
        a.name = json_object_get_string(objEx);
        
        json_object_object_get_ex(obj, "from", &objEx);
        a.from = json_object_get_int(objEx);
        
        json_object_object_get_ex(obj, "to", &objEx);
        a.to = json_object_get_int(objEx);
        
        aseprite.animations[i] = a;
    }
	
	return aseprite;
}
