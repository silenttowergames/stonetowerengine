#include "MenuFunctions.h"

int Menu_MenuUpdate_Basic(ApplicationState* app, ecs_world_t* world, int itemCount, int itemSelected)
{
    if(keys(Held, DOWN))
    {
        itemSelected++;
    }
    
    if(keys(Held, UP))
    {
        itemSelected--;
    }
    
    itemSelected %= itemCount;
    
    if(itemSelected < 0)
    {
        itemSelected += itemCount;
    }
    
    return itemSelected;
}

void Menu_ItemUpdate_Basic(ApplicationState* app, ecs_world_t* world, ecs_entity_t menuID, ecs_entity_t itemID, Renderable* renderable, int itemCount, int itemSelected, int itemIndex)
{
    bool out;
    Body* body = ecs_get_mut(world, itemID, Body, &out);
    
    const Body* mBody = ecs_get(world, menuID, Body);
    
    uint64_t c;
    
    if(itemSelected == itemIndex)
    {
        c = colorU(255, 0, 0, 255);
    }
    else
    {
        c = colorU(255, 255, 255, 255);
    }
    
    body->position.X = mBody->position.X;
    body->position.Y = mBody->position.Y + 24 + (10 * itemIndex);
    renderable->color = c;
}
