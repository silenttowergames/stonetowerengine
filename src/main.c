#include "includes.c"

ecs_world_t* createWorld(ApplicationState* app)
{
    ecs_world_t* world = ecs_init(); // flecs.world.create
    
    ecs_set_context(world, app);
    ecs_set_target_fps(world, 1);
    
    ECS_SYSTEM(world, Test1System, EcsOnUpdate);
    
    return world;
}

int main(int arcg, char* argv[])
{
    ApplicationState app = { 0, 0, };
    
    Logger logger = {
        "log.txt",
    };
    
    Logger_Log(&logger, "ERROR", "This is a test error");
    
    ecs_world_t* world;
    
    while(!app.quit)
    {
        world = createWorld(&app);
        
        while(ecs_progress(world, 0))
        {
            if(app.quit)
            {
                app.quit = 0;
                
                app.counter = 0;
                
                break;
            }
        }
        
        ecs_fini(world); // flecs.world.free
    }
    
    return 0;
}
