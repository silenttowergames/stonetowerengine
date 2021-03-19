#include "MenuSystem.h"
#include "../Components/Menu.h"
#include "../Components/MenuItem.h"
#include "../Components/Renderable.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Input/KeyboardStateFunctions.h"

void MenuSystem(ecs_iter_t* it)
{
    fctx();
    
    Menu* menu = ecs_column(it, Menu, 1);
    MenuItem* menuItem;
    Renderable* renderable;
    bool out;
    
    for(int i = 0; i < it->count; i++)
    {
        renderable = ecs_get_mut(it->world, it->entities[i], Renderable, &out);
        
        renderable->active = menu[i].active;
        
        if(menu[i].active && menu[i].menuUpdate != NULL)
        {
            menu[i].itemSelected = menu[i].menuUpdate(app, menu[i].itemCount, menu[i].itemSelected);
        }
        
        for(int j = 0; j < menu[i].itemCount; j++)
        {
            menuItem = ecs_get_mut(it->world, menu[i].items[j], MenuItem, &out);
            renderable = ecs_get_mut(it->world, menu[i].items[j], Renderable, &out);
            
            renderable->active = menu[i].active;
            
            if(menu[i].active)
            {
                if(menu[i].itemUpdate != NULL)
                {
                    menu[i].itemUpdate(app, it->entities[i], menu[i].items[j], renderable, menu[i].itemCount, menu[i].itemSelected, j);
                }
                
                if(menu[i].itemSelected == j)
                {
                    if(menuItem->hovering != NULL)
                    {
                        menuItem->hovering(app, menu[i].items[j], menu);
                    }
                    
                    if(menuItem->select != NULL && keys(Pressed, RETURN))
                    {
                        menuItem->select(app, menu[i].items[j], menu);
                    }
                }
            }
            else
            {
                renderable->color = colorU(255, 255, 255, 100);
            }
        }
    }
}
