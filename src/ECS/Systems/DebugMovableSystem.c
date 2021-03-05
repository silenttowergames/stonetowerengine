#include "DebugMovableSystem.h"
#include "../Components/Body.h"
#include "../Components/RenderableFunctions.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Input/KeyboardStateFunctions.h"
#include "../../Input/MouseStateFunctions.h"
#include "../../Utilities/quadFunctions.h"

static ecs_entity_t dragging;
static float2d diff;
static float2d mouse;
static quad pos;
static float temp;

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
            
            b[i].position.X = app->inputManager.mouseState.position.X - diff.X;
            b[i].position.Y = app->inputManager.mouseState.position.Y - diff.Y;
            
            if(keys(Down, LSHIFT))
            {
                b[i].position.X = (round((b[i].position.X + 4) / 8) * 8) - 4;
                b[i].position.Y = (round((b[i].position.Y + 4) / 8) * 8) - 4;
            }
        }
    }
    else if(mouse(Pressed, LEFTCLICK))
    {
        for(int i = it->count; i >= 0; i--)
        {
            if(!r[i].active || r[i].render != Renderable_Sprite_Render)
            {
                continue;
            }
            
            mouse = app->inputManager.mouseState.position;
            mouse.X -= (app->renderState.targets[r[i].renderTargetID].camera.resolution.X / 2) - app->renderState.targets[r[i].renderTargetID].camera.position.X;
            mouse.Y -= (app->renderState.targets[r[i].renderTargetID].camera.resolution.Y / 2) - app->renderState.targets[r[i].renderTargetID].camera.position.Y;
            
            pos = Renderable_Sprite_GetPosQuad(&r[i], b[i].position);
            
            if(
                mouse.X < pos.topLeft.X
                ||
                mouse.X > pos.bottomRight.X
                ||
                mouse.Y < pos.bottomLeft.Y
                ||
                mouse.Y > pos.topRight.Y
            )
            {
                continue;
            }
            
            dragging = it->entities[i];
            
            diff = app->inputManager.mouseState.position;
            diff.X -= b[i].position.X;
            diff.Y -= b[i].position.Y;
            
            return;
        }
    }
}
