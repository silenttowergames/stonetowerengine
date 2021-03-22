#include "FPSPrintSystem.h"
#include "../../Application/ApplicationStateFunctions.h"

void FPSPrintSystem(ecs_iter_t* it)
{
    fctx();
    
    printf("FPS: %1.5f\n", app->averageFPS);
}
