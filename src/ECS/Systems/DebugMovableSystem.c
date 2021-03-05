#include "DebugMovableSystem.h"
#include "../Components/Body.h"
#include "../Components/Renderable.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Input/MouseStateFunctions.h"

static ecs_entity_t dragging;
static float2d diff;

void DebugMovableSystem(ecs_iter_t* it)
{
    fctx();
    
    if(!app->movable || mouse(Released, LEFTCLICK))
    {
        dragging = 0;
        
        return;
    }
    
    Renderable* r = ecs_column(it, Renderable, 1);
    Body* b = ecs_column(it, Body, 2);
    
    if(dragging != 0)
    {
        for(int i = it->count; i >= 0; i--)
        {
            if(dragging != it->entities[i])
            {
                continue;
            }
            
            b->position.X = app->inputManager.mouseState.position.X - diff.X;
            b->position.Y = app->inputManager.mouseState.position.Y - diff.Y;
        }
    }
    else if(mouse(Pressed, LEFTCLICK))
    {
        for(int i = it->count; i >= 0; i--)
        {
            dragging = it->entities[i];
            
            diff = app->inputManager.mouseState.position;
            diff.X -= b->position.X;
            diff.Y -= b->position.Y;
            
            return;
        }
    }
}