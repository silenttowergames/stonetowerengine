#pragma once

#include "Menu.h"
#include "../../Application/ApplicationState.h"

typedef struct MenuItem
{
    Menu* menu;
    void (*hovering)(ApplicationState*);
} MenuItem;
