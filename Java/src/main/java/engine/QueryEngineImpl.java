package engine;

import li3.Interface;
import java.util.*;
import java.io.*;
import javax.xml.stream.*;
import java.util.stream.Collectors;


import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;


public class QueryEngineImpl implements Interface {
    /*Estrutura*/
	private Structure qs;

    /**
     * Método de inicialização da estrutura
     */
    public void init(){
        qs = new Structure();
    }

    /**
     * Carrega toda a informação dos diferentes ficheiros para a estrutura, usando StaX por streams
     * @param nspaps        Número de snapshots
     * @param snap_paths    Nome dos snapshots
     */
    public void load(int nspaps, ArrayList<String> snap_paths){
        for (String snap: snap_paths){
            
            boolean id = false, titl = false, rev = false, ts = false, cont = false, userN = false, id_C = false, new_Rev = false, text = false;
            long id_article  = -1, id_revision = -1, id_cont = -1;
            String content = null, timestamp = null, username = null, title = null;

            try{
                XMLInputFactory input = XMLInputFactory.newInstance();
                input.setProperty(XMLInputFactory.IS_COALESCING, true);
                InputStream stream_input = new FileInputStream(snap);
                XMLStreamReader streamReader = input.createXMLStreamReader(stream_input);

                while(streamReader.hasNext()){

                    streamReader.next();

                    switch(streamReader.getEventType()){
                        /** Caso em que o input encontrado corresponde a um elemento (tag) inicial, na árvore XML,
                         * de acordo com a informação que se pretende obter */
                        case XMLStreamConstants.START_ELEMENT: {
                            /** Encontra o inicio de um artigo ("page")*/
                            if (streamReader.getLocalName().equals("page")) {
                                qs.incrementNumberOfPages();
                            }
                            /** Encontra a tag id do artigo, revisão e/ou contribuidor*/
                            else if (streamReader.getLocalName().equals("id")) {
                                id = true;
                                if (cont) id_C = true;
                            }
                            /** Encontra a tag do titulo*/
                            else if (streamReader.getLocalName().equals("title")) {
                                titl = true;
                            }
                            /** Encontra o inicio de uma revisão*/
                            else if (streamReader.getLocalName().equals("revision")) {
                                rev = true;
                            }
                            /** Encontra um timestamp */
                            else if (streamReader.getLocalName().equals("timestamp")) {
                                ts = true;
                            }
                            /** Encontra a tag de um contribuidor*/
                            else if (streamReader.getLocalName().equals("contributor")) {
                                cont = true;
                            }
                            /** Encontra um username*/
                            else if (streamReader.getLocalName().equals("username")) {
                                userN = true;
                            }
                            /** Encontra um texto de um artigo (contido na sua revisão)*/
                            else if (streamReader.getLocalName().equals("text")){
                                text = true;
                            }
                            break;
                        }
                        /** Caso em que o input encontrado corresponde a um elemento (tag) de texto, na árvore XML,
                         * de acordo com a informação que se pretende obter*/ 
                        case XMLStreamConstants.CHARACTERS:
                            /** Obtem um titulo de um artigp*/
                            if (titl) {
                                content = streamReader.getText();
                                if (!content.equals(""))
                                    title = content;
                                titl = false;
                            }
                            /** Obtem um id de um artigo*/
                            if (id && !rev) {
                                content = streamReader.getText();
                                if (!content.equals("")) {
                                    id_article = Long.parseLong(content);
                                }
                                id = false;
                            }
                            /** Obtem um id de uma revisão*/
                            if (id && rev) {
                                content = streamReader.getText();
                                if (!content.equals("")) {
                                    id_revision = Long.parseLong(content);
                                }
                                id  = false;
                            }
                            /** Obtem um timestamp de uma revisão e adicionar o artigo com as informações obtidas, na estrutura */
                            if (ts){
                                content = streamReader.getText();
                                if (!content.equals("")) {
                                    timestamp = content;
                                    boolean b;
                                    b = qs.addArticle(id_article, title, id_revision, timestamp);
                                    if (b) new_Rev = true;
                                }
                                ts = false;
                            }
                            /** Obtem um username de um contribuidor*/
                            if (userN) {
                                content = streamReader.getText();
                                if (!content.equals(""))
                                    username = content;
                                userN = false;
                            }
                            /** Obtem um id de um contribuidor e adiciona o contribuidor com as informações obtidas, na estrutura*/
                            if (id_C && cont) {
                                content = streamReader.getText();
                                if (!content.equals("")){
                                    id_cont = Long.parseLong(content);
                                    qs.addContributor(id_cont, username, new_Rev);
                                }
                                id_C = false;
                                cont = false;
                                new_Rev = false;
                            }
                            /** Calcula o comprimento e o número dde palavras do texto de um artigo (contido na revisão) 
                             * e atualiza esses valores na estrutura*/ 
                            if (text && rev){
                                content = streamReader.getText();
                                if (!content.equals(""))
                                    qs.updateArticleLength(id_article, content);
                                text = false;
                                rev = false;
                            }
                            break;
                    }
                }
            }
            /** Verifica as excepções*/
            catch (Exception e){
                e.printStackTrace();
            }
        }
        /** Adiciona todos os titulos dos artigos encontrados à estrutura*/
        qs.addTitlesToTable();
    }


    /**
     * Retorna o número de artigos totais
     * @return Artigos totais
     */
    public long all_articles() {
        return qs.getNumberOfPages();
    }


