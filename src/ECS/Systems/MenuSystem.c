#include "MenuSystem.h"
#include "../Components/Menu.h"
#include "../Components/MenuItem.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Input/KeyboardStateFunctions.h"

void MenuSystem(ecs_iter_t* it)
{
    fctx();
    
    ECS_COMPONENT(it->world, MenuItem);
    
    Menu* menu = ecs_column(it, Menu, 1);
    MenuItem* menuItem;
    bool out;
    
    for(int i = 0; i < it->count; i++)
    {
        if(menu[i].menuUpdate != NULL)
        {
            menu[i].itemSelected = menu[i].menuUpdate(app, menu[i].itemCount, menu[i].itemSelected);
        }
        
        for(int j = 0; j < menu[i].itemCount; j++)
        {
            menuItem = ecs_get_mut(it->world, menu[i].items[j], MenuItem, &out);
            
            if(menu[i].itemUpdate != NULL)
            {
                menu[i].itemUpdate(app, menu[i].items[j], menu[i].itemCount, menu[i].itemSelected, j);
            }
            
            if(menu[i].itemSelected == j)
            {
                if(menuItem->hovering != NULL)
                {
                    menuItem->hovering(app, menu[i].items[j]);
                }
                
                if(key(Pressed, RETURN) && menuItem->select != NULL)
                {
                    menuItem->select(app, menu[i].items[j]);
                }
            }
        }
    }
}
