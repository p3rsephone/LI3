package engine;


import java.util.LinkedList;

public class Article {
    
    private long id; ///< ID do artigo
	private long lastRevision; ///< ID da última revisão
	private long length; ///< Tamanho do artigo em carateres
	private long lengthW; ///< Tamanho do artigo em palavras
	private String title; ///< Título do artigo
    private LinkedList<Revision> revisions = new LinkedList<>(); ///< Revisoes do Artigo

    /** CONSTRUTORES */

    /**
     * Cria um Artigo sem parâmetros
     */
    public Article() {
        this.setId(0);
        this.setLastRevision(0);
        this.setLength(0);
        this.setLengthW(0);
        this.setTitle(null);
    }

    /**
     * Cria um Artigo passado parâmetros
     * @param id               ID do artigo
     * @param lastRevision     ID da ultima revisão
     * @param length           Tamanho em caracteres
     * @param lengthW          Tamanho em palavras
     * @param revisions        ArrayList de revisões
     */
    public Article(long id, long lastRevision, long length, long lengthW, String title){
        this.setId(id);
        this.setLastRevision(lastRevision);
        this.setLength(length);
        this.setLengthW(lengthW);
        this.setTitle(title);
    }

    /**
     * Constroi um Artigo a partir de um já existente
     * @param a Artigo já definido
     */
    public Article(Article a) {
        this(a.getId(), a.getLastRevision(), a.getLength(), a.getLengthW(), a.getTitle());
    }

    /** Métodos de instância */

    /**
     * Faz a cópia de um Artigo
     * @return Cópia de Artigo
     */
    public Article clone(){
        return new Article(this);
    }

    /**
     * Retorna o id do artigo
     * @return ID
     */
    public long getId() {
        return id;
    }

    /**
     * Altera o id do artigo
     * @param id Novo id
     */
    public void setId(long id) {
        this.id = id;
    }

    /**
     * Retorna o id da ultima revisão
     * @return Ultima revisão
     */
    public long getLastRevision() {
        return lastRevision;
    }

    /**
     * Altera o id da ultima revisão
     * @param lastRevision Nova ultima revisão
     */
    public void setLastRevision(long lastRevision) {
        this.lastRevision = lastRevision;
    }

    /**
     * Retorna o tamanho do artigo em carateres
     * @return Tamanho (carateres)
     */
    public long getLength() {
        return length;
    }

    /**
     * Altera o tamanho do artigo em carateres
     * @param length Novo tamanho de carateres
     */
    public void setLength(long length) {
        this.length = length;
    }

    /**
     * Retorna o número de palavras do artigo
     * @return Tamanho (palavras)
     */
    public long getLengthW() {
        return lengthW;
    }

    /**
     * Altera o tamanho do artigo em palavras
     * @param lengthW Novo tamanho de palavras
     */
    public void setLengthW(long lengthW) {
        this.lengthW = lengthW;
    }

    /**
     * Retorna o título do artigo
     * @return Título
     */
    public String getTitle() {
        return title;
    }

    /**
     * Altera o título do artigo
     * @param title Novo título
     */
    public void setTitle(String title) {
        this.title = title;
    }

   /**
     * Retorna uma cópia das revisoes do artigo
     * @return Revisoes do artigo
     */
    public LinkedList<Revision> getRevisions() {
        LinkedList<Revision> revisions = new LinkedList<>();
        if (this.revisions != null)
            for(Revision r : this.revisions)
                revisions.add(r.clone());
        return revisions;
    }

    /**
     * Retorna o timestamp de uma determinada revisão do artigo
     * @param rev_id ID da revisão
     * @return TimeStamp da revisão
     */
    public String getRevTimestamp(long rev_id){
        int i;
        for (i = 0; i<this.revisions.size() && this.revisions.get(i).getId() != rev_id; i++);
        if (i < this.revisions.size())
            return this.revisions.get(i).getTimestamp();
        else return null;
    }
    
    /**
     * Altera as revisoes do artigo
     * @param revisions Revisoes do artigo
     */
    public void setRevisions(LinkedList<Revision> revisions){
        LinkedList<Revision> list = new LinkedList<>();
        for (Revision r: revisions)
            list.add(r.clone());
        revisions = list;
    }

    /**
     * Compara dois artigos
     * @param a Artigo a comparar
     * @return É o mesmo artigo (true) ou não (false)
     */
    public boolean equals(Object o){
        if (o == null) return false;

        if (this == o) return true;

        Article a = (Article) o;
        return (id == a.getId() && lastRevision == a.getLastRevision()
                && length == a.getLength() && lengthW == a.getLengthW()
                && title.equals(a.getTitle()) && revisions.equals(a.getRevisions()));
    }

    /**
     * Imprime a informação de um artigo
     * @return Artigo em String
     */
    public String toString(){
        return "ID: " + id +
                "\nTítulo: " + title +
                "\nTamanho em caracteres: " + length +
                "\nTamanho em palavras: " + lengthW +
                "\nUltima revisão: " + lastRevision +
                "\nRevisões: " + revisions;
    }

    /**
     * Adiciona uma revision a um artigo
     * @param revision Revisão a ser adicionada
     */
    public int addRev(Revision r){
        if (this.revisions.contains(r)) {
            return 0;
        }
        else {
            this.revisions.add(r);
            setLastRevision(r.getId());
            return 1;
        }
    }
}