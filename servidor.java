import java.io.*;
import java.net.*;

public class Servidor {
    public static void main(String[] args) {
        ServerSocket servidor = null;
        Socket cliente = null;
        BufferedReader entrada = null;
        PrintWriter salida = null;
        
        try {
            // Crear un socket servidor en el puerto 5000
            servidor = new ServerSocket(5000);
            System.out.println("Servidor iniciado, esperando cliente...");
            
            // Aceptar conexiones del cliente
            cliente = servidor.accept();
            System.out.println("Cliente conectado");

            // Flujos para recibir y enviar mensajes
            entrada = new BufferedReader(new InputStreamReader(cliente.getInputStream()));
            salida = new PrintWriter(cliente.getOutputStream(), true);
            
            // Ciclo para intercambiar mensajes con el cliente
            String mensaje;
            while ((mensaje = entrada.readLine()) != null) {
                System.out.println("Cliente: " + mensaje);
                salida.println("Mensaje recibido: " + mensaje);
            }
        } catch (IOException e) {
            System.out.println("Error en el servidor: " + e.getMessage());
        } finally {
            try {
                if (entrada != null) entrada.close();
                if (salida != null) salida.close();
                if (cliente != null) cliente.close();
                if (servidor != null) servidor.close();
            } catch (IOException e) {
                System.out.println("Error cerrando recursos: " + e.getMessage());
            }
        }
    }
}
