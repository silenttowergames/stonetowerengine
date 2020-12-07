#include <math.h>
#include <flecs.h>
#include "BasicAABBSystem.h"

void BasicAABBSystem(ecs_iter_t* it)
{
    fctx();
    
    assert(aabbQuery != NULL);
    assert(aabbMapQuery != NULL);
    
    BasicAABBSystem_FindSolidMapLayer();
    BasicAABBSystem_GetAllEntities();
    BasicAABBSystem_Phase_Narrow();
}

static void BasicAABBSystem_FindSolidMapLayer()
{
    tileMapSolid = NULL;
    tileMapSolidBody = NULL;
    
    ecs_iter_t iter = ecs_query_iter(aabbMapQuery);
    while(ecs_query_next(&iter))
    {
        if(iter.count <= 0)
        {
            return;
        }
        
        tileMapSolid = &ecs_column(&iter, Renderable, 2)[0];
        tileMapSolidBody = &ecs_column(&iter, Body, 3)[0];
        
        break;
    }
}

static void BasicAABBSystem_GetAllEntities()
{
    if(aabbEnitities == NULL)
    {
        aabbEnitities = malloc(sizeof(ecs_entity_t) * MAX_SPRITES); // aabbEnitities allocate
        aabbBasics = malloc(sizeof(BasicAABB*) * MAX_SPRITES); // aabbBasics allocate
        aabbBodies = malloc(sizeof(Body*) * MAX_SPRITES); // aabbBodies allocate
    }
    
    ecs_iter_t iter = ecs_query_iter(aabbQuery);
    
    entitiesCount = 0;
    while(ecs_query_next(&iter))
    {
        BasicAABB* basicAABB = ecs_column(&iter, BasicAABB, 1);
        Body* body = ecs_column(&iter, Body, 2);
        
        for(int i = 0; i < iter.count; i++)
        {
            aabbEnitities[entitiesCount] = iter.entities[i];
            aabbBasics[entitiesCount] = &basicAABB[i];
            aabbBodies[entitiesCount] = &body[i];
            
            entitiesCount++;
            
            if(entitiesCount >= MAX_SPRITES)
            {
                break;
            }
        }
        
        if(entitiesCount >= MAX_SPRITES)
        {
            break;
        }
    }
    
    if(entitiesCount < MAX_SPRITES)
    {
        aabbEnitities[entitiesCount] = -1;
    }
}

static void BasicAABBSystem_Entity_Tilemap(walls wall, BasicAABB* aabb, int h0, Body* body, Renderable* tileMapSolid, Body* tileMapSolidBody, bool isY)
{
    //*
    TiledJSONLayer* layer = (TiledJSONLayer*)tileMapSolid->data;
    
    Hitbox tileHitbox = Hitbox_CreateBasic((float2d){
        tileMapSolid->texture->tilesize.X,
        tileMapSolid->texture->tilesize.Y,
    });
    tileHitbox.offset.X = -tileMapSolid->texture->tilesize.X / 2;
    tileHitbox.offset.Y = -tileMapSolid->texture->tilesize.Y / 2;
    
    int index;
    int2d xRange;
    int2d yRange;
    
    xRange.X = wall.left + fmin(body->velocity.X, 0) - tileMapSolidBody->position.X;
    xRange.Y = wall.right + fmax(body->velocity.X, 0) - tileMapSolidBody->position.X;
    
    xRange.X /= tileMapSolid->texture->tilesize.X;
    xRange.X -= 2;
    xRange.Y /= tileMapSolid->texture->tilesize.X;
    xRange.Y += 2;
    
    yRange.X = wall.top + fmin(body->velocity.Y, 0) - tileMapSolidBody->position.Y;
    yRange.Y = wall.bottom + fmax(body->velocity.Y, 0) - tileMapSolidBody->position.Y;
    
    yRange.X /= tileMapSolid->texture->tilesize.Y;
    yRange.X -= 2;
    yRange.Y /= tileMapSolid->texture->tilesize.Y;
    yRange.Y += 2;
    
    for(int Y = yRange.X; Y < yRange.Y; Y++)
    {
        if(Y <= -1)
        {
            Y = -1;
            
            continue;
        }
        
        if(Y >= layer->size.Y)
        {
            break;
        }
        
        for(int X = xRange.X; X < xRange.Y; X++)
        {
            if(X <= -1)
            {
                X = -1;
                
                continue;
            }
            
            if(X >= layer->size.X)
            {
                break;
            }
            
            index = (Y * layer->size.X) + X;
            
            if(layer->tiles[index] == 0)
            {
                continue;
            }
            
            walls w1 = Hitbox_GetWalls(&tileHitbox, (float2d){
                tileMapSolidBody->position.X + (X * tileMapSolid->texture->tilesize.X),
                tileMapSolidBody->position.Y + (Y * tileMapSolid->texture->tilesize.Y),
            });
            
            BasicAABB_TryHitboxes(
                aabb,
                body,
                &aabb->hitboxes[h0],
                &wall,
                NULL,
                NULL,
                &tileHitbox,
                &w1,
                isY
            );
        }
    }
    //*/
}

