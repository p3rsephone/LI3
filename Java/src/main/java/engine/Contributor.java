package engine;


import java.util.LinkedList;


public class Contributor {
    
    private long id; ///< ID do contribuidor
    private long count; ///< Número de contribuições
    private String username; ///< Nome do contribuidor
    

    /** CONSTRUTORES */

    /**
     * Cria um Contribuidor sem parâmetros
     */
    public Contributor() {
        this.setId(0);
        this.setCount(0);
        this.setUsername(null);
    }

    /**
     * Cria um Contribuidor passado parâmetros
     * @param id
     * @param count
     * @param username
     */
    public Contributor(long id, long count, String username){
        this.setId(id);
        this.setCount(count);
        this.setUsername(username);
    }

    /**
     * Constroi um Contribuidor a partir de um já existente
     * @param c Contribuidor já definido
     */
    public Contributor(Contributor c) {
        this(c.getId(), c.getCount(), c.getUsername());
    }

    /** Métodos de instância */

    /**
     * Faz a cópia de um Contribuidor
     * @return Cópia de Contribuidor
     */
    public Contributor clone(){
        return new Contributor(this);
    }

    /**
     * Retona o ID do contribuidor
     * @return ID do contribuidor
     */
    public long getId() {
        return id;
    }

    /**
     * Altera o ID do contribuidor
     * @param id Novo ID
     */
    public void setId(long id) {
        this.id = id;
    }

    /**
     * Retorna o número de contribuições
     * @return Número de contribuições
     */
    public long getCount() {
        return count;
    }

    /**
     * Altera o número de contribuições
     * @param count Novo número de contribuições
     */
    public void setCount(long count) {
        this.count = count;
    }

    /**
     * Retorna o nome do contribuidor
     * @return Nome
     */
    public String getUsername() {
        return username;
    }

    /**
     * Altera o nome do contribuidor
     * @param username Novo nome
     */
    public void setUsername(String username) {
        this.username = username;
    }

    /**
     * Compara dois Contribuidors
     * @param c Contribuidor a comparar
     * @return É o mesmo Contribuidor (true) ou não (false)
     */
    public boolean equals(Object o){
        if (o == null) return false;

        if (this == o) return true;

        Contributor c = (Contributor) o;
        return (id == c.getId() && count == c.getCount()
                && username.equals(c.getUsername()));
    }

    /**
     * Imprime a informação de um contribuidor
     * @return Contribuidor em String
     */
    public String toString(){
        return "ID: " + id +
                "\nNome: " + username +
                "\nNº de contribuições: " + count;
    }

    /**
     * Incrementa o número de contribuições
     */
    public void increaseCount(){
        this.count++;
    }

}

