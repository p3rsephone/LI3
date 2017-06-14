package li3;

import common.MyLog;
import engine.QueryEngineImpl;

import java.util.ArrayList;
import java.util.Arrays;

public class Main {


    public static void main(String[] args){

        /*
            LOG CONFIGURATION
        */
        MyLog log = new MyLog("results");
        MyLog logtime = new MyLog("times");
        /* -------------------------------------------------------------------------------------------*/

        /*
            INIT PHASE
         */
        long beginning = System.currentTimeMillis();
        long before = System.currentTimeMillis();
        Interface qe = new QueryEngineImpl();
        qe.init();
        long after = System.currentTimeMillis();
        logtime.writeLog("INIT -> "+(after-before)+" ms\n");

        /*
            LOAD PHASE
         */
        before = System.currentTimeMillis();
        qe.load(args.length,new ArrayList<String>(Arrays.asList(args)));
        after = System.currentTimeMillis();
        logtime.writeLog("LOAD -> "+(after-before)+" ms\n");

        /*
           Query 1
        */
        before = System.currentTimeMillis();
        long allarticles = qe.all_articles();
        after = System.currentTimeMillis();
        logtime.writeLog("ALL_ARTICLES -> "+(after-before)+" ms\n");
        log.writeLog("all_articles() -> "+allarticles + "\n");

        /*
           Query 2
        */
        before = System.currentTimeMillis();
        long uniquearticles = qe.unique_articles();
        after = System.currentTimeMillis();
        logtime.writeLog("UNIQUE_ARTICLES -> "+(after-before)+" ms\n");
        log.writeLog("unique_articles() -> "+uniquearticles+ "\n");

        /*
           Query 3
        */
        before = System.currentTimeMillis();
        long all_revisions = qe.all_revisions();
        after = System.currentTimeMillis();
        logtime.writeLog("ALL_REVISIONS -> "+(after-before)+" ms\n  ");
        log.writeLog("all_revisions() -> "+all_revisions+ "\n  ");

        /*
           Query 4
        */
        before = System.currentTimeMillis();
        ArrayList<Long> top_10_contrib = qe.top_10_contributors();
        after = System.currentTimeMillis();
        logtime.writeLog("TOP_10_CONTRIBUTORS -> " + (after - before) + " ms\n  ");
        String top_10_contributors = "";
        for(Long l : top_10_contrib) {
            top_10_contributors = top_10_contributors + l + " ";
        }
        log.writeLog("top_10_contributors() -> " + top_10_contributors+ "\n  ");

        /*
           Query 5
        */
        before = System.currentTimeMillis();
        String cname = qe.contributor_name(28903366);
        after = System.currentTimeMillis();
        logtime.writeLog("CONTRIBUTOR_NAME -> "+(after-before)+" ms\n  ");
        log.writeLog("contributor_name(28903366) -> "+cname+ "\n  ");

        /*
           Query 6
        */
        before = System.currentTimeMillis();
        ArrayList<Long> top_20_largest_articles = qe.top_20_largest_articles();
        after = System.currentTimeMillis();
        logtime.writeLog("TOP_20_LARGEST_ARTICLES -> " + (after - before) + " ms\n  ");
        String top_20_larticles = "";
        for(Long l : top_20_largest_articles) {
            top_20_larticles = top_20_larticles + l + " ";
        }
        log.writeLog("top_20_largest_articles() -> " + top_20_larticles+ "\n  ");

        /*
           Query 7
        */
        before = System.currentTimeMillis();
        String atitle = qe.article_title(15910);
        after = System.currentTimeMillis();
        logtime.writeLog("ARTICLE_TITLE -> "+(after-before)+" ms\n  ");
        log.writeLog("article_title(15910) -> "+atitle+ "\n  ");

        /*
           Query 8
        */
        before = System.currentTimeMillis();
        ArrayList<Long> top_n_words = qe.top_N_articles_with_more_words(30);
        after = System.currentTimeMillis();
        logtime.writeLog("TOP_N_ARTICLES_WITH_MORE_WORDS -> " + (after - before) + " ms\n  ");
        String top_n_words_s = "";
        for(Long l : top_n_words) {
            top_n_words_s = top_n_words_s + l + " ";
        }
        log.writeLog("top_N_articles_with_more_words(30) -> " + top_n_words_s+ "\n  ");

        /*
           Query 9
        */
        before = System.currentTimeMillis();
        ArrayList<String> titlespref = qe.titles_with_prefix("Anax");
        after = System.currentTimeMillis();
        logtime.writeLog("TITLES_WITH_PREFIX -> " + (after - before) + " ms\n  ");
        String titlespf = "";
        for(String s : titlespref) {
            titlespf = titlespf + s + " ";
        }
        log.writeLog("titles_with_prefix(Anax) -> " + titlespf+ "\n  ");

        /*
           Query 10
        */
        before = System.currentTimeMillis();
        String atime = qe.article_timestamp(12,763082287);
        after = System.currentTimeMillis();
        logtime.writeLog("ARTICLE_TIMESTAMP -> "+(after-before)+" ms\n  ");
        log.writeLog("article_timestamp(12,763082287) -> "+atime+ "\n  ");

        /*
            CLEAN PHASE
         */
        before = System.currentTimeMillis();
        qe.clean();
        after = System.currentTimeMillis();
        logtime.writeLog("CLEAN -> "+(after-before)+" ms\n  ");
        long end = System.currentTimeMillis();
        logtime.writeLog("COMPLETE TIME -> "+(end-beginning)+" ms\n  ");
    }

}
