package engine;


public class LengthText {
    private static long lengthChars;
    private static long lengthWords;

    /**
     * Conta o número de bytes num caractere codificado em utf8
     * @param c Caractere
     * @return Número de bytes
     */
    private static int utf8ToBytes (char c) {
        if (c <= 0x7f) return 1;
        if (c <= 0x7ff) return 2;
        if (c <= 0xffff) return 3;
        return 0;
    }

    /**
     * Conta o número de palavras e caracteres numa string
     * @param text String a contar
     */
    public static void count(String text){
        lengthChars = 0;
        lengthWords = 0;
        int i = 1, length = text.length();
        char c = text.charAt(0);
        boolean flag = true;
        while (i < length) {
            for (; (c == ' ' || c == '\n' || c == '\t') && i < length; c = text.charAt(i), i++, flag = true)
                lengthChars += utf8ToBytes(c);

            if (flag) {
                lengthWords++;
                flag = false;
            }

            for (; c != ' ' && c != '\n' && c != '\t' && i < length; c = text.charAt(i), i++)
                lengthChars += utf8ToBytes(c);
        }
        lengthChars++;
    }

    /**
     * Retorna o número de caracteres contados
     * @return Número de caracteres
     */
    public static long getLengthChars(){
        return lengthChars;
    }

    /**
     * Retorna o número de palavras contadas
     * @return Número de palavras
     */
    public static long getLengthWords(){
        return lengthWords;
    }
}
