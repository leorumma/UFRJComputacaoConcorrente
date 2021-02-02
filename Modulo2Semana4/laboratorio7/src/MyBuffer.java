import java.util.Arrays;

public class MyBuffer {

    //Foi definido que se a posição contendo 0 está vazia e se conter 1 está preenchida.
    //buffer com tudo 0 está vazio
    //buffer com tudo 1 está cheio

    int consumidor = 0;
    int produtor = 0;

    int[] buffer;

    MyBuffer(int tamanhoBuffer) {
        buffer = new int[tamanhoBuffer];
        inicializarBuffer();
    }

    private void inicializarBuffer() {
        Arrays.fill(buffer, 0);
    }

    public synchronized void imprimirElementosBuffer() {
        for (int j : buffer) {
            System.out.print("[" + j + "]");
        }
        System.out.println("\n");
    }

    private boolean isCheio() {
        int cont = 0;
        for (int j : buffer) {
            if (j != 0) {
                cont++;
            }
        }
        return cont == buffer.length;
    }

    private boolean isVazio() {
        int cont = 0;
        for (int j : buffer) {
            if (j != 0) {
                cont++;
            }
        }
        return cont == 0;
    }

    public synchronized void inserirElemento(int id) {
        try {
            while (this.consumidor > 0) {
                System.out.println("Produtor bloqueado" + id);
                wait();
                this.produtor++;
            }
            if (isCheio()) {
                wait();
                System.out.println("O buffer esta cheio.. aguarde");
            }
            int posicao = 0;
            for (int i = 0; i < buffer.length; i++) {
                if (buffer[i] == 0) {
                    posicao = i;
                    break;
                }
            }
            buffer[posicao] = 1;
            imprimirElementosBuffer();
            this.produtor--;
            System.out.println("Produtor terminou" + id);
            notifyAll();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public synchronized void removerElemento(int id) {
        try {
            while (this.produtor > 0) {
                System.out.println("Consumidor bloqueado" + id);
                wait();
                this.consumidor++;
            }
            if (isVazio()) {
                wait();
                System.out.println("O buffer esta vazio.. aguarde");
            }
            int posicao = 0;
            for (int i = 0; i < buffer.length; i++) {
                if (buffer[i] != 0) {
                    posicao = i;
                    break;
                }
            }
            buffer[posicao] = 0;
            imprimirElementosBuffer();
            this.consumidor--;
            System.out.println("Consumidor terminou" + id);
            notifyAll();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
