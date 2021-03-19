#include "PauseMenuSystem.h"
#include "../Components/Menu.h"
#include "../Components/PauseMenu.h"

void PauseMenuSystem(ecs_iter_t* it)
{
    Menu* menu = ecs_column(it, Menu, 1);
    PauseMenu* pauseMenu = ecs_column(it, PauseMenu, 2);
    
    for(int i = 0; i < it->count; i++)
    {
        if(!pauseMenu[i].active)
        {
            continue;
        }
        
        menu->active = it->delta_time == 0;
    }
}
