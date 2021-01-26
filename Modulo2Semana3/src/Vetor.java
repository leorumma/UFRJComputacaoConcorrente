import java.util.Arrays;

public class Vetor {

    private final int[] vector;

    Vetor(int tamanhoVetor, int valor) {
        this.vector = new int[tamanhoVetor];
        this.iniciarVetor(valor);
    }

    public int getTamanhoVetor() {
        return vector.length;
    }

    private void iniciarVetor(int valor) {
        Arrays.fill(vector, valor);
    }

    public void setValue(int valor, int posicao) {
        vector[posicao] = valor;
    }

    public int getValue(int posicao){
        return vector[posicao];
    }

}
