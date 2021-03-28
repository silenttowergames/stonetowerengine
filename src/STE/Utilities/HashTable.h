#pragma once

/*
Copyright 2021 Silent Tower Games LLC

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct HashTable
{
    int length;
    int allocated;
    int* lengths;
    int* allocateds;
    uint64_t* keys;
    void*** entities;
} HashTable;

HashTable HashTable_New(int length);
void HashTable_Expand(HashTable* hashTable, int length);
int HashTable_GetIndex(HashTable* hashTable, uint64_t cell);
int HashTable_Cell_GetIndex(HashTable* hashTable, int cellIndex, void* entity);
void HashTable_Add(HashTable* hashTable, uint64_t cell, void* entity);
void HashTable_Clean(HashTable* hashTable);
uint64_t HashTable_SpatialCellKey(int sizeX, int sizeY, float X, float Y);
void HashTable_Free(HashTable* hashTable);
