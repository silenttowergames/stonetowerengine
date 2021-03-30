#include <flecs.h>
#include "../../Application/ApplicationStateFunctions.h"
#include "AnimateSystem.h"

void AnimateSystem(ecs_iter_t* it)
{
    fctx();
	
    Animate* a = ecs_column(it, Animate, 1);
    Renderable* s = ecs_column(it, Renderable, 2);
    bool useAnim = false;
    bool checkAnim = false;
    
    for(int i = 0; i < it->count; i++)
    {
        if(a[i].nextAnimationKey != NULL && (a[i].animation == NULL || strcmp(a[i].nextAnimationKey, a[i].animation->name) != 0))
        {
            useAnim = true;
            checkAnim = true;
            
            for(int j = 0; j < s[i].texture->aseprite.animationsCount; j++)
            {
				if(strcmp(s[i].texture->aseprite.animations[j].name, a[i].nextAnimationKey) != 0)
                {
                    continue;
                }
                
                if(a[i].animation == &s[i].texture->aseprite.animations[j])
                {
                    useAnim = false;
                    
                    break;
                }
                
                a[i].animation = &s[i].texture->aseprite.animations[j];
                
                break;
            }
            
            a[i].nextAnimationKey = NULL;
            
            if(a[i].animation == NULL || !useAnim)
            {
                continue;
            }
            
            a[i].frame = a[i].animation->from;
            a[i].progress = 0;
        }
        else
        {
            a[i].progress += (1000.0 / app->FPS) * a[i].speed;
            
            if(a[i].progress > s[i].texture->aseprite.frames[a[i].frame].duration)
            {
                while(a[i].progress > s[i].texture->aseprite.frames[a[i].frame].duration)
                {
                    a[i].progress -= s[i].texture->aseprite.frames[a[i].frame].duration;
                }
                
                a[i].frame++;
                
                if(a[i].frame > a[i].animation->to)
                {
                    a[i].frame = a[i].animation->from;
                }
            }
        }
        
        s[i].frame = s[i].texture->aseprite.frames[a[i].frame].position;
    }
}
