#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 1234
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE], request[BUFFER_SIZE];

    // setup
    bzero((char*)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // create a socekt
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // coneect to the server
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(sock);
        exit(1);
    }

    while (1) {
        bzero(buffer, 256);
        read(sock, buffer, 256);
        printf("%s", buffer); // What's your requirement?

        bzero(buffer, 256);
        scanf("%s", buffer); // 1, 2, 3
        write(sock, buffer, strlen(buffer));

        if (buffer[0] == '1') { // DNS
            bzero(buffer, 256);
            read(sock, buffer, 256);
            printf("%s", buffer); // Input URL address :

            bzero(buffer, 256);
            scanf("%s", buffer); // URL
            write(sock, buffer, strlen(buffer));

            bzero(buffer, 256);
            read(sock, buffer, 256);
            printf("address get from domain name : %s\n\n", buffer);
        }
        else if (buffer[0] == '2') { // QUERY
            bzero(buffer, 256);
            read(sock, buffer, 256);
            printf("%s", buffer); // Input student ID:

            bzero(buffer, 256);
            scanf("%s", buffer); // 1234
            write(sock, buffer, strlen(buffer));

            bzero(buffer, 256);
            read(sock, buffer, 256);
            printf("Email get from server : %s\n\n", buffer); // gmail
        }
        else if (buffer[0] == '3') { // QUIT
            break;
        }
        else {
            break;
        }
    }

    close(sock);
    return 0;
}
