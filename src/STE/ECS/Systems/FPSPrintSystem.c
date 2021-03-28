#include "FPSPrintSystem.h"
#include "../../Application/ApplicationStateFunctions.h"

static int counter = -60;

void FPSPrintSystem(ecs_iter_t* it)
{
    fctx();
    
    if(++counter < app->FPS)
    {
        return;
    }
    
    counter = 0;
    
    printf("FPS: %1.5f\n", app->averageFPS);
}
