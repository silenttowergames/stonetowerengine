#include <json.h>
#include "TiledJSONFunctions.h"
#include "TiledJSONProperty.h"
#include "../ECS/Components/Body.h"
#include "../ECS/Components/RenderableFunctions.h"

TiledJSON TiledJSON_Load(ApplicationState* app, const char* key)
{
    TiledJSON tiled;
    memset(&tiled, 0, sizeof(TiledJSON));
    tiled.key = key;
    
    const char* format = "assets/maps/%s.json";
    tiled.filename = malloc(sizeof(char) * (strlen(format) - 2 + 1 + strlen(key))); // TiledJSON.filename allocate
    sprintf(tiled.filename, format, key);
    
    FILE* f;
    char* buffer;
    json_object* parsed_json;
    json_object* layers;
    json_object* layer;
    json_object* tilesets;
    json_object* obj;
    json_object* objEx;
    
    f = fopen(tiled.filename, "r");
    fseek(f, 0, SEEK_END);
    int length = ftell(f);
    buffer = malloc(length);
    fseek(f, 0, SEEK_SET);
    fread(buffer, length, 1, f);
    fclose(f);
    
    parsed_json = json_tokener_parse(buffer);
    
    json_object_object_get_ex(parsed_json, "tilewidth", &obj);
    tiled.tilesize.X = json_object_get_int(obj);
    
    json_object_object_get_ex(parsed_json, "tileheight", &obj);
    tiled.tilesize.Y = json_object_get_int(obj);
    
    json_object_object_get_ex(parsed_json, "tilesets", &tilesets);
    for(int i = 0; i < json_object_array_length(tilesets); i++)
    {
        // Only supports one tileset!
        
        obj = json_object_array_get_idx(tilesets, i);
        json_object_object_get_ex(obj, "name", &objEx);
        
        const char* texture = json_object_get_string(objEx);
        tiled.texture = mapGet(app->assetManager.mapTexture, texture, Texture);
        
        assert(tiled.texture != NULL);
        
        break;
    }
    
    json_object_object_get_ex(parsed_json, "layers", &layers);
    tiled.layerCount = json_object_array_length(layers);
    
    tiled.layers = malloc(sizeof(TiledJSONLayer) * tiled.layerCount); // TiledJSON.layers allocate
    tiled.layersMap = ecs_map_new(TiledJSONLayer, tiled.layerCount); // TiledJSON.layersMap allocate
    
    for(int i = 0; i < tiled.layerCount; i++)
    {
        TiledJSONLayer tlayer;
        memset(&tlayer, 0, sizeof(TiledJSONLayer));
        
        layer = json_object_array_get_idx(layers, i);
        
        json_object_object_get_ex(layer, "type", &obj);
        tlayer.type = json_object_get_string(obj);
        
        json_object_object_get_ex(layer, "name", &obj);
        tlayer.name = json_object_get_string(obj);
        
        json_object_object_get_ex(layer, "id", &obj);
        tlayer.id = json_object_get_int(obj);
        
        if(strcmp(tlayer.type, "tilelayer") == 0)
        {
            tlayer.objects = NULL;
            
            json_object_object_get_ex(layer, "width", &obj);
            tlayer.size.X = json_object_get_int(obj);
            
            json_object_object_get_ex(layer, "height", &obj);
            tlayer.size.Y = json_object_get_int(obj);
            
            json_object_object_get_ex(layer, "data", &obj);
            tlayer.count = json_object_array_length(obj);
            tlayer.realCount = 0;
            
            tlayer.tiles = malloc(sizeof(int) * tlayer.count); // TiledJSONLayer.tiles allocate
            
            for(int j = 0; j < tlayer.count; j++)
            {
                objEx = json_object_array_get_idx(obj, j);
                tlayer.tiles[j] = json_object_get_int(objEx);
                
                if(tlayer.tiles[j] != 0)
                {
                    tlayer.realCount++;
                }
            }
        }
        else if(strcmp(tlayer.type, "objectgroup") == 0)
        {
            tlayer.tiles = NULL;
            
            json_object_object_get_ex(layer, "objects", &obj);
            tlayer.count = json_object_array_length(obj);
            
            tlayer.objects = malloc(sizeof(TiledJSONObject) * tlayer.count);
            
            for(int j = 0; j < tlayer.count; j++)
            {
                TiledJSONObject object;
                memset(&object, 0, sizeof(TiledJSONObject));
                
                object.layer = i;
                
                json_object* item;
                
                objEx = json_object_array_get_idx(obj, j);
                
                json_object_object_get_ex(objEx, "id", &item);
                object.id = json_object_get_int(item);
                
                json_object_object_get_ex(objEx, "x", &item);
                object.position.X = json_object_get_double(item);
                
                json_object_object_get_ex(objEx, "y", &item);
                object.position.Y = json_object_get_double(item);
                
                json_object_object_get_ex(objEx, "name", &item);
                object.name = json_object_get_string(item);
                
                json_object_object_get_ex(objEx, "type", &item);
                object.type = json_object_get_string(item);
                
                json_object_object_get_ex(objEx, "properties", &item);
                if(item != NULL)
                {
                    json_object* property;
                    json_object* propertyChild;
                    TiledJSONProperty* prop;
                    char* propertyType;
                    
                    object.propertiesCount = json_object_array_length(item);
                    object.propertiesArray = malloc(sizeof(TiledJSONProperty) * object.propertiesCount);
                    object.properties = ecs_map_new(TiledJSONProperty, object.propertiesCount);
                    
                    for(int p = 0; p < object.propertiesCount; p++)
                    {
                        property = json_object_array_get_idx(item, p);
                        
                        prop = &object.propertiesArray[p];
                        memset(prop, 0, sizeof(TiledJSONProperty));
                        
                        json_object_object_get_ex(property, "name", &propertyChild);
                        prop->key = json_object_get_string(propertyChild);
                        
                        json_object_object_get_ex(property, "type", &propertyChild);
                        prop->type = json_object_get_string(propertyChild);
                        
                        json_object_object_get_ex(property, "value", &propertyChild);
                        if(strcmp(prop->type, "string") == 0)
                        {
                            prop->valueString = json_object_get_string(propertyChild);
                        }
                        else if(strcmp(prop->type, "bool") == 0)
                        {
                            prop->valueBool = json_object_get_boolean(propertyChild);
                        }
                        else if(strcmp(prop->type, "int") == 0)
                        {
                            prop->valueInt = json_object_get_int(propertyChild);
                        }
                        else if(strcmp(prop->type, "float") == 0)
                        {
                            prop->valueDouble = json_object_get_double(propertyChild);
                        }
                        
                        mapSet(object.properties, prop->key, prop);
                    }
                }
                
                tlayer.objects[j] = object;
            }
        }
        
        tiled.layers[i] = tlayer;
        
        if(tiled.layers[i].name != NULL)
        {
            mapSet(tiled.layersMap, tiled.layers[i].name, &tiled.layers[i]);
        }
    }
    
    return tiled;
}

