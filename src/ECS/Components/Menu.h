#pragma once

#include <flecs.h>
#include "../../Input/KeyboardStateFunctions.h"
#include "../../Utilities/colorFunctions.h"

typedef struct Menu
{
    ecs_entity_t* items;
    int itemCount;
    int itemSelected;
    // applicationState, entityID, itemCount, itemSelected, itemIndex
    void (*itemUpdate)(ApplicationState*, ecs_entity_t, int, int, int);
    // applicationState, itemCount, itemSelected; returns new value of itemSelected
    int (*menuUpdate)(ApplicationState*, int, int);
} Menu;

int Menu_MenuUpdate_Basic(ApplicationState* app, int itemCount, int itemSelected)
{
    if(key(Held, DOWN))
    {
        itemSelected++;
    }
    
    if(key(Held, UP))
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

void Menu_ItemUpdate_Basic(ApplicationState* app, ecs_entity_t entityID, int itemCount, int itemSelected, int itemIndex)
{
    ECS_COMPONENT(app->world, Body);
    ECS_COMPONENT(app->world, Renderable);
    
    bool out;
    Body* body = ecs_get_mut(app->world, entityID, Body, &out);
    Renderable* renderable = ecs_get_mut(app->world, entityID, Renderable, &out);
    
    uint64_t c;
    
    if(itemSelected == itemIndex)
    {
        c = colorU(255, 0, 0, 255);
    }
    else
    {
        c = colorU(255, 255, 255, 255);
    }
    
    body->position.Y = 10 * itemIndex;
    renderable->color = c;
}

#define menuEasy(itemVarName, itemCountVarName, menuEntityID, count, eventItem, eventMenu) \
    int itemCountVarName = 0; \
    ecs_entity_t* itemVarName = malloc(sizeof(ecs_entity_t*) * count); \
    ecs_set(world, menuEntityID, Menu, { itemVarName, count, 0, eventItem, eventMenu, })
