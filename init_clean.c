#include "interface.h"
#include "structures.h"
#include <stdlib.h>


/** ---- Init ---- */

/**
 * [Inicialização da tabela de Hash geral]
 * @param  h [Tabela de Hash]
 */
void initHash(HashTable h){
    int i;
    for (i=0; i<SIZE; i++)
        h[i].list = NULL;
}

/**
 * [Inicialização da tabela de Hash para os contribuidores]
 * @param  h [Tabela de Hash]
 */
void initHashC(HashTable_C h){
    int i;
    for (i=0; i<SIZE_C; i++)
        h[i].list = NULL;
}

/**
 * [Inicialização da tabela alfabética para os titulos]
 * @param  p [Tabela para os titulos]
 */
void initTabP(Tab_Titles p){
    int i;
    for (i=0; i<SIZE_T; i++)
        p[i].list = NULL;
}

/**
 * [Inicializa a estrutura (alocando memória e colocando valores a zero)]
 * @return [estrura inicializada]
 */
TAD_istruct init(){
	TAD_istruct qs = malloc (sizeof(struct TCD_istruct));
    initHash(qs->data);
    initHashC(qs->contributors);
    initTabP(qs->titles);
    qs->numberOfPages = 0;
    qs->uniques = 0;
	qs->totalRevisions = 0;
	qs->top_contributors = NULL;
	qs->top_largest = NULL;
	qs->top_words = NULL;
	qs->prefix = NULL;

	return qs;
}


/** ---- Clean ---- */

/**
 * [Liberta todas as listas do tipo LList_R]
 * @param  list  [Lista a ser libertada]
 */
void freeListR (LList_R list){
	LList_R aux;

	while (list){
		aux = list;
		list = list->next;
		free(aux->timestamp);
		free(aux);
	}
}

/**
 * [Liberta todas as listas do tipo LList_C]
 * @param  list  [Lista a ser libertada]
 */
void freeListC (LList_C list){
	LList_C aux;

	while (list){
		aux = list;
		list = list->next;
		free(aux->username);
		free(aux);
	}
}

/**
 * [Liberta todas as listas do tipo LList_T]
 * @param list [Lista a ser libertada]
 */
void freeListP(LList_T list){
	LList_T aux;

	while (list){
		aux = list;
		list = list->next;
		free(aux);
	}
}

/**
 * [Liberta todas as listas do tipo LList]
 * @param  list  [Lista a ser libertada]
 */
void freeList (LList list){
	LList aux;

	while (list){
		freeListR(list->revisions);
		aux = list;
		list = list->next;
		free(aux->title);
		free(aux);
	}
}

/**
 * [Liberta uma HashTable]
 * @param h [Tabela de Hash de artigos]
 * @param N [Tamanh]o
 */
void freeHashTable(HashTable h, int N){
	int i;
	for(i=0; i<N; i++)
		if (h[i].list)
			freeList(h[i].list);
}

/**
 * [Liberta uma HashTable_C
 * @param h [Tabela de Hash de contribuidores]
 * @param N [Tamanho]
 */
void freeHashTable_C(HashTable_C h, int N){
	int i;
	for(i=0; i<N; i++)
		if (h[i].list)
			freeListC(h[i].list);
}

/**
 * [Liberta uma Tab_Titles]
 * @param t [Tabela]
 * @param N [Tamanho]
 */
void freeTab(Tab_Titles t, int N){
	int i;
	for(i=0; i<N; i++)
		freeListP(t[i].list);
}

/**
 * [Liberta todos os recursos associados à estrutura TAD_istruct]
 * @param  qs      [Estrutra]
 * @return         [Retorna uma estrutura "limpa", sem nada guardado na memória]
 */
TAD_istruct clean(TAD_istruct qs){
	freeHashTable(qs->data, SIZE);
	freeHashTable_C(qs->contributors, SIZE_C);
	freeTab(qs->titles, SIZE_T);
	free(qs->prefix);
	free(qs->top_contributors);
	free(qs->top_largest);
	free(qs->top_words);
	free(qs); qs = NULL;
	return qs;
}
