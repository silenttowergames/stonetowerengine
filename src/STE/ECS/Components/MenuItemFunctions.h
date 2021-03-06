#pragma once

#include "MenuItem.h"

void MenuItem_Select_Test(ApplicationState* app, ecs_entity_t entityID, Menu* menu);

void MenuItem_Select_Disable(ApplicationState* app, ecs_entity_t entityID, Menu* menu);

#define menuItemSetup(menuEntityID, itemFontName, itemFontSize, itemVarName) \
    ecs_entity_t meid = menuEntityID;\
    ecs_entity_t* mitems = itemVarName;\
    const char* miFontName = itemFontName;\
    int miFontSize = itemFontSize;

#define menuItemEasy(menuEntityID, itemVarName, itemCountVarName, renderableValue, itemSelectEvent, itemHoveringEvent) \
    itemVarName[itemCountVarName] = ecs_new(world, 0); \
    ecs_set(world, itemVarName[itemCountVarName], Body, bodyEasy(0, 0)); \
    ecs_set(world, itemVarName[itemCountVarName], Renderable, renderableValue); \
    ecs_set(world, itemVarName[itemCountVarName], MenuItem, { menuEntityID, itemSelectEvent, itemHoveringEvent, }); \
    itemCountVarName++;

#define menuItemSuperEasy(renderableText, itemSelectEvent, itemHoveringEvent) \
    menuItemEasy(\
        meid,\
        mitems,\
        currentItem,\
        RenderableText(\
            miFontName,\
            miFontSize,\
            layer,\
            1,\
            0,\
            colorU(255, 255, 255, 255),\
            0,\
            renderableText,\
            false\
        ),\
        itemSelectEvent,\
        itemHoveringEvent\
    )
