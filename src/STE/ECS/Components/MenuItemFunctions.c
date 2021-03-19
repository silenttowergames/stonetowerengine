#include "MenuItemFunctions.h"

void MenuItem_Select_Test(ApplicationState* app, ecs_entity_t entityID, Menu* menu)
{
    const Renderable* renderable = ecs_get(app->world, entityID, Renderable);
    
    printf("Menu item selected: %s\n", (char*)renderable->data);
}

void MenuItem_Select_Disable(ApplicationState* app, ecs_entity_t entityID, Menu* menu)
{
    ecs_set_time_scale(app->world, 1);
}