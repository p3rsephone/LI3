package engine;

import java.util.Comparator;

public class ArticleWordsComparator implements Comparator<Article>{

    /**
     * Compara dois artigos consoante o número de palavras
     * @param a1 Artigo 1
     * @param a2 Artigo 2
     * @return Artigo 1 é maior (-1); Artigo 2 é maior (1); São iguais (0);
     */
    public int compare(Article a1, Article a2){
        if (a1.getLengthW() > a2.getLengthW()) return -1;
        if (a1.getLengthW() < a2.getLengthW()) return 1;
        return (((Long) a1.getId()).compareTo(a2.getId()));
    }
}
