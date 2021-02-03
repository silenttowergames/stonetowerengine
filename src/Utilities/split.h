#pragma once

char** split(const char* phrase, int phraseLength, char delimiter, int* wordCount);
char** split_str(const char* phrase, char delimiter, int* wordCount);
void split_free(char** words, int wordCount);