    /**
     * Retorna o número de artigos únicos
     * @return Artigos únicos
     */
    public long unique_articles() {
        return qs.getUniqueArticles();
    }


    /**
     * Retorna o número de revisões
     * @return Número de revisões
     */
    public long all_revisions() {
        return qs.getTotalRevisions();
    }


    /**
     * Retorna um ArrayList com o top (10) maiores contribuidores
     * @return Top contribuidores
     */
    public ArrayList<Long> top_10_contributors() {
        int N = 10, i=0;
        TreeSet<Contributor> tree = new TreeSet<>(new ContributorComparator());
        ArrayList<Long> top = new ArrayList<>(N);

        for (Contributor c: qs.getContributors().values())
            if (i == 0 || (c.getCount()) >= tree.last().getCount()){
                tree.add(c);
                if (i == N) tree.pollLast();
                else i++;
            }

        while (tree.size() > 0)
            top.add(tree.pollFirst().getId());
        return top;
    }

    // Versão com streams
    /*
    public ArrayList<Long> top_10_contributors() {
        int N = 10;
        return qs.getContributors().values().stream()
                                            .sorted(new ContributorComparator())
                                            .limit(N)
                                            .map(c -> c.getId())
                                            .collect(Collectors.toCollection(ArrayList::new));
    }

    /**
     * Retorna o nome do contribuidor com um determinado ID (se existir)
     * @param contributor_id ID do contribuidor a procurar
     * @return Nome do contribuidor ou null se não existir
     */
    public String contributor_name(long contributor_id) {
        String username = null;
        if (qs.getContributors().containsKey(contributor_id))
            username = qs.getContributors().get(contributor_id).getUsername();
        return username;
    }


    /**
     * Retorna um ArrayList com o top (20) maiores artigos (em caracteres)
     * @return Top maiores artigos em caracteres
     */
    public ArrayList<Long> top_20_largest_articles() {
        int N = 20, i=0;
        TreeSet<Article> tree = new TreeSet<>(new ArticleCharsComparator());
        ArrayList<Long> top = new ArrayList<>(N);

        for (Article a: qs.getArticles().values())
            if (i == 0 || a.getLength() >= tree.last().getLength()){
                tree.add(a);
                if (i == N) tree.pollLast();
                else i++;
            }

        while (tree.size() > 0)
            top.add(tree.pollFirst().getId());

        return top;
    }

    //Versão com streams
    /*
    public ArrayList<Long> top_20_largest_articles() {
        int N = 20;
        return qs.getArticles().values().stream()
                                        .sorted(new ArticleCharsComparator())
                                        .limit(N)
                                        .map(art -> art.getId())
                                        .collect(Collectors.toCollection(ArrayList::new));
    }
    */


    /**
     * Retorna o título do artigo com um determinado ID (se existir)
     * @param article_id ID do artigo a procurar
     * @return Título do artigo ou null se não existir
     */
    public String article_title(long article_id) {
        String title = null;
        if (qs.getArticles().containsKey(article_id))
            title = qs.getArticles().get(article_id).getTitle();

        return title;
    }


    /**
     * Retorna o top (N) de artigos com mais palavras
     * @param n Tamanho do top
     * @return  Top maiores artigos em palavras
     */
    public ArrayList<Long> top_N_articles_with_more_words(int N) {
        int i=0;
        TreeSet<Article> tree = new TreeSet<>(new ArticleWordsComparator());
        ArrayList<Long> top = new ArrayList<>(N);

        for (Article a: qs.getArticles().values())
            if (i == 0 || a.getLengthW() >= tree.last().getLengthW()){
                tree.add(a);
                if (i == N) tree.pollLast();
                else i++;
            }

        while (tree.size() > 0)
            top.add(tree.pollFirst().getId());

        return top;
    }

    //Versão com streams
    /*
    public ArrayList<Long> top_N_articles_with_more_words(int N) {
        return qs.getArticles().values().stream()
                                        .sorted(new ArticleWordsComparator())
                                        .limit(N)
                                        .map(art -> art.getId())
                                        .collect(Collectors.toCollection(ArrayList::new));
    }
    */

    /**
     * Retorna um ArrayList com todos os títulos com um determinado prefixo
     * @param prefix Prefixo
     * @return Artigos com o prefixo
     */
    public ArrayList<String> titles_with_prefix(String prefix) {
        TreeSet<String> tree = new TreeSet<>();
        ArrayList<String> prefixedTitles = new ArrayList<String>();
        for (String s: qs.getTitles().get(prefix.charAt(0)))
            if (s.startsWith(prefix))
                tree.add(s);

        while (tree.size() > 0)
            prefixedTitles.add(tree.pollFirst());
        return prefixedTitles;
    }

    //Versão com streams
    /*
    public ArrayList<String> titles_with_prefix(String prefix) {
        return qs.getTitles().get(prefix.charAt(0)).stream()
                                                   .filter( t -> t.startsWith(prefix))
                                                   .sorted()
                                                   .collect(Collectors.toCollection(ArrayList::new));
    }
    */

    /**
     * Retorna a data (timestamp) de uma determinada revisão de um determinado artigo (se existir)
     * @param article_id    ID do artigo
     * @param revision_id   ID da revisão
     * @return  Data da revisão ou null se não existir
     */
    public String article_timestamp(long article_id, long revision_id) {
        String timestamp = null;
        timestamp = qs.getArticles().get(article_id).getRevTimestamp(revision_id);
        return timestamp;
    }

    /**
     * Limpa a estrutura
     */
    public void clean() {
        qs = null;
    }
}