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
    
    factoryRun(app, "TextBox", 0, -20, 5, NULL);
}

int main(int arcg, char* argv[])
{
    init(
        "Engine Test",
        "v1.0.0",
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
    
    factories(
        3,
        factory(Player),
        factory(NPC),
        factory(TextBox)
    );
    
    loop();
    
    quit();
}
