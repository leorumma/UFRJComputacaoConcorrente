public class Tarefa extends Thread {

    private final Vetor vetA;

    private final Vetor vetB;

    private final Vetor vetC;

    private final int inicio;

    private final int fim;

    Tarefa(Vetor vetA, Vetor vetB, Vetor vetC, int inicio, int fim ){
        this.vetA = vetA;
        this.vetB = vetB;
        this.vetC = vetC;
        this.inicio = inicio;
        this.fim = fim;
    }

    public void run(){
        for (int i = inicio; i < fim; i++){
            vetC.setValue((vetA.getValue(i)+vetB.getValue(i)),i);
        }
    }

}
