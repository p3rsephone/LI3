#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "interface.h"

#define SIZE 	12007
#define SIZE_C  4049
#define SIZE_T  27

typedef struct linkedList_c{
    long user_id;
    int count;
    char* username;
    struct linkedList_c *next;
}*LList_C;


typedef struct linkedList_r{
	long id;
	char* timestamp;
	struct linkedList_r *next;
}*LList_R;

typedef struct linkedList_t{
	char* title;
	struct linkedList_t *next;
}*LList_T;


typedef struct linkedList{
	long id;
	long lastRevision;
	long length;
	long lengthW;
	char* title;
    LList_R revisions;
	struct linkedList *next;
}*LList;

typedef struct hash{
	LList list;
}HashTable[SIZE];

typedef struct hash_c{
    LList_C list;
}HashTable_C[SIZE_C];


typedef struct titles{
	LList_T list;
} Tab_Titles[SIZE_T];

struct TCD_istruct{
	long numberOfPages;
    long uniques;
	long totalRevisions;
	HashTable data;
    HashTable_C contributors;
    Tab_Titles titles;
    long* top_contributors;
    long* top_largest;
    long* top_words;
    char** prefix;
};

#endif
