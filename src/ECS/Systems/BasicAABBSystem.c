#include <math.h>
#include <flecs.h>
#include "BasicAABBSystem.h"
#include "../Components/BasicAABB.h"
#include "../Components/Body.h"
#include "../Components/HitboxFunctions.h"
#include "../../Rendering/SpriteBatch.h"
#include "../../Utilities/walls.h"

ecs_query_t* aabbQuery = NULL;
ecs_query_t* aabbMapQuery = NULL;
static ecs_entity_t* aabbEnitities = NULL;
static BasicAABB** aabbBasics = NULL;
static Body** aabbBodies = NULL;
static ecs_map_t* aabbHashTable = NULL;
static int entitiesCount;
static Renderable* tileMapSolid = NULL;

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
    
    ecs_iter_t iter = ecs_query_iter(aabbMapQuery);
    while(ecs_query_next(&iter))
    {
        if(iter.count <= 0)
        {
            return;
        }
        
        tileMapSolid = &ecs_column(&iter, Renderable, 2)[0];
        
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

static void BasicAABBSystem_Phase_Narrow()
{
    // TODO: Hash table. For now it brute-forces
    
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
                            aabbBasics[e1],
                            aabbBodies[e1],
                            &aabbBasics[e1]->hitboxes[h1],
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

void BasicAABBSystemOld(ecs_iter_t* it)
{
    fctx();
    
    ecs_iter_t it0 = ecs_query_iter(aabbQuery);
    ecs_iter_t it1;
    
    while(ecs_query_next(&it0))
    {
        BasicAABB* a0 = ecs_column(&it0, BasicAABB, 1);
        BasicAABB* a1 = NULL;
        
        Body* b0 = ecs_column(&it0, Body, 2);
        Body* b1 = NULL;
        
        Hitbox* hitbox0 = NULL;
        Hitbox* hitbox1 = NULL;
        
        for(int i = 0; i < it0.count; i++)
        {
            if(a0[i].hitboxesCount <= 0)
            {
                continue;
            }
            
            for(int isY = 0; isY <= 1; isY++)
            {
                for(int h0 = 0; h0 < a0[i].hitboxesCount; h0++)
                {
                    hitbox0 = &a0[i].hitboxes[h0];
                    
                    it1 = ecs_query_iter(aabbQuery);
                    
                    while(ecs_query_next(&it1))
                    {
                        a1 = ecs_column(&it1, BasicAABB, 1);
                        b1 = ecs_column(&it1, Body, 2);
                        
                        for(int x = 0; x < it1.count; x++)
                        {
                            // Same entity, skip
                            if(it1.entities[x] == it0.entities[i])
                            {
                                continue;
                            }
                            
                            if(a1[x].hitboxesCount == 0)
                            {
                                continue;
                            }
                            
                            for(int h1 = 0; h1 < a1[x].hitboxesCount; h1++)
                            {
                                hitbox1 = &a1[x].hitboxes[h1];
                                
                                BasicAABB_TryHitboxes(a0, b0, hitbox0, a1, b1, hitbox1, (bool)isY);
                            }
                        }
                    }
                }
                
                if(!isY)
                {
                    b0[i].position.X += b0[i].velocity.X;
                }
                else
                {
                    b0[i].position.Y += b0[i].velocity.Y;
                }
            }
        }
    }
}

static void BasicAABB_TryHitboxes(
    BasicAABB* a0,
    Body* b0,
    Hitbox* hitbox0,
    BasicAABB* a1,
    Body* b1,
    Hitbox* hitbox1,
    bool isY
)
{
    walls w0 = Hitbox_GetWalls(hitbox0, b0);
    walls w1 = Hitbox_GetWalls(hitbox1, b1);
    
    // Horizontal collisions
    if(!isY)
    {
        if(
            (w0.bottom > w1.top && w0.top < w1.bottom)
            ||
            (w0.top < w1.bottom && w0.bottom > w1.bottom)
            ||
            (w0.top >= w1.top && w0.bottom <= w1.bottom)
        )
        {
            if(b0->velocity.X < 0 && w1.right <= w0.left)
            {
                b0->velocity.X = fmin(0, fmax(b0->velocity.X, w1.right - w0.left));
            }
            else if(b0->velocity.X > 0 && w1.left >= w0.right)
            {
                b0->velocity.X = fmax(0, fmin(b0->velocity.X, w1.left - w0.right));
            }
        }
    }
    // Vertical collisions
    else
    {
        if(
            (w0.right > w1.left && w0.left < w1.right)
            ||
            (w0.left < w1.right && w0.right > w1.right)
            ||
            (w0.left >= w1.left && w0.right <= w1.right)
        )
        {
            if(b0->velocity.Y < 0 && w1.bottom <= w0.top)
            {
                b0->velocity.Y = fmin(0, fmax(b0->velocity.Y, w1.bottom - w0.top));
            }
            else if(b0->velocity.Y > 0 && w1.top >= w0.bottom)
            {
                b0->velocity.Y = fmax(0, fmin(b0->velocity.Y, w1.top - w0.bottom));
            }
        }
    }
}
