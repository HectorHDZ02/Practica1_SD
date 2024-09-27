#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int servidor, cliente, len, numero;
    struct sockaddr_in servidor_addr, cliente_addr;

    // Crear socket
    servidor = socket(AF_INET, SOCK_STREAM, 0);
    if (servidor == -1) {
        printf("Error al crear el socket\n");
        return -1;
    }

    // Configurar la estructura del servidor
    servidor_addr.sin_family = AF_INET;
    servidor_addr.sin_addr.s_addr = INADDR_ANY;
    servidor_addr.sin_port = htons(5000);

    // Asociar socket con la dirección IP y el puerto
    if (bind(servidor, (struct sockaddr *)&servidor_addr, sizeof(servidor_addr)) < 0) {
        printf("Error al asociar el socket\n");
        close(servidor);
        return -1;
    }

    // Escuchar conexiones entrantes
    listen(servidor, 3);
    printf("Esperando conexión...\n");

    len = sizeof(cliente_addr);
    cliente = accept(servidor, (struct sockaddr *)&cliente_addr, (socklen_t*)&len);
    if (cliente < 0) {
        printf("Error al aceptar la conexión\n");
        close(servidor);
        return -1;
    }

    printf("Cliente conectado\n");

    // Intercambio de números enteros
    while (1) {
        // Recibir número del cliente
        if (recv(cliente, &numero, sizeof(int), 0) > 0) {
            printf("Número recibido del cliente: %d\n", numero);
            // Enviar el mismo número de vuelta
            if (send(cliente, &numero, sizeof(int), 0) < 0) {
                printf("Error al enviar el número\n");
                break;
            }
        } else {
            printf("Cliente desconectado\n");
            break;
        }
    }

    close(cliente);
    close(servidor);
    return 0;
}
