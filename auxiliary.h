#ifndef AUXILIARY_H
#define AUXILIARY_H

#include "structures.h"
int hash(int x, int N);
int prefix_idx (char c);
int compareUser(long id1, long id2, int count1, int count2);
int compareTitle (char* prefix, char* title);
int compareStr (const void *a, const void *b);
void insertTop(long id, int count, long top[], int topC[], int N);
void initArrays(long* array1, int* array2, int N);
void insertArray(long* top, int* topC, int N, int flag, TAD_istruct qs);

#endif