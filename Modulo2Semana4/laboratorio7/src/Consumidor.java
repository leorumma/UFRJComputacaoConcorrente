public class Consumidor extends Thread {
    int id; //identificador da thread
    int delay; //atraso bobo
    MyBuffer monitor;//objeto monitor para coordenar a lógica de execução das threads

    // Construtor
    Consumidor(int id, int delayTime, MyBuffer m) {
        this.id = id;
        this.delay = delayTime;
        this.monitor = m;
    }

    // Método executado pela thread
    public void run() {
        double j = 777777777.7, i;
        try {
            while (true) {
                this.monitor.removerElemento(this.id);
                for (i = 0; i < 100000000; i++) {
                    j = j / 2;
                } //...loop bobo para simbolizar o tempo de leitura
                sleep(this.delay);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
