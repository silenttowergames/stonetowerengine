#include "StoneTower.h"
#include "includes_libs.h"
#include "includes_vendor.h"
#include "ecs_declarations.h"
#include "includes.h"

// FIXME: DirectX & Vulkan not working
// TODO: UI framework
// TODO: Debug mode in config
// TODO: Dialogue system
// TODO: Hot-reload map (give factories a unique ID based on X, Y, key, prop?)

void initWorld(ecs_world_t* world)
{
    ECS_Setup(DEFINE, world)
    
    ECS_SYSTEM(world, EngineUpdateSystem, EcsOnUpdate, 0);
    ECS_SYSTEM(world, PauseMenuSystem, EcsOnUpdate, Menu, PauseMenu);
    ECS_SYSTEM(world, AINPCSystem, EcsOnUpdate, AINPC, Body);
    ECS_SYSTEM(world, MoveSystem, EcsOnUpdate, AIPlayer, Body);
    
    BasicAABBSystem_Init();
    
    MenuSystem_Init();
    
    ECS_SYSTEM(world, CameraFollowSystem, EcsOnUpdate, Body, CameraFollow, Renderable);
    ECS_SYSTEM(world, DepthSystem, EcsOnUpdate, Body, Renderable);
    ECS_SYSTEM(world, AnimateSystem, EcsOnUpdate, Animate, Renderable);
    
    DrawSystem_Init();
}

void initializeScene(ecs_world_t* world)
{
    ctx();
    
    factoryRun(app, "Player", 0, 0, 0, NULL);
    factoryRun(app, "NPC", 32, 0, 0, NULL);
    factoryRun(app, "NPC", 0, 32, 0, NULL);
    factoryRun(app, "NPC", 32, 32, 0, NULL);
}

void init2Scene(ecs_world_t* world)
{
    ctx();
    
    //factoryRun(app, "TextBox", -20, -20, 2, NULL);
    
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            //factoryRun(app, "NPC", 80 + (x * 12), 80 + (y * 12), 2, NULL);
        }
    }
    
    factoryRun(app, "TestMenu", -120, -40, 5, NULL);
}

void ShaderUpdate_Disable(void* _app, void* _renderTarget, void* _shader)
{
    sctx();
    
    if(keys(Pressed, s))
    {
        shader->disabled = !shader->disabled;
    }
    
    Shader_ParamCopy(shader, "Width", &renderTarget->size.X, sizeof(int));
    Shader_ParamCopy(shader, "Height", &renderTarget->size.Y, sizeof(int));
}

void cmdPlaySound(ApplicationState* app, int argc, char** argv)
{
    for(int i = 0; i < argc; i++)
    {
        soundPlay(argv[i]);
    }
}

void cmdChangeScene(ApplicationState* app, int argc, char** argv)
{
    for(int i = 0; i < argc; i++)
    {
        app->flecsScene = argv[i];
        
        break;
    }
}

int main(int arcg, char* argv[])
{
    ini_t* testINI = ini_load("test.ini");
    
    char* name = (char*)ini_get(testINI, "strings", "Name");
    name[1] = 'l';
    name = (char*)ini_get(testINI, "strings", "Name");
    
    int nOne;
    ini_sget(testINI, "numbers", "Three", "%d", &nOne);
    
    ini_free(testINI);
    
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
    
    // TODO: GameData save & load INI
    char* gameDataFileKey = "save.ini";
    char* gameDataFilename = malloc(sizeof(char) * (strlen(app.savePath) + strlen(gameDataFileKey) + 1));
    sprintf(gameDataFilename, "%s%s", app.savePath, gameDataFileKey);
    GameData gameData = GameData_Create(gameDataFilename);
    gameData.data = malloc(sizeof(GameDataAttribute) * 5);
    gameData.map = ecs_map_new(GameDataAttribute*, 5);
    
    GameDataAttribute* attr;
    
    gameData.data[0] = gdAttr("hello", 5, Int);
    attr = &gameData.data[0];
    mapSet(gameData.map, attr->key, &attr);
    
    gameData.data[1] = gdAttr("hiThere", 7, Int);
    attr = &gameData.data[1];
    mapSet(gameData.map, attr->key, &attr);
    
    gameData.data[2] = gdAttr("alrighty", "Hello, World!", String);
    attr = &gameData.data[0];
    mapSet(gameData.map, attr->key, &attr);
    
    printf("`%s`: %d\n", (*mapGet(gameData.map, "hello", GameDataAttribute*))->key, (*mapGet(gameData.map, "hello", GameDataAttribute*))->valueInt);
    
    FILE* gdINI = fopen("test2.ini", "w");
    char* format;
    char* formatFinal;
    for(int i = 0; i < 3; i++)
    {
        attr = &gameData.data[i];
        
        switch(attr->type)
        {
            case GAMEDATA_Int:
            {
                fprintf(gdINI, "%s = %d\n", attr->key, attr->valueInt);
            } break;
            
            case GAMEDATA_Bool:
            {
                fprintf(gdINI, "%s = %d\n", attr->key, attr->valueBool);
            } break;
            
            case GAMEDATA_Float:
            {
                fprintf(gdINI, "%s = %.*f\n", DBL_DIG - 1, attr->key, attr->valueFloat);
            } break;
            
            case GAMEDATA_String:
            {
                fprintf(gdINI, "%s = \"%s\"\n", attr->key, attr->valueString);
            } break;
        }
    }
    fclose(gdINI);
    
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
    
    app.console.commands = ecs_map_new(ConsoleCommand, 2);
    ConsoleCommand cmd = { "play", cmdPlaySound, };
    mapSet(app.console.commands, "play", &cmd);
    cmd = (ConsoleCommand){ "scene", cmdChangeScene, };
    mapSet(app.console.commands, "scene", &cmd);
    
    loop();
    
    quit();
}
