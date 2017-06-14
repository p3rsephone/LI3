package engine;

import java.util.ArrayList;
import java.util.HashMap;
import java.lang.String;


public class Structure {
    private long numberOfPages; ///< Número de artigos total
    private long uniqueArticles; ///< Número de artigos únicos
    private long totalRevisions;  ///< Número de revisões diferentes
    private HashMap<Long, Article> articles; ///< Tabela de Hash com os artigos
    private HashMap<Long, Contributor> contributors; ///< Tabela de Hash com os contribuidores
    private HashMap<Character, ArrayList<String>> titles; ///< Tabela com os títulos

    /**
     * Inicializa a estrutura
     */
    public Structure(){
        numberOfPages = 0;
        uniqueArticles = 0;
        totalRevisions = 0;
        articles = new HashMap<>();
        contributors = new HashMap<>();
        titles = new HashMap<>();
    }

    /**
     * Adiciona um artigo (se não existir)
     * @param id            ID
     * @param title         Título
     * @param revisionID    ID da revisão
     * @param timestamp     Data da revisão
     * @return O artigo foi inserido com sucesso (true) ou já existe (false)
     */
    public boolean addArticle(long id, String title, long revisionID, String timestamp){
        if (!articles.containsKey(id)){
            Article article = new Article(id, revisionID, 0, 0, title);
            Revision revision = new Revision(revisionID, timestamp);
            article.addRev(revision);
            articles.put(id, article);
            totalRevisions++;
            uniqueArticles++;
            return true;
        }
        else{
            if (articles.get(id).getLastRevision() != revisionID){
                Revision revision = new Revision(revisionID, timestamp);
                articles.get(id).setLastRevision(revisionID);
                articles.get(id).addRev(revision);
                articles.get(id).setTitle(title);
                totalRevisions++;
                return true;
            }
        }
        return false;
    }

    /**
     * Adiciona um contribuidor (se não existir)
     * @param id        ID
     * @param username  Nome
     * @param newRev    Indica se foi adicionada uma nova revisão
     */
    public void addContributor(long id, String username, boolean newRev){
        if (!contributors.containsKey(id)) {
            Contributor contributor = new Contributor(id, 1, username);
            contributors.put(id, contributor);
        }
        else if (newRev) contributors.get(id).increaseCount();
    }

    /**
     * Adiciona um título à tabela de títulos
     * @param title  Título a adicionar
     */
    public void addTitlesToTable(){
        for (Article a: articles.values()) {
            if (!titles.containsKey(a.getTitle().charAt(0)))
                titles.put(a.getTitle().charAt(0), new ArrayList<>());
            titles.get(a.getTitle().charAt(0)).add(a.getTitle());
        }
    }

    /**
     * Atualiza o número de caracteres e palavras
     * @param id
     * @param text
     */
    public void updateArticleLength(long id, String text){
        LengthText.count(text);
        if (LengthText.getLengthChars() > articles.get(id).getLength())
            articles.get(id).setLength(LengthText.getLengthChars());
        if (LengthText.getLengthWords() > articles.get(id).getLengthW())
            articles.get(id).setLengthW(LengthText.getLengthWords());
    }

    /**
     * Incrementa o número de pages (artigos totais)
     */
    public void incrementNumberOfPages(){
        numberOfPages++;
    }

    /**
     * Retorna o número de artigos totais
     * @return Número de artigos totais
     */
    public long getNumberOfPages(){
        return numberOfPages;
    }

    /**
     * Retorna o número de artigos únicos
     * @return Número de artigos únicos
     */
    public long getUniqueArticles(){
        return uniqueArticles;
    }

    /**
     * Retorna o número de revisões totais
     * @return Número de revisões
     */
    public long getTotalRevisions(){
        return totalRevisions;
    }

    /**
     * Retorna o map com os artigos
     * @return Map de Artigos
     */
    public HashMap<Long, Article> getArticles(){
        return articles;
    }

    /**
     * Retorna o map de contribuidores
     * @return Map de contribuidores
     */
    public HashMap<Long, Contributor> getContributors(){
        return contributors;
    }

    /**
     * Retorna o Map de títulos
     * @return Map de títulos
     */
    public HashMap<Character, ArrayList<String>> getTitles(){
        return titles;
    }
}
