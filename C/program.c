#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "interface.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

/**
 * [Imprime um array de longs]
 * @param array [Array]
 * @param N     [Tamanho do array]
 */
void printArray(long array[], int N){
    int i;
    for (i=0; i<N; i++)
        printf("%ld -", array[i]);
}

/**
 * [Imprime a ajuda no interpretador]
 */
void printHelp(){
	printf(GRN "Choose a query from 1 - 10. 'q' to exit.\n" RESET);
	printf("->1.........all_articles()\n");
	printf("->2.........unique_articles()\n");
	printf("->3.........all_revisions()\n");
	printf("->4 id......article_title(id)\n");
	printf("->5 id......contributor_name(id)\n");
	printf("->6 id rev..article_timestamp(id, rev)\n");
	printf("->7 p.......titles_with_prefix(p)\n");
	printf("->8.........top_10_contributors()\n");
	printf("->9.........top_20_largest_articles()\n");
	printf("->10 n......top_N_articles_with_more_words(n)\n");
	printf(GRN "Extra options\n" RESET);
	printf("->11........clean and init\n");
	printf("->12 f......load file f\n");
	printf("->13........help\n\n");
}

/**
 * [Responsável pela leitura de comandos]
 * @param argc [Número de argumentos]
 * @param argv [Array com os argumentos]
 */
void interpreter(int argc, char** argv){
	printf(RED "/-/ INTERPRETER MODE ON /-/\n" RESET);

	printf(GRN "Initializing\n" RESET);
	TAD_istruct qs = init();

	if (argc <= 2) printf(RED "Warning " RESET "- No file inserted.\n\n");

	else{
		int i;
		printf(RED "Loading" RESET);
		for (i=2; i<argc; i++)
			printf(" %s", argv[i]);
		printf("\n");
		qs = load(qs, argc-2, argv+2);
	}

	printHelp();

	int i, n, x, s, id, rev;
	char** titles;
	char* file = (char *) malloc (sizeof (char));
	char** files = (char **) malloc (sizeof(char *));
	long* top;
	char command[20];
	char p[20];
	printf(GRN "> " RESET);
	s = scanf("%s", command);
	while (strcmp(command, "q") && strcmp(command, "Q")){
		x = atoi(command);
		switch (x){
			case 1 : printf(RED "All articles : " RESET "%ld\n", all_articles(qs));
					 break;
			case 2 : printf(RED "Unique articles: " RESET "%ld\n", unique_articles(qs));
					 break;
			case 3 : printf(RED "All revisions: " RESET "%ld\n", all_revisions(qs));
					 break;
			case 4 : s = scanf("%d", &id);
					 if (s)
					 	printf(RED "Article %d title: " RESET "%s\n", id, article_title(id, qs));
					 break;
			case 5 : s = scanf("%d", &id);
					 if (s)
					 	printf(RED "Contributor %d name: " RESET "%s\n", id, contributor_name(id, qs));
					 break;
			case 6 : s = scanf("%d", &id);
					 s = s && scanf("%d", &rev);
					 if (s)
					 	printf(RED "Article %d timestamp: " RESET "%s\n", id, article_timestamp(id,rev,qs));
					 break;
			case 7 : s = scanf("%s", p);
					 if (s){
					 	printf(RED "Titles with prefix %s\n" RESET, p);
    					titles = titles_with_prefix(p,qs);
    					for (i=0; titles[i]; i++)
        					printf("%s\n", titles[i]);
        			 }
        			 break;
        	case 8 : printf(RED "Top 10 contributors\n" RESET);
    				 top = top_10_contributors(qs);
    				 for (i=0; i<10; i++)
    					 printf("Id - %ld\tName - %s\n", top[i], contributor_name(top[i], qs));
    				 break;
    		case 9 : printf(RED "Top 20 largest articles\n" RESET);
    				 top = top_20_largest_articles(qs);
    				 for (i=0; i<20; i++)
        				 printf("Id - %ld\tName - %s\n", top[i], article_title(top[i], qs));
        			 break;
        	case 10 : s = scanf("%d", &n);
        			  if (s){
        			  	printf(RED "Top %d articles with more words\n" RESET, n);
    					top = top_N_articles_with_more_words(n, qs);
    				  	for (i=0; i<n; i++)
						printf("Id - %ld\tName - %s\n",top[i], article_title(top[i], qs));
        			  }
        			  break;
			case 11: qs = clean(qs); qs = init(qs);
					 printf(GRN "Clean and Init done.\n" RESET);
					 break;
			case 12: s = scanf("%s", file);
					 if (s){
					 	files[0] = file;
					 	printf(RED "Loading" RESET);
					 	printf(" %s\n", files[0]);
						qs = load(qs, 1, files);
						printf(GRN "Loading Complete\n" RESET);
					 }
					 break;
			case 13: printHelp();
					 break;
			default : printf(RED "Error" RESET " - unknow command. Press 13 for help.\n");
			}

		printf(GRN "> " RESET);
		s = scanf("%s", command);
	}
	printf(RED "Quiting execution\n" RESET);
	if (qs) qs = clean(qs);
}

