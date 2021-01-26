public class Main {

    static final int nThread = 3;

    public static void main(String[] args) {

        Thread[] threads = new Thread[nThread];

        Vetor vetA = new Vetor(30, 6);

        Vetor vetB = new Vetor(30, 14);

        Vetor vetC = new Vetor(30, 0);


        int tamanhoSequencia = vetA.getTamanhoVetor() / nThread;
        int resto = vetA.getTamanhoVetor() % nThread;
        int tamanhoSequenciaComRestoDistribuido = 0;
        int inicio;
        int fim;
        for (int i = 0; i < threads.length; i++) {
            int len = tamanhoSequencia;
            inicio = tamanhoSequenciaComRestoDistribuido;
            if (resto > 0){
                len++;
                resto--;
            }
            tamanhoSequenciaComRestoDistribuido+= len;
            fim = inicio + len;
            threads[i] = new Tarefa(vetA, vetB, vetC,inicio, fim);
        }


        for (Thread thread : threads) {
            thread.start();
        }

        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                return;
            }
        }

        for (int i = 0; i < vetC.getTamanhoVetor(); i++){
            System.out.println("O valor do vetC na posição "+ i + " eh " + vetC.getValue(i) );
        }

    }


}
