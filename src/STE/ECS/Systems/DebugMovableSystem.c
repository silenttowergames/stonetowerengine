#include "DebugMovableSystem.h"
#include "../Components/Body.h"
#include "../Components/RenderableFunctions.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Input/KeyboardStateFunctions.h"
#include "../../Input/MouseStateFunctions.h"
#include "../../Utilities/quadFunctions.h"

static ecs_entity_t dragging;
static bool camDrag;
static float2d diff;
static quad pos;
static float temp;

void DebugMovableSystem(ecs_iter_t* it)
{
    fctx();
    
    if(!app->movable)
    {
        dragging = 0;
        
        return;
    }
    
    Renderable* r = ecs_column(it, Renderable, 1);
    Body* b = ecs_column(it, Body, 2);
    
    if(dragging == 0 && !camDrag)
    {
        if(mouse(Down, LEFTCLICK))
        {
            for(int i = it->count; i >= 0; i--)
            {
                if(!r[i].active || r[i].render != Renderable_Sprite_Render)
                {
                    continue;
                }
                
                pos = Renderable_Sprite_GetPosQuad(&r[i], b[i].position);
                
                if(
                    app->renderState.targets[i].mouse.X < pos.topLeft.X
                    ||
                    app->renderState.targets[i].mouse.X > pos.bottomRight.X
                    ||
                    app->renderState.targets[i].mouse.Y < pos.bottomLeft.Y
                    ||
                    app->renderState.targets[i].mouse.Y > pos.topRight.Y
                )
                {
                    continue;
                }
                
                dragging = it->entities[i];
                
                diff = app->inputManager.mouseState.position;
                diff.X -= b[i].position.X;
                diff.Y -= b[i].position.Y;
                
                break;
            }
        }
        else if(mouse(Down, RIGHTCLICK))
        {
            dragging = 0;
            
            camDrag = true;
            
            diff.X = app->inputManager.mouseState.position.X;
            diff.Y = app->inputManager.mouseState.position.Y;
        }
    }
    
    if(dragging > 0)
    {
        if(mouse(Up, LEFTCLICK))
        {
            dragging = 0;
            
            return;
        }
        
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
    
    if(camDrag)
    {
        if(mouse(Up, RIGHTCLICK))
        {
            camDrag = false;
            
            return;
        }
        
        for(int i = app->renderState.targetsCount; i >= 0; i--)
        {
            if(!app->renderState.targets[i].hovered)
            {
                continue;
            }
            
            app->renderState.targets[i].camera.position.X -= app->inputManager.mouseState.position.X - diff.X;
            app->renderState.targets[i].camera.position.Y -= app->inputManager.mouseState.position.Y - diff.Y;
            
            diff.X = app->inputManager.mouseState.position.X;
            diff.Y = app->inputManager.mouseState.position.Y;
            
            return;
        }
    }
}