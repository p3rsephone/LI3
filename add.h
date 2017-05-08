#ifndef ADD_H
#define ADD_H

#include "structures.h"
LList newLList (LList l, long id, long lastRevision, char* title);
LList_C newLList_c (LList_C *list, long id, char* username);
LList_R newRev (long revision, char* timestamp);
int addData(LList *list, long id, long lastRevision, char* title);
void addContributor(LList_C *list, long id, char* username);
int addRev(LList* list, long id, long revision, char* timestamp, char* title);
void addTitle(LList_T *list, char* title);

#endif
