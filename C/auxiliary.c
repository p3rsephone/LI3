#include "interface.h"
#include "structures.h"
#include <string.h>
#include <stdio.h>

/**
 * [Função de Hash geral]
 * @param  x [Variavel que se vai aplicar a função]
 * @param  N [Tamanho da Hash]
 * @return   [Chave]
 */
int hash(int x, int N){
	return x%N;
}

/**
 * [Retorna o indice a que corresponde um caractér]
 * @param c [Char a analizar]
 * @return  [Índice]
*/
int prefix_idx (char c){
	int idx;
	if (c>=65 && c<=90) idx = c-65;
	else idx = 26;
	return idx;
}

/**
 * [Verifica se o primeiro utilizador tem mais artigos do que o segundo (caso tiverem o mesmo são comparados os ids)]
 * @param  id1    [ID do primeiro utilizador]
 * @param  id2    [ID do segundo utilizador]
 * @param  count1 [Quantia de artigos do primeiro utilizador]
 * @param  count2 [Quantia de artigos do segundo utilizador]
 * @return        [1 ou 0, dependendo se o primeiro utilizador tem ou não mais artigos que o segundo]
 */
int compareUser(long id1, long id2, int count1, int count2){
	if (count1 > count2 || (count1 == count2 && id1 < id2))
		return 1;
	else return 0;
}

/**
 * [Verifica se o titulo de um artigo contém ou não um prefixo]
 * @param  prefix [Prefixo]
 * @param  title  [Titulo de um artigo]
 * @return        [1 ou 0, dependendo se o titulo contém ou não o prefixo]
 */
int compareTitle (char* prefix, char* title){
	int i;
	for(i=0; prefix[i]!='\0'; i++)
		if (prefix[i] != title[i]) return 0;

	return 1;
}

/**
 * [Função de comparação de duas strings]
 * @param  a [Primeira string]
 * @param  b [Primeira string]
 * @return   [1,0 ou -1 dependendo se a primeira string é maior, igual ou menor do que a segunda]
 */
int compareStr (const void *a, const void *b){
	return strcmp(*(char * const *) a, *(char * const *) b);
}


/**
 * [Insere um ID e uma determinada contagem, por ordem crescente, nas suas respetivas listas]
 * @param  id    [ID do utilizador/artigo]
 * @param  count [Contagem que queremos inserir]
 * @param  top   [Lista dos ID's]
 * @param  topC  [Lista da respetiva contagem]
 * @param  N     [Tamanho de ambas as listas]
 */
void insertTop(long id, int count, long top[], int topC[], int N){
	for (; N>0 && compareUser(id, top[N-1], count, topC[N-1]); N--){ // compara o contribuidor novo  com o ultimo contribuidor do array (que é o mais pequeno),
		top[N] = top[N-1]; // se o novo tiver mais counts,
		topC[N] = topC[N-1]; // irá deslocar o elementos do array que sao menores para a direita até colocar o novo no sitio
	}

	top[N] = id;
	topC[N] = count;
}

/**
 * [Inicia 2 arrays com N elementos a 0]
 * @param  array1 [Primeiro array]
 * @param  array2 [Segundo array]
 * @param  N      [Número de elementos de ambos os arrays]
 */
void initArrays(long* array1, int* array2, int N){
	for (N=N-1; N>=0; N--){
		array1[N] = 0;
		array2[N] = 0;
	}
}

/**
 * [Insere um ID e o número de palavras/caracteres nas suas respetivas listas]
 * @param  top  [Lista dos ID's]
 * @param  topC [Lista do número de palavras/caracteres]
 * @param  N    [Tamanho de ambas as listas]
 * @param  flag [Flag que nos indica se se trata do número de palavras (1) ou de caracteres (0)]
 * @param  qs   [Estrutura]
 */
void insertArray(long* top, int* topC, int N, int flag, TAD_istruct qs){
	int i, n = 1, length;
	long id;
	LList *list;
	for (i=0; i<SIZE; i++){
		list = &(qs->data[i].list);
		for (; *list; list = &((*list)->next)){
			id = (*list)->id;
			if (!flag) length = (*list)->length;
			else length = (*list)->lengthW;
			if (compareUser(id, top[n-1], length, topC[n-1])){
				insertTop(id, length, top, topC, n);
				if(n < N) n++;
			}
		}
	}
}