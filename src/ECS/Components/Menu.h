#pragma once

#include <flecs.h>
#include "../../Input/KeyboardStateFunctions.h"
#include "../../Utilities/colorFunctions.h"

typedef struct Menu
{
    ecs_entity_t* items;
    int itemCount;
    int itemSelected;
    // applicationState, menuID, itemID, renderable, itemCount, itemSelected, itemIndex
    void (*itemUpdate)(ApplicationState*, ecs_entity_t, ecs_entity_t, Renderable*, int, int, int);
    // applicationState, itemCount, itemSelected; returns new value of itemSelected
    int (*menuUpdate)(ApplicationState*, int, int);
    bool active;
} Menu;

int Menu_MenuUpdate_Basic(ApplicationState* app, int itemCount, int itemSelected)
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

void Menu_ItemUpdate_Basic(ApplicationState* app, ecs_entity_t menuID, ecs_entity_t itemID, Renderable* renderable, int itemCount, int itemSelected, int itemIndex)
{
    bool out;
    Body* body = ecs_get_mut(app->world, itemID, Body, &out);
    
    const Body* mBody = ecs_get(app->world, menuID, Body);
    
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

ECS_DTOR(Menu, ptr, {
    free(ptr->items); // MenuItem* free
})

#define menuEasy(itemVarName, itemCountVarName, menuEntityID, count, eventItem, eventMenu, active) \
    int itemCountVarName = 0; \
    ecs_entity_t* itemVarName = malloc(sizeof(ecs_entity_t*) * count); \
    ecs_set(world, menuEntityID, Menu, { itemVarName, count, 0, eventItem, eventMenu, active, })
