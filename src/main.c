#include "StoneTower.h"

void initWorld(ecs_world_t* world)
{
    ECS_COMPONENT(world, AINPC);
    ECS_COMPONENT(world, AIPlayer);
    ECS_COMPONENT(world, Animate);
    ECS_COMPONENT(world, BasicAABB);
    ECS_COMPONENT(world, Body);
    ECS_COMPONENT(world, CameraFollow);
    ECS_COMPONENT(world, Renderable);
    ECS_COMPONENT(world, TileLayerCollides);
    
    ECS_SYSTEM(world, SDLEventsSystem, EcsOnUpdate, 0);
    ECS_SYSTEM(world, EngineUpdateSystem, EcsOnUpdate, 0);
    ECS_SYSTEM(world, AINPCSystem, EcsOnUpdate, AINPC, Body);
    ECS_SYSTEM(world, MoveSystem, EcsOnUpdate, AIPlayer, Body);
    ECS_SYSTEM(world, BasicAABBSystem, EcsOnUpdate, 0);
    ECS_SYSTEM(world, CameraFollowSystem, EcsOnUpdate, Body, CameraFollow);
    ECS_SYSTEM(world, DepthSystem, EcsOnUpdate, Body, Renderable);
    ECS_SYSTEM(world, AnimateSystem, EcsOnUpdate, Animate, Renderable);
    ECS_SYSTEM(world, DrawSystem, EcsOnUpdate, Body, Renderable);
    ECS_SYSTEM(world, FinalizeScreenSystem, EcsOnUpdate, 0);
    
    const EcsQuery* sort = ecs_get(world, DrawSystem, EcsQuery);
	ecs_query_order_by(world, sort->query, ecs_entity(Renderable), SortByLayerThenY);
    
    aabbQuery = ecs_query_new(world, "BasicAABB, Body");
    aabbMapQuery = ecs_query_new(world, "TileLayerCollides, Renderable");
}

void initializeScene(ecs_world_t* world)
{
    ctx();
    
    printf("called initializeScene()\n");
    
    factoryRun(app, "Player", 0, 0, 0, NULL);
    factoryRun(app, "NPC", 32, 0, 0, NULL);
    factoryRun(app, "NPC", 0, 32, 0, NULL);
    factoryRun(app, "NPC", 32, 32, 0, NULL);
}

void init2Scene(ecs_world_t* world)
{
    ctx();
    
    //factoryRun(app, "TextBox", -20, 32, 2, NULL);
    
    for(int x = 0; x < 24; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            factoryRun(app, "NPC", 80 + (x * 12), 80 + (y * 12), 2, NULL);
        }
    }
}

void ShaderUpdate_Disable(void* _app, void* _renderTarget, void* _shader)
{
    sctx();
    
    //shader->disabled = !shader->disabled;
    
    Shader_ParamCopy(shader, "Width", &renderTarget->size.X, sizeof(int));
    Shader_ParamCopy(shader, "Height", &renderTarget->size.Y, sizeof(int));
}

int main(int arcg, char* argv[])
{
    Config config;
    config.size.X = 1280;
    config.size.Y = 720;
    config.fullscreen = false;
    config.language = "en";
    
    init(
        "Engine Test",
        STE_VERSION,
        "OpenGL",
        60,
        config,
        320, 180,
        initWorld,
        "map0",
        RSZ_Floor
    );
    
    scenes(
        3,
        scene(initialize),
        sceneTiled("map1", NULL),
        sceneTiled("map0", init2Scene)
    );
    
    textures(
        2,
        Texture_Create(app.renderState.device, "16x16", 16, 16, 0, 0, 0, 0),
        Texture_Create(app.renderState.device, "8x8", 8, 8, 0, 0, 0, 0)
    );
    
    maps(
        2,
        TiledJSON_Load(&app, "map0"),
        TiledJSON_Load(&app, "map1")
    );
    
    shaders(
        1,
        Shader_Create(app.renderState.device, "CRTShader", ShaderUpdate_Disable)
    );
    
    scripts(
        1,
        LuaScript_Load("test")
    );
    
    sounds(
        4,
        Sound_create_load("calm-example.ogg", Play_Default),
        Sound_create_load("hit.ogg", Play_Default),
        Sound_create_speech("speech0", "This is a test!", Play_Default),
        Sound_create_sfxr("sfxr", Play_Default)
    );
    
    factories(
        3,
        factory(Player),
        factory(NPC),
        factory(TextBox)
    );
    
    renderTargets(
        1,
        RenderTarget_Create(&app, (int2d){ 320, 180, }, (int2d){ 0, 0, }, true, (FNA3D_Vec4){ 1, 0, 1, 1, })
        //RenderTarget_Create(&app, (int2d){ 80, 80, }, (int2d){ 80, -40, }, false, (FNA3D_Vec4){ 0, 1, 0, 1, })
    );
    
    /*
    app.renderState.mainRenderTarget.shadersCount = 1;
    app.renderState.mainRenderTarget.shaders = malloc(sizeof(Shader*) * app.renderState.mainRenderTarget.shadersCount);
    app.renderState.mainRenderTarget.shaders[0] = mapGet(app.assetManager.mapShader, "CRTShader", Shader);
    //*/
    
    loop();
    
    quit();
}
