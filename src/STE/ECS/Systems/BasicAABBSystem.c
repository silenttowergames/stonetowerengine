#include <math.h>
#include <flecs.h>
#include "BasicAABBSystem.h"
#include "../../Utilities/HashTable.h"

static HashTable hashTable;

void BasicAABBSystem(ecs_iter_t* it)
{
    assert(aabbQuery != NULL);
    assert(aabbMapQuery != NULL);
    
    BasicAABBSystem_FindSolidMapLayer();
    BasicAABBSystem_GetAllEntities();
    BasicAABBSystem_Phase_Broad();
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
    if(aabbItems == NULL)
    {
        HashTable_Free(&hashTable);
        hashTable = HashTable_New(8);
        
        aabbItems = malloc(sizeof(BasicAABBItem) * MAX_SPRITES); // aabbEnitities allocate
    }
    
    ecs_iter_t iter = ecs_query_iter(aabbQuery);
    
    entitiesCount = 0;
    while(ecs_query_next(&iter))
    {
        BasicAABB* basicAABB = ecs_column(&iter, BasicAABB, 1);
        Body* body = ecs_column(&iter, Body, 2);
        
        for(int i = 0; i < iter.count; i++)
        {
            body[i].initialVelocity = body[i].velocity;
            
            aabbItems[entitiesCount] = (BasicAABBItem){
                .entity = iter.entities[i],
                .basicAABB = &basicAABB[i],
                .body = &body[i],
            };
            
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
    
    /*
    if(entitiesCount < MAX_SPRITES)
    {
        aabbEnitities[entitiesCount] = -1;
    }
    //*/
}

static void BasicAABBSystem_Entity_Tilemap(walls wall, BasicAABB* aabb, int h0, Body* body, Renderable* tileMapSolid, Body* tileMapSolidBody, bool isY)
{
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
}

static void BasicAABBSystem_Phase_Broad()
{
    // 1. Fill hash table
    //    a. Math to see how many cells an entity can fit inside
    // 2. Perform narrow X checks on each cell
    //    a. Don't check entity against itself
    // 3. Go through all entities, move on X
    // 4. Perform narrow Y checks on each cell
    // 5. Go through all entities, move on Y
    return;
    for(int i = 0; i < entitiesCount; i++)
    {
        //
    }
}

static void BasicAABBSystem_Phase_Narrow()
{
    // TODO: Hash table. For now it brute-forces
    
    walls w0;
    
    for(int e0 = 0; e0 < entitiesCount; e0++)
    {
        if(aabbItems[e0].basicAABB->hitboxesCount <= 0)
        {
            continue;
        }
        
        for(int isY = 0; isY <= 1; isY++)
        {
            for(int h0 = 0; h0 < aabbItems[e0].basicAABB->hitboxesCount; h0++)
            {
                if(!aabbItems[e0].basicAABB->hitboxes[h0].active)
                {
                    continue;
                }
                
                w0 = Hitbox_GetWalls(&aabbItems[e0].basicAABB->hitboxes[h0], aabbItems[e0].body->position);
                
                // Map collisions
                if(tileMapSolid != NULL)
                {
                    BasicAABBSystem_Entity_Tilemap(w0, aabbItems[e0].basicAABB, h0, aabbItems[e0].body, tileMapSolid, tileMapSolidBody, isY);
                }
                
                // Object collisions
                for(int e1 = 0; e1 < entitiesCount; e1++)
                {
                    if(e0 == e1 || aabbItems[e1].basicAABB->hitboxesCount <= 0)
                    {
                        continue;
                    }
                    
                    for(int h1 = 0; h1 < aabbItems[e1].basicAABB->hitboxesCount; h1++)
                    {
                        if(!aabbItems[e1].basicAABB->hitboxes[h1].active)
                        {
                            continue;
                        }
                        
                        BasicAABB_TryHitboxes(
                            aabbItems[e0].basicAABB,
                            aabbItems[e0].body,
                            &aabbItems[e0].basicAABB->hitboxes[h0],
                            &w0,
                            aabbItems[e1].basicAABB,
                            aabbItems[e1].body,
                            &aabbItems[e1].basicAABB->hitboxes[h1],
                            NULL,
                            isY
                        );
                    }
                }
                
                if(!isY)
                {
                    aabbItems[e0].body->position.X += aabbItems[e0].body->velocity.X;
                    aabbItems[e0].body->effectiveVelocity.X = aabbItems[e0].body->velocity.X;
                }
                else
                {
                    aabbItems[e0].body->position.Y += aabbItems[e0].body->velocity.Y;
                    aabbItems[e0].body->effectiveVelocity.Y = aabbItems[e0].body->velocity.Y;
                }
            }
        }
    }
}

void BasicAABBSystemFree()
{
    HashTable_Free(&hashTable);
    free(aabbItems);
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
