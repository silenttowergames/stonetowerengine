#include "StoneTower.h"

void initWorld(ecs_world_t* world)
{
    ECS_COMPONENT(world, AIPlayer);
    ECS_COMPONENT(world, Animate);
    ECS_COMPONENT(world, Body);
    ECS_COMPONENT(world, CameraFollow);
    ECS_COMPONENT(world, Renderable);
    
    ECS_SYSTEM(world, SDLEventsSystem, EcsOnUpdate, 0);
    ECS_SYSTEM(world, EngineUpdateSystem, EcsOnUpdate, 0);
    ECS_SYSTEM(world, MoveSystem, EcsOnUpdate, AIPlayer, Body);
    ECS_SYSTEM(world, CameraFollowSystem, EcsOnUpdate, Body, CameraFollow);
    ECS_SYSTEM(world, DepthSystem, EcsOnUpdate, Body, Renderable);
    ECS_SYSTEM(world, AnimateSystem, EcsOnUpdate, Animate, Renderable);
    ECS_SYSTEM(world, DrawSystem, EcsOnUpdate, Body, Renderable);
    ECS_SYSTEM(world, FinalizeScreenSystem, EcsOnUpdate, 0);
    
    const EcsQuery* sort = ecs_get(world, DrawSystem, EcsQuery);
	ecs_query_order_by(world, sort->query, ecs_entity(Renderable), SortByLayerThenY);
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
    
    factoryRun(app, "TextBox", -20, 32, 2, NULL);
}

void ShaderUpdate_Disable(void* _shader)
{
    sctx();
    
    //shader->disabled = !shader->disabled;
    
    int width = 640;
    int height = 360;
    Shader_ParamCopy(shader, "Width", &width, sizeof(width));
    Shader_ParamCopy(shader, "Height", &height, sizeof(height));
}

int main(int arcg, char* argv[])
{
    const char* keyTest = "This is a test! asdfkljhasdkfj alskdj fa sdflkjasdfklj asdfjk asdflkj asdlj asdflkj asdf";
    uint32_t keyInt = hashlittle(keyTest, strlen(keyTest), 0);
    uint64_t keyDouble = Flecs_Map_Key(keyTest);
    printf("%u\n%u\n", keyInt, keyDouble);
    
    init(
        "Engine Test",
        STONE_TOWER_ENGINE_VERSION,
        "OpenGL",
        60,
        1280, 720,
        320, 180,
        initWorld,
        "map0"
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
    
    factories(
        3,
        factory(Player),
        factory(NPC),
        factory(TextBox)
    );
    
    renderTargets(
        1,
        RenderTarget_Create(app.renderState.device, (int2d){ 320, 180, }, (int2d){ 320, 180, }, (int2d){ 0, 0, })
    );
    
    loop();
    
    quit();
}
