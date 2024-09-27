import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Cliente {
    public static void main(String[] args) {
        Socket socket = null;
        DataOutputStream salida = null;
        DataInputStream entrada = null;

        try {
            // Conectar al servidor en localhost, puerto 5000
            socket = new Socket("127.0.0.1", 5000);
            System.out.println("Conectado al servidor");

            // Flujos para enviar y recibir datos
            salida = new DataOutputStream(socket.getOutputStream());
            entrada = new DataInputStream(socket.getInputStream());

            // Escanear números desde el teclado
            Scanner scanner = new Scanner(System.in);
            while (true) {
                System.out.print("Ingrese un número entero para enviar al servidor (0 para salir): ");
                int numero = scanner.nextInt();

                // Enviar número al servidor
                salida.writeInt(numero);
                salida.flush();

                // Salir si el número es 0
                if (numero == 0) break;

                // Recibir respuesta del servidor
                int numeroRecibido = entrada.readInt();
                System.out.println("Número recibido del servidor: " + numeroRecibido);
            }
        } catch (IOException e) {
            System.out.println("Error de conexión: " + e.getMessage());
        } finally {
            try {
                if (entrada != null) entrada.close();
                if (salida != null) salida.close();
                if (socket != null) socket.close();
            } catch (IOException e) {
                System.out.println("Error cerrando recursos: " + e.getMessage());
            }
        }
    }
}