/**
 * [Irá executar um conjunto pré definido de instruções ou irá chamar a função interpreter]
 * @param argc [Número de argumentos]
 * @param argv [Array com os argumentos]
 * @return      [-]
 */
int main(int argc, char **argv){
    int i;

    if (argc > 1 && !strcmp(argv[1], "-i"))
    	interpreter(argc, argv);

	else{

	printf(RED "Initializing\n" RESET);
	TAD_istruct qs = init();

	printf(RED "Loading" RESET);
	for (i=1; i<argc; i++)
		printf(" %s", argv[i]);
	printf("\n");
	qs = load(qs, argc-1, argv+1);

	printf("\n");
	printf(RED "All articles : " RESET "%ld\n", all_articles(qs));
	printf(RED "Unique articles: " RESET "%ld\n", unique_articles(qs));
	printf(RED "All revisions: " RESET "%ld\n", all_revisions(qs));
	printf(RED "Article %d title: " RESET "%s\n", 25507, article_title(25507, qs));
	printf(RED "Article %d title: " RESET "%s\n", 1111, article_title(1111, qs));
    printf(RED "Article %d title: " RESET "%s\n", 30302, article_title(30302, qs));
    printf(RED "Article %d title: " RESET "%s\n", 987419, article_title(987419, qs));
	printf(RED "Contributor %d name: " RESET "%s\n", 28903366, contributor_name(28903366, qs));
    printf(RED "Contributor %d name: " RESET "%s\n", 194203, contributor_name(194203, qs));
    printf(RED "Contributor %d name: " RESET "%s\n", 1000, contributor_name(1000, qs));
    printf(RED "Article %d timestamp: " RESET "%s\n", 12, article_timestamp(12,763082287,qs));
    printf(RED "Article %d timestamp: " RESET "%s\n", 12, article_timestamp(12,755779730,qs));
    printf(RED "Article %d timestamp: " RESET "%s\n", 12, article_timestamp(12,4479730,qs));

    printf("\n");
    long* top;
    printf(RED "Top 10 contributors\n" RESET);
    top = top_10_contributors(qs);
    for (i=0; i<10; i++)
    	printf("Id - %ld\tName - %s\n", top[i], contributor_name(top[i], qs));

    printf("\n");
    char** titles;
    char* prefix = "Anax";
    printf(RED "Titles with prefix %s\n" RESET, prefix);
    titles = titles_with_prefix(prefix,qs);
    for (i=0; titles[i]; i++)
        printf("%s\n", titles[i]);;

	printf("\n");
    printf(RED "Top 20 largest articles\n" RESET);
    long* topLongest = top_20_largest_articles(qs);
    for (i=0; i<20; i++)
        printf("%ld - ", topLongest[i]);

    printf("\n\n");

    int n = 30;
    printf(RED "Top %d articles with more words\n" RESET, n);
    long* topWords = top_N_articles_with_more_words(n, qs);
    for (i=0; i<n; i++)
        printf("%ld - ", topWords[i]);

    printf("\n");
    qs = clean(qs);
    }
}
