#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in servidor;
    char mensaje[1024];
    char respuesta[1024];

    // Crear el socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("No se pudo crear el socket\n");
        return -1;
    }

    // Configurar la estructura del servidor
    servidor.sin_addr.s_addr = inet_addr("127.0.0.1"); // Dirección IP del servidor
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(5000); // Puerto del servidor

    // Conectar al servidor
    if (connect(sock, (struct sockaddr *)&servidor, sizeof(servidor)) < 0) {
        printf("Error al conectar con el servidor\n");
        return -1;
    }

    printf("Conectado al servidor\n");

    // Enviar y recibir mensajes
    while (1) {
        printf("Ingrese mensaje: ");
        fgets(mensaje, sizeof(mensaje), stdin);

        // Quitar el salto de línea del final del mensaje
        mensaje[strcspn(mensaje, "\n")] = 0;

        // Enviar el mensaje al servidor
        if (send(sock, mensaje, strlen(mensaje), 0) < 0) {
            printf("Error al enviar el mensaje\n");
            return -1;
        }

        // Recibir la respuesta del servidor
        if (recv(sock, respuesta, sizeof(respuesta), 0) < 0) {
            printf("Error al recibir la respuesta\n");
            return -1;
        }

        printf("Servidor: %s\n", respuesta);
    }

    close(sock);
    return 0;
}
