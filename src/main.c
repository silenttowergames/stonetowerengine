#include <stdio.h>
#include <flecs.h>

#include "ApplicationState/ApplicationStateInit.h"
#include "ApplicationState/ApplicationStateFunctions.h"
#include "ECS/FlecsFunctions.h"
#include "Utilities/ArrayFunctions.h"

typedef struct myInt
{
    const char* key;
    int value;
} myInt;

int main()
{
    ecs_os_set_api_defaults();
    
    Array array;
    ARRAY_CREATE(array, 5, myInt);
    
    myInt myIntValue = { "one", 1, };
    ARRAY_ADD(array, myInt, myIntValue);
    myIntValue = (myInt){ "two", 2, };
    ARRAY_ADD(array, myInt, myIntValue);
    
    if(array.length < array.allocated)
    {
        myInt* _array = (myInt*)array.data;
        ((myInt*)array.data)[array.length] = myIntValue;
        ecs_map_set(array.map, ((myInt*)array.data)[array.length].key, &((myInt*)array.data)[array.length]);
        array.length++;
    }
    
    printf("%s: %d\n%s: %d\n", ((myInt*)array.data)[0].key, ((myInt*)array.data)[0].value, ((myInt*)array.data)[1].key, ((myInt*)array.data)[1].value);
    
    printf("Flecs\n");
    
    app = ApplicationState_Init();
    app.quit = true;
    
    ecs_world_t* world = NULL;
    
    int i;
    
    do {
        i = 0;
        
        world = Flecs_Init();
        
        while(ecs_progress(world, 0))
        {
            printf("Frame %d\n", i);
            
            if(i >= 3)
            {
                break;
            }
            
            i++;
        }
        
        Flecs_Free(world);
    }
    while(!app.quit);
    
    return 0;
}
