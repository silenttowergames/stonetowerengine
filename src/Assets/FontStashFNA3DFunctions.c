#include "FontStashFNA3DFunctions.h"
#include "SpriteBatchFunctions.h"
#include "TextureFunctions.h"
#include "../Utilities/float2d.h"
#include "../Utilities/quad.h"

int FontStashFNA3D_RenderCreate(void* uptr, int width, int height)
{
    FontStashFNA3D* fna = (FontStashFNA3D*)uptr;
    
    if(fna->texture.asset != NULL)
    {
        FNA3D_AddDisposeTexture(fna->app->renderState.device, fna->texture.asset);
    }
    
    fna->texture = Texture_NewBlank(fna->app->renderState.device, width, height, 4, false);
    
    fna->texture.size.X = width;
    fna->texture.size.Y = height;
    fna->texture.tilesize.X = width;
    fna->texture.tilesize.Y = height;
    
    return 1;
}

int FontStashFNA3D_RenderResize(void* uptr, int width, int height)
{
    return FontStashFNA3D_RenderCreate(uptr, width, height);
}

void FontStashFNA3D_RenderUpdate(void* uptr, int* rect, const unsigned char* data)
{
    FontStashFNA3D* fna = (FontStashFNA3D*)uptr;
    
    int
        width = fna->texture.size.X,
        height = fna->texture.size.Y,
        size = width * height * sizeof(unsigned char),
        channels = 4
    ;
    
    unsigned char* _data = malloc(size * channels);
    
    for(int i = 0; i < size; i++)
    {
        int val = data[i];
        
        for(int c = 0; c < channels; c++)
        {
            _data[(i * channels) + c] = val;
        }
    }
    
    FNA3D_SetTextureData2D(fna->app->renderState.device, fna->texture.asset, FNA3D_SURFACEFORMAT_COLOR, 0, 0, width, height, 0, _data, size * channels);
}

void FontStashFNA3D_RenderDraw(void* uptr, const float* verts, const float* tcoords, const unsigned int* colors, int nverts)
{
    FontStashFNA3D* fna = (FontStashFNA3D*)uptr;
    quad pos;
    quad src;
    
    for(int i = 0; i < nverts * 2; i += 12)
    {
        SpriteBatch_AddQuad(
            &fna->app->renderState.spriteBatch,
            &fna->app->renderState.camera,
            fna->texture.asset,
            pos,
            src,
            colors[i / 2]
        );
    }
}

void FontStashFNA3D_RenderDelete(void* uptr)
{
    // TODO: FontStashFNA3D_RenderDelete
}

FONScontext* FontStashFNA3D_Create(ApplicationState* app, int width, int height, int flags)
{
    FONSparams params;
    
    FontStashFNA3D* fna = malloc(sizeof(FontStashFNA3D));
    memset(fna, 0, sizeof(FontStashFNA3D));
    
    fna->texture = Texture_NewBlank(fna->app->renderState.device, width, height, 4, false);
    
    memset(&params, 0, sizeof(params));
    params.width = width;
    params.height = height;
    params.flags = (unsigned char)flags;
    params.userPtr = fna;
    params.renderCreate = FontStashFNA3D_RenderCreate;
    params.renderResize = FontStashFNA3D_RenderResize;
    params.renderUpdate = FontStashFNA3D_RenderUpdate;
    params.renderDraw = FontStashFNA3D_RenderDraw;
    params.renderDelete = FontStashFNA3D_RenderDelete;
    
    return fonsCreateInternal(&params);
}
