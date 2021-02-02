public class Main {

    public static void main(String[] args) {

        MyBuffer myBuffer = new MyBuffer(10);
        Produtor[] produtors = new Produtor[4];       // Threads leitores
        Consumidor[] consumidors = new Consumidor[3];   // Threads escritores

        for (int i = 0; i < produtors.length; i++) {
            produtors[i] = new Produtor(i + 1, (i + 1) * 500, myBuffer);
            produtors[i].start();
        }
        for (int i = 0; i < consumidors.length; i++) {
            consumidors[i] = new Consumidor(i + 1, (i + 1) * 500, myBuffer);
            consumidors[i].start();
        }


    }


}