static void BasicAABBSystem_Phase_Narrow()
{
    // TODO: Hash table. For now it brute-forces
    
    walls w0;
    walls w1;
    
    for(int e0 = 0; e0 < entitiesCount; e0++)
    {
        if(aabbBasics[e0]->hitboxesCount <= 0)
        {
            continue;
        }
        
        for(int isY = 0; isY <= 1; isY++)
        {
            for(int h0 = 0; h0 < aabbBasics[e0]->hitboxesCount; h0++)
            {
                if(!aabbBasics[e0]->hitboxes[h0].active)
                {
                    continue;
                }
                
                w0 = Hitbox_GetWalls(&aabbBasics[e0]->hitboxes[h0], aabbBodies[e0]->position);
                
                // Map collisions
                if(tileMapSolid != NULL)
                {
                    BasicAABBSystem_Entity_Tilemap(w0, aabbBasics[e0], h0, aabbBodies[e0], tileMapSolid, tileMapSolidBody, isY);
                }
                
                // Object collisions
                for(int e1 = 0; e1 < entitiesCount; e1++)
                {
                    if(e0 == e1 || aabbBasics[e1]->hitboxesCount <= 0)
                    {
                        continue;
                    }
                    
                    for(int h1 = 0; h1 < aabbBasics[e1]->hitboxesCount; h1++)
                    {
                        if(!aabbBasics[e1]->hitboxes[h1].active)
                        {
                            continue;
                        }
                        
                        BasicAABB_TryHitboxes(
                            aabbBasics[e0],
                            aabbBodies[e0],
                            &aabbBasics[e0]->hitboxes[h0],
                            &w0,
                            aabbBasics[e1],
                            aabbBodies[e1],
                            &aabbBasics[e1]->hitboxes[h1],
                            NULL,
                            isY
                        );
                    }
                }
                
                if(!isY)
                {
                    aabbBodies[e0]->position.X += aabbBodies[e0]->velocity.X;
                }
                else
                {
                    aabbBodies[e0]->position.Y += aabbBodies[e0]->velocity.Y;
                }
            }
        }
    }
}

void BasicAABBSystemFree()
{
    free(aabbEnitities);
}

static void BasicAABB_TryHitboxes(
    BasicAABB* a0,
    Body* b0,
    Hitbox* hitbox0,
    walls* w0,
    BasicAABB* a1,
    Body* b1,
    Hitbox* hitbox1,
    walls* w1,
    bool isY
)
{
    walls _w0;
    if(w0 == NULL)
    {
        _w0 = Hitbox_GetWalls(hitbox0, b0->position);
        w0 = &_w0;
    }
    
    walls _w1;
    if(w1 == NULL)
    {
        _w1 = Hitbox_GetWalls(hitbox1, b1->position);
        w1 = &_w1;
    }
    
    // Horizontal collisions
    if(!isY)
    {
        if(
            (w0->bottom > w1->top && w0->top < w1->bottom)
            ||
            (w0->top < w1->bottom && w0->bottom > w1->bottom)
            ||
            (w0->top >= w1->top && w0->bottom <= w1->bottom)
        )
        {
            if(hitbox1->solidRight && b0->velocity.X < 0 && w1->right <= w0->left)
            {
                b0->velocity.X = fmin(0, fmax(b0->velocity.X, w1->right - w0->left));
            }
            else if(hitbox1->solidLeft && b0->velocity.X > 0 && w1->left >= w0->right)
            {
                b0->velocity.X = fmax(0, fmin(b0->velocity.X, w1->left - w0->right));
            }
        }
    }
    // Vertical collisions
    else
    {
        if(
            (w0->right > w1->left && w0->left < w1->right)
            ||
            (w0->left < w1->right && w0->right > w1->right)
            ||
            (w0->left >= w1->left && w0->right <= w1->right)
        )
        {
            if(hitbox1->solidBottom && b0->velocity.Y < 0 && w1->bottom <= w0->top)
            {
                b0->velocity.Y = fmin(0, fmax(b0->velocity.Y, w1->bottom - w0->top));
            }
            else if(hitbox1->solidTop && b0->velocity.Y > 0 && w1->top >= w0->bottom)
            {
                b0->velocity.Y = fmax(0, fmin(b0->velocity.Y, w1->top - w0->bottom));
            }
        }
    }
}
