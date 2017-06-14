#include "structures.h"
#include <stdlib.h>

/**
 * [Criação de uma lista de artigos]
 * @param  l            [Lista pré-existente]
 * @param  id           [ID de um artigo]
 * @param  lastRevision [ID da última revisão]
 * @param  title        [Título do artigo]
 * @return              [Lista atualizada]
 */
LList newLList (LList l, long id, long lastRevision, char* title){
    LList new = malloc (sizeof (struct linkedList));
    new->id = id;
	new->lastRevision = lastRevision;
 	new->title = title;
	new->revisions=NULL;
	new->length = 0;
	new->lengthW = 0;
	new->next = l;
    return new;
}

/**
 * [Criação de uma lista de contribuidores]
 * @param  list     [Lista pré-existente]
 * @param  id       [ID de um contribuidor]
 * @param  username [Nome do contribuidor]
 * @return          [Lista atualizada]
 */
LList_C newLList_c (LList_C *list, long id, char* username){
    LList_C new = malloc (sizeof (struct linkedList_c));
    new->user_id = id;
	new->count = 1;
	new->username = username;
    new->next = *list;
    return new;
}

/**
 * [Criação de uma lista de revisões]
 * @param  revision  [ID de uma revisão]
 * @param  timestamp [Timestamp da revisão]
 * @return           [Lista atualizada]
 */
LList_R newRev (long revision, char* timestamp){
	LList_R new = malloc (sizeof (struct linkedList_r));
	new->id=revision;
	new->timestamp= timestamp;
	new->next=NULL;
	return new;
}

/**
 * [Adição de informação a uma lista de artigos]
 * @param  list         [Lista pré-existente]
 * @param  id           [ID de um artigo]
 * @param  lastRevision [ID da última revisão]
 * @param  title        [Título do artigo]
 * @return 				[Sucesso (1) ou o elemento já existe (0)]
 */
int addData(LList *list, long id, long lastRevision, char* title){
	while (*list && id < (*list)->id)
		list = &((*list)->next);
	if (!(*list) || id != (*list)->id){
		*list = newLList(*list, id, lastRevision, title);
		return 1;
	}
	else return 0;
}

/**
 * [Adição de informação a uma lista de contribuidores]
 * @param  list     [Lista pré-existente]
 * @param  id       [ID de um contribuidor]
 * @param  username [Nome do contribuidor]
 */
void addContributor(LList_C *list, long id, char* username){
	for(;*list && id < (*list)->user_id ; list=&((*list)->next));

	if (!(*list) || (*list)->user_id != id)
		*list=newLList_c(list, id, username);
	else {
		(*list)->count++;
		free(username);
	}
}

/**
 * [Adição de informação a uma lista de revisões e atualiza a lista do artigo]
 * @param  list      [Lista de artigos]
 * @param  id        [ID de um artigo]
 * @param  revision  [ID de uma revisão]
 * @param  timestamp [Timestamp de uma revisão]
 * @param  title     [Título de uma revisão]
 * @return 			 [Sucesso (1) ou a revisão já está atualizada (0)]
 */
int addRev(LList* list, long id, long revision, char* timestamp, char *title){
	while (*list && id < (*list)->id)
			list = &((*list)->next);

	LList_R *aux;
	aux = &(*list)->revisions;
	for (;*aux && (*aux)->id != revision; aux = &((*aux)->next));

	if (!*aux){
		char *aux_title = (*list)->title;
		*aux = newRev(revision, timestamp);
		(*list)->lastRevision = revision;
		(*list)->title = title;
		if (aux_title != title)
			free(aux_title);
		return 1;
	}
	else {
		free(timestamp);
		free(title);
		return 0;
	}
}

/**
 * [Adição de informação a uma lista de titulos]
 * @param  list  [Lista de titulos]
 * @param  title [Titulo de um artigo]
 */
void addTitle(LList_T *list, char* title){
	LList_T aux = (LList_T)malloc(sizeof(struct linkedList_t));
	aux->title = title;
	aux->next = *list;
	*list = aux;
}
