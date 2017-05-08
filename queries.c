#include "interface.h"
#include "structures.h"
#include "auxiliary.h"
#include <stdlib.h>

/**
 * [Retorna o número de artigos]
 * @param  qs [Estrutura]
 * @return    [Número de artigos]
 */
long all_articles(TAD_istruct qs) {
	return qs->numberOfPages;
}

/**
 * [Retorna o número de artigos únicos]
 * @param  qs [Estrutura]
 * @return    [Número de artigos únicos]
 */
long unique_articles(TAD_istruct qs) {
    return qs->uniques;
}

/**
 * [Retorna o número de revisões]
 * @param  qs [Estrutra]
 * @return    [Número de revisões]
 */
long all_revisions(TAD_istruct qs){
	return qs->totalRevisions;
}

/**
 * [Retorna o nome do artigo dando o ID do mesmo]
 * @param  qs         [Estrutra]
 * @param  article_id [ID do artigo]
 * @return            [Nome do artigo (NULL se não existir)]
 */
char* article_title(long article_id, TAD_istruct qs){
	LList *aux;
    aux = &(qs->data[hash(article_id, SIZE)].list);

	for (;*aux && (*aux)->id > article_id; aux = &((*aux)->next));
	if (*aux && (*aux)->id == article_id)
		return (*aux)->title;
    else return NULL;
}

/**
 * [Retorna o nome do contribuidor dando o ID do mesmo]
 * @param  qs             [Estrutra]
 * @param  contributor_id [ID do artigo]
 * @return                [Nome do contribuidor (NULL se não existir)]
 */
char* contributor_name(long contributor_id, TAD_istruct qs){
	LList_C *aux;
    aux = &(qs->contributors[hash(contributor_id, SIZE_C)].list);

	for (;*aux && (*aux)->user_id > contributor_id; aux = &((*aux)->next));
	if ((*aux) && contributor_id == (*aux)->user_id)
		return (*aux)->username;
    else return NULL;
}

/**
 * [Retorna o timestamp de um artigo dando o seu ID e o ID da revisão]
 * @param  qs          [Estrutra]
 * @param  article_id  [ID do artigo]
 * @param  revision_id [ID da revisão]
 * @return             [Timestamp do artigo (NULL se não existir)]
 */
char* article_timestamp(long article_id, long revision_id, TAD_istruct qs){
	LList* aux;
	aux = &(qs->data[hash(article_id, SIZE)].list);
	for (;*aux && (*aux)->id > article_id; aux = &((*aux)->next));

	if (*aux && article_id == (*aux)->id){
		LList_R *aux_r;
		aux_r = &((*aux)->revisions);
		for (; *aux_r; aux_r = &((*aux_r)->next))
			if ((*aux_r)->id == revision_id)
				return (*aux_r)->timestamp;
	}
	return NULL;
}

/**
 * [Retorna uma lista dos 10 utilizadores com mais contribuições]
 * @param  qs      [Estrutra]
 * @return         [Lista dos 10 utilizadores com mais contribuições]
 */
long* top_10_contributors(TAD_istruct qs){
	if (qs->top_contributors) free(qs->top_contributors);
	int N = 10;
	long *top = (long *) malloc(N * sizeof(long));
	int topC[N];
	int i, n = 1;
	LList_C *list;

	initArrays(top, topC, N);

	for (i=0; i<SIZE_C; i++){
		list = &(qs->contributors[i].list);
		for (; *list; list = &((*list)->next)){
			long id = (*list)->user_id;
			int count = (*list)->count;
			if (compareUser(id, top[n-1], count, topC[n-1])){
				insertTop(id, count, top, topC, n);
				if(n < N) n++;
			}
		}
	}
	qs->top_contributors = top;

	return top;
}

/**
 * [Retorna uma lista de titulos de artigos com um determinado prefixo]
 * @param  prefix  [Prefixo]
 * @param  qs      [Estrutra]
 * @return         [Lista de titulos com um determinado prefixo]
 */
char** titles_with_prefix(char* prefix, TAD_istruct qs){
	if (qs->prefix) free(qs->prefix);
	int indice = prefix_idx(prefix[0]), N=50, i, compare;
	char** titles = (char **) malloc(N * sizeof(char *));
	LList_T *aux;
	aux = &(qs->titles[indice].list);

	for(i=0; *aux; aux = &((*aux)->next)){
		compare = compareTitle(prefix, (*aux)->title);
		if (compare == 1){
			 titles[i] = (*aux)->title;
			 i++;
		}
		if (i == N){
			N *= 2;
			titles = realloc(titles, sizeof(char*) * N);
		}
	}
	titles[i] = NULL;
	qsort(titles,i, sizeof(char*), compareStr);
	qs->prefix = titles;

	return titles;
}

/**
 * [Retorna uma lista dos ID's dos top 20 maiores artigos]
 * @param  qs      [Estrutra]
 * @return         [Lista de ID's dos top 20 maior artigos]
 */
long* top_20_largest_articles(TAD_istruct qs){
	if (qs->top_largest) free(qs->top_largest);
	int N = 20;
	long *top = (long *) malloc(N * sizeof(long));
	int topC[N];

	initArrays(top, topC, N);
	insertArray(top, topC, N, 0, qs);
	qs->top_largest = top;

	return top;
}
/**
 * [Retorna uma lista dos ID's dos top N artigos com mais palavras]
 * @param  qs [Estrutra]
 * @param  N  [Quantidade de artigos desejada]
 * @return    [Lista de ID's dos top N artigos com mais palavras]
 */
long* top_N_articles_with_more_words(int N, TAD_istruct qs){
	if (qs->top_words) free(qs->top_words);
	long *top = (long *) malloc(N * sizeof(long));
	int topC[N];

	initArrays(top, topC, N);
	insertArray(top, topC, N, 1, qs);
	qs->top_words = top;
	return top;
}
