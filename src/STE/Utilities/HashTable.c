#include "HashTable.h"

/*
Copyright 2021 Silent Tower Games LLC

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

HashTable HashTable_New(int length)
{
    HashTable hashTable;
    memset(&hashTable, 0, sizeof(hashTable));
    
    HashTable_Expand(&hashTable, length);
    
    return hashTable;
}

void HashTable_Expand(HashTable* hashTable, int length)
{
    if(length <= hashTable->length)
    {
        return;
    }
    
    int lengthOld = hashTable->length;
    
    hashTable->allocated = length;
    
    hashTable->keys = realloc(hashTable->keys, sizeof(uint64_t) * hashTable->allocated);
    hashTable->lengths = realloc(hashTable->lengths, sizeof(int) * hashTable->allocated);
    hashTable->allocateds = realloc(hashTable->allocateds, sizeof(int) * hashTable->allocated);
    hashTable->entities = realloc(hashTable->entities, sizeof(void***) * hashTable->allocated);
    
    for(int i = lengthOld; i < length; i++)
    {
        hashTable->keys[i] = UINT64_MAX;
        hashTable->lengths[i] = 0;
        hashTable->allocateds[i] = 0;
        hashTable->entities[i] = NULL;
    }
}

int HashTable_GetIndex(HashTable* hashTable, uint64_t cell)
{
    if(cell == UINT64_MAX)
    {
        return -1;
    }
    
    for(int i = 0; i < hashTable->length; i++)
    {
        if(hashTable->keys[i] == UINT64_MAX || hashTable->keys[i] != cell)
        {
            continue;
        }
        
        return i;
    }
    
    return -1;
}

int HashTable_Cell_GetIndex(HashTable* hashTable, int cellIndex, void* entity)
{
    if(cellIndex >= hashTable->length)
    {
        printf("fail\n");
        return -1;
    }
    
    for(int i = 0; i < hashTable->lengths[cellIndex]; i++)
    {
        if(hashTable->entities[cellIndex][i] != entity)
        {
            continue;
        }
        
        return i;
    }
    
    return -1;
}

void HashTable_Add(HashTable* hashTable, uint64_t cell, void* entity)
{
    assert(hashTable->length <= hashTable->allocated);
    
    int index = HashTable_GetIndex(hashTable, cell);
    
    if(index == -1)
    {
        if(hashTable->length == hashTable->allocated)
        {
            HashTable_Expand(hashTable, hashTable->allocated * 2);
        }
        
        index = hashTable->length;
        
        hashTable->keys[index] = cell;
    }
    
    if(hashTable->entities[index] == NULL)
    {
        // This is a pretty blatant magic number
        hashTable->entities[index] = malloc(sizeof(void*) * 4);
        hashTable->allocateds[index] = 4;
        hashTable->length++;
    }
    
    assert(hashTable->lengths[index] <= hashTable->allocateds[index]);
    
    if(hashTable->lengths[index] == hashTable->allocateds[index])
    {
        // Do the math on allocateds first, then use allocateds. So you don't repeat the same math twice, and so you don't need to possiby change it in two spots
        hashTable->allocateds[index] *= 2;
        hashTable->entities[index] = realloc(hashTable->entities[index], sizeof(void**) * hashTable->allocateds[index]);
    }
    
    hashTable->entities[index][hashTable->lengths[index]] = entity;
    hashTable->lengths[index]++;
}

void HashTable_Clean(HashTable* hashTable)
{
    memset(hashTable->lengths, 0, sizeof(int) * hashTable->length);
}

uint64_t HashTable_SpatialCellKey(int sizeX, int sizeY, float X, float Y)
{
    uint64_t uX = (int)floorf(X / sizeX);
    uint64_t uY = (int)floorf(Y / sizeY);
    
    return uX + (uY << 32);
}

void HashTable_Free(HashTable* hashTable)
{
    free(hashTable->allocateds);
    free(hashTable->entities);
    free(hashTable->keys);
    free(hashTable->lengths);
}
