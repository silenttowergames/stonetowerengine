#include "FontFunctions.h"

Font Font_Create(ApplicationState* app, const char* key)
{
    Font font;
    memset(&font, 0, sizeof(font));
    
    font.key = key;
    
    char* filename = malloc(sizeof(char) * (strlen(key) + 14));
	sprintf(filename, "assets/fonts/%s", key);
    
    font.filename = filename;
    
    font.fonsID = fonsAddFont(app->fons, key, filename);
    
    printf("`%s`: %d\n", filename, font.fonsID);
	
    return font;
}
