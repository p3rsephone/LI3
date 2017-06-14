package engine;


import java.util.LinkedList;


public class Revision {
    
    private long id; ///< ID da revisão
    private String timestamp; ///< Data da revisão
   

    /** CONSTRUTORES */

    /**
     * Cria uma Revision sem parâmetros
     */
    public Revision() {
        this.setId(0);
        this.setTimestamp(null);
    }

    /**
     * Cria uma Revision passado parâmetros
     * @param id          ID da revisão
     * @param timestamp   Data da revisão
     */
    public Revision(long id, String timestamp){
        this.setId(id);
        this.setTimestamp(timestamp);
    }

    /**
     * Constroi uma Revision a partir de uma já existente
     * @param r Revision já definida
     */
    public Revision(Revision r) {
        this(r.getId(), r.getTimestamp());
    }

    /** Métodos de instância */

    /**
     * Faz a cópia de uma Revision
     * @return Cópia de Revision
     */
    public Revision clone(){
        return new Revision(this);
    }

    /**
     * Retorna o ID da revisão
     * @return ID
     */
    public long getId() {
        return id;
    }

    /**
     * Altera o ID da revisão
     * @param id Novo ID
     */
    public void setId(long id) {
        this.id = id;
    }

    /**
     * Retorna a data da revisão
     * @return Data
     */
    public String getTimestamp() {
        return timestamp;
    }

    /**
     * Altera a data da revisão
     * @param timestamp Nova data
     */
    public void setTimestamp(String timestamp) {
        this.timestamp = timestamp;
    }

    /**
     * Compara duas revisoes
     * @param r Revisao a comparar
     * @return É a mesma revisao (true) ou não (false)
     */
    public boolean equals(Object o){
        if (o == null) return false;

        if (this == o) return true;

        Revision r = (Revision) o;
        return (id == r.getId() && timestamp.equals(r.getTimestamp()));
    }

    /**
     * Imprime a informação de uma revisão
     * @return Revisão em String
     */
    public String toString(){
        return "ID: " + id +
                "\nData: " + timestamp;
    }

}

