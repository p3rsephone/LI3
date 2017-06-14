package engine;

import java.util.Comparator;

public class ContributorComparator implements Comparator<Contributor>{

    /**
     * Compara dois utilizadores consoante o número de contribuições
     * @param a1 Contribuidor 1
     * @param a2 Contribuidor 2
     * @return Contribuidor 1 é maior (-1); Contribuidor 2 é maior (1); São iguais (0);
     */
    public int compare(Contributor c1, Contributor c2){
        if (c1.getCount() > c2.getCount()) return -1;
        if (c1.getCount() < c2.getCount()) return 1;
        return (((Long) c1.getId()).compareTo(c2.getId()));
    }
}
