#include "StoneTower.h"
#include "includes_libs.h"
#include "includes_vendor.h"
#include "ecs_declarations.h"
#include "includes.h"

void initWorld(ecs_world_t* world)
{
    ECS_COMPONENT_DEFINE(world, AINPC);
    ECS_COMPONENT_DEFINE(world, AIPlayer);
    ECS_COMPONENT_DEFINE(world, Animate);
    ECS_COMPONENT_DEFINE(world, BasicAABB);
    ECS_COMPONENT_DEFINE(world, Body);
    ECS_COMPONENT_DEFINE(world, CameraFollow);
    ECS_COMPONENT_DEFINE(world, Menu);
    ECS_COMPONENT_DEFINE(world, MenuItem);
    ECS_COMPONENT_DEFINE(world, Renderable);
    ECS_COMPONENT_DEFINE(world, TileLayerCollides);
    
    ECS_SYSTEM(world, EngineUpdateSystem, EcsOnUpdate, 0);
    ECS_SYSTEM(world, AINPCSystem, EcsOnUpdate, AINPC, Body);
    ECS_SYSTEM(world, MoveSystem, EcsOnUpdate, AIPlayer, Body);
    
    BasicAABBSystem_Init();
    
    ECS_SYSTEM(world, MenuSystem, EcsOnUpdate, Menu, :MenuItem);
    ecs_set_component_actions(world, Menu, { .dtor = ecs_dtor(Menu), });
    
    ECS_SYSTEM(world, CameraFollowSystem, EcsOnUpdate, Body, CameraFollow);
    ECS_SYSTEM(world, DepthSystem, EcsOnUpdate, Body, Renderable);
    ECS_SYSTEM(world, AnimateSystem, EcsOnUpdate, Animate, Renderable);
    
    DrawSystem_Init();
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
    
    factoryRun(app, "TextBox", -20, -20, 2, NULL);
    
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            factoryRun(app, "NPC", 80 + (x * 12), 80 + (y * 12), 2, NULL);
        }
    }
    
    factoryRun(app, "TestMenu", -120, -40, 1, NULL);
}

void ShaderUpdate_Disable(void* _app, void* _renderTarget, void* _shader)
{
    sctx();
    
    if(key(Pressed, s))
    {
        shader->disabled = !shader->disabled;
    }
    
    Shader_ParamCopy(shader, "Width", &renderTarget->size.X, sizeof(int));
    Shader_ParamCopy(shader, "Height", &renderTarget->size.Y, sizeof(int));
}

int main(int arcg, char* argv[])
{
    configDefault(config, 1280, 720, "en");
    
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
        4,
        scene(initialize),
        sceneTiled("map1", NULL),
        sceneTiled("map0", init2Scene),
        scene(init2)
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
        2,
        LuaScript_Load("test"),
        LuaScript_Load("test2")
    );
    
    fonts(
        2,
        Font_Create(&app, "Bloodyslime/Bloodyslime.ttf"),
        Font_Create(&app, "PressStart2P/PressStart2P.ttf")
    );
    
    sounds(
        4,
        Sound_create_load("calm-example.ogg", Play_StopAll),
        Sound_create_load("hit.ogg", Play_Default),
        Sound_create_speech("speech0", "Uncompromised", Play_Default),
        Sound_create_sfxr("sfxr", Play_Default)
    );
    
    factories(
        4,
        factory(Player),
        factory(NPC),
        factory(TextBox),
        factory(TestMenu)
    );
    
    renderTargets(
        1,
        RenderTarget_Create(&app, (int2d){ 320, 180, }, (int2d){ 0, 0, }, true, (FNA3D_Vec4){ 1, 0, 1, 1, })
        //RenderTarget_Create(&app, (int2d){ 80, 80, }, (int2d){ 80, -40, }, false, (FNA3D_Vec4){ 0, 1, 0, 1, })
    );
    
    //*
    app.renderState.mainRenderTarget.shadersCount = 1;
    app.renderState.mainRenderTarget.shaders = malloc(sizeof(Shader*) * app.renderState.mainRenderTarget.shadersCount);
    app.renderState.mainRenderTarget.shaders[0] = *mapGet(app.assetManager.mapShader, "CRTShader", Shader*);
    //*/
    
    loop();
    
    quit();
}