void TiledJSON_Build(ApplicationState* app, TiledJSON* tiled)
{
    int layer = 0;
    Factory* factory;
    
    for(int i = 0; i < tiled->layerCount; i++)
    {
        if(strcmp(tiled->layers[i].type, "tilelayer") == 0)
        {
            TiledJSON_Map(app->world, &tiled->layers[i], tiled->texture, layer);
        }
        else if(strcmp(tiled->layers[i].type, "objectgroup") == 0)
        {
            for(int j = 0; j < tiled->layers[i].count; j++)
            {
                if(tiled->layers[i].objects[j].type == NULL || strlen(tiled->layers[i].objects[j].type) == 0)
                {
                    continue;
                }
                
                // TODO: Send properties with factory call
                //ApplicationState_GetFactory(app, tiled->layers[i].objects[j].type, &tiled->layers[i].objects[j]);
                factory = ApplicationState_GetFactory(app, tiled->layers[i].objects[j].type);
                
                if(factory == NULL)
                {
                    continue;
                }
                
                factory->callable(
                    app->world,
                    tiled->layers[i].objects[j].position.X,
                    tiled->layers[i].objects[j].position.Y,
                    layer
                );
            }
        }
        
        layer++;
    }
}

void TiledJSON_Map(ecs_world_t* world, TiledJSONLayer* layer, Texture* texture, int layerID)
{
    if(strcmp(layer->type, "tilelayer") != 0)
    {
        return;
    }
    
    ctx();
    
    ecs_entity_t e = ecs_new(world, 0);
    
    ECS_COMPONENT(world, Body);
    ECS_COMPONENT(world, Renderable);
    
    ecs_set(world, e, Body, {
        { 0, 0, },
    });
    ecs_set(world, e, Renderable, {
        texture,
        { 0, 0, },
        { texture->tilesize.X / 2, texture->tilesize.Y / 2, },
        { 1, 1, },
        false,
        false,
        0,
        (void*)layer,
        Renderable_Tilemap_Render,
        layerID,
        0.0f,
    });
}
