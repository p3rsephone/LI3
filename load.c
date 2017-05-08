#include "interface.h"
#include "auxiliary.h"
#include "add.h"
#include <libxml/parser.h>

/**
 * [Percorrerá a estrutura dos titulos e irá colocar-los na tabela de prexixos consoante a letra que começa]
 * @param qs [Estrutura]
 */
void load_pref(TAD_istruct qs){
	LList *aux;
	int i, indice;
	LList_T aux_p, list;

	for(i=0; i<SIZE_T; qs->titles[i].list = NULL, i++)
		for(list=qs->titles[i].list, aux_p=list; list; list=list->next, aux_p=list, free(aux_p));

	for (i=0; i<SIZE; i++){
		aux = &(qs->data[i].list);
		for(; *aux; aux = &((*aux)->next)){
			indice = prefix_idx((*aux)->title[0]);
			addTitle(&(qs->titles[indice].list), (*aux)->title);
		}
	}
}


/**
 * [Percorre a estrutura do contribuidor, retirando a informação necessária]
 * @param  level4 [Pointer para o contribuidor]
 * @param  doc    [Snapshot]
 * @param  qs     [Estrutura]
 */
void load_contributor(xmlNodePtr level4, TAD_istruct qs) {
	char* username = NULL;
	long id = -1;

	for (; level4; level4 = level4->next){
		if (!xmlStrcmp(level4->name, (const xmlChar *)"username"))
			username = (char *) xmlNodeGetContent(level4);
		
		else if (!xmlStrcmp(level4->name, (const xmlChar *)"id"))
			id = atol((char *) level4->xmlChildrenNode->content);
	}

	if (username && id != -1)
		addContributor(&(qs->contributors[hash(id, SIZE_C)].list), id, username);
}


/**
 * [Percorre o texto de uma revisão, retirando a informação necessária]
 * @param  text [Texto da revisão]
 * @param  id   [ID da revisão]
 * @param  qs   [Estrutura]
 */
void load_text(xmlChar* text, long id, TAD_istruct qs){
	long lengthW = 0;
	int flag = 1;
	xmlChar *s, *aux;
	LList *list;
	list = &(qs->data[hash(id, SIZE)].list);
	while ((*list)->id != id)
		list = &((*list)->next);

	for (s = aux = text; *s;){
		while ((*s == ' ' || *s == '\n' || *s == '\t') && *s){
			s++;
			flag = 1;
		}
		if (flag && *s){
			lengthW++;
			flag = 0;
		}
		while (*s != ' ' && *s != '\n' && *s != '\t' && *s)
			s++;
	}

	if ((*list)->length < s-aux) (*list)->length = s-aux;
	if ((*list)->lengthW < lengthW) (*list)->lengthW = lengthW;
}

/**
 * [Percorre a estrutura da revisão, retirando a informação necessária]
 * @param  level3 [Pointer para a revisão]
 * @param  id     [ID da revisão]
 * @param  doc    [Snapshot]
 * @param  qs     [Estrutura]
 * @param  title  [Título da revisão]
 */
void load_revision(xmlNodePtr level3, long id, TAD_istruct qs, char *title){
	long revision = -1;
	char* timestamp = NULL;
	int sameRevision = -1;
	xmlNodePtr level4_c = NULL, level4_t = NULL;

	for (; level3; level3 = level3->next){
		if (!xmlStrcmp(level3->name, (const xmlChar *)"id"))
			revision = atol((char *) level3->xmlChildrenNode->content);

		else if (!xmlStrcmp(level3->name, (const xmlChar *)"timestamp"))
			timestamp = (char *) xmlNodeGetContent(level3);

		else if (!xmlStrcmp(level3->name, (const xmlChar *)"contributor"))
				level4_c = level3->xmlChildrenNode;

		else if (!xmlStrcmp(level3->name, (const xmlChar *) "text"))
			if (level3->xmlChildrenNode)
				level4_t = level3->xmlChildrenNode;
	}

	if (addRev(&(qs->data[hash(id, SIZE)].list), id, revision, timestamp, title)){
		sameRevision = 0;
		qs->totalRevisions++;
		load_contributor(level4_c, qs);
	}
	else sameRevision = 1;

	if (!sameRevision && level4_t) 
		load_text(level4_t->content, id, qs);
}


/**
 * [Percorre a estrutura da página, retirando a informação necessária]
 * @param  level2 [Pointer para a página]
 * @param  doc    [Snapshot]
 * @param  qs     [Estrutura]
 */
void load_page(xmlNodePtr level2, TAD_istruct qs) {
    long id = -1;
	xmlNodePtr level3 = NULL;
	char *title = NULL;

    for (; level2; level2 = level2->next){
	    if (!xmlStrcmp(level2->name, (const xmlChar *)"id"))
	       	id = atol((char *) level2->xmlChildrenNode->content);

		else if (!xmlStrcmp(level2->name, (const xmlChar *)"title"))
			title = (char *) xmlNodeGetContent(level2);

		else if (!xmlStrcmp(level2->name, (const xmlChar *)"revision"))
			level3 = level2->xmlChildrenNode;
	}

	if (id != -1 && title)
		if (addData(&(qs->data[hash(id, SIZE)].list), id, -1, title))
			qs->uniques++;

	if (level3) load_revision(level3, id, qs, title);
}


/**
 * [Percorre os datasets recebidos, retirando a informação necessária]
 * @param  qs          [Estrutura]
 * @param  nsnaps      [Número de snapshots]
 * @param  snaps_paths [Array com o nome dos snapshots]
 * @return             [Estrutura atualizada]
 */
TAD_istruct load(TAD_istruct qs, int nsnaps, char* snaps_paths[]){
	int i, options, threads = 4;
	if (threads > nsnaps)
		threads = nsnaps;

 	options = XML_PARSE_NOBLANKS | XML_PARSE_COMPACT | XML_PARSE_HUGE;
	
	#pragma omp parallel num_threads(threads)
	{
	 	xmlDocPtr doc;
	 	xmlNodePtr root, level1, level2;

	 	#pragma omp for ordered
	 	for(i=0; i<nsnaps; i++){
	 		doc = xmlReadFile(snaps_paths[i], NULL, options);
	 		#pragma omp ordered
	 		{
	 		root = xmlDocGetRootElement(doc);
	 		level1 = root->xmlChildrenNode;
	 		for (; level1; level1 = level1->next){
	 			if (!xmlStrcmp(level1->name, (const xmlChar *)"page")){
	 				qs->numberOfPages++;
	                level2 = level1->xmlChildrenNode;
	                load_page(level2, qs);
	            }
	        }
	 		xmlFreeDoc(doc);
	 		}
	 	}
	}

 	load_pref(qs);

 	return qs;
}