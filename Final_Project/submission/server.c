#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#define PORT 1234
#define BUFFER_SIZE 1024
static char id[256][BUFFER_SIZE], email[256][BUFFER_SIZE];
int cnt = 0;

int main() {
    // query files
    FILE* file = fopen("query.txt", "r");
    if (!file) perror("Error opening query.txt");
    while (~fscanf(file, "%s%s", id[cnt], email[cnt])) cnt++;
    fclose(file);

    // init
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    // setup
    bzero((char*)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY; // ?

    // bind the socket
    if (bind(server_sock = socket(AF_INET, SOCK_STREAM, 0), (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_sock);
        exit(1);
    }

    // listen
    if (listen(server_sock, 10) == -1) {
        perror("Listen failed");
        close(server_sock);
        exit(1);
    }

    while (1) {
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        if (client_sock == -1) {
            perror("Accept failed");
            continue;
        }

        // connection success
        // handle client
        char buffer[BUFFER_SIZE], response[BUFFER_SIZE];

        while (1) {
            bzero(buffer, 256);
            strcpy(buffer, "What's your requirement? 1.DNS 2.QUERY 3.QUIT : ");
            write(client_sock, buffer, strlen(buffer));

            if (read(client_sock, buffer, 256) <= 0) {
                perror("Read failed");
            }
            else if (buffer[0] == '1') {
                bzero(buffer, 256);
                strcpy(buffer, "Input URL address : ");
                write(client_sock, buffer, strlen(buffer));

                bzero(buffer, 256);
                read(client_sock, buffer, 256);

                struct hostent *host = gethostbyname(buffer);
                if (!host) strcpy(response, "No such URL address");
                else strcpy(response, inet_ntoa(*((struct in_addr*)host->h_addr)));
                write(client_sock, response, 256);
            }
            else if (buffer[0] == '2') {
                bzero(buffer, 256);
                strcpy(buffer, "Input student ID : ");
                write(client_sock, buffer, strlen(buffer));

                bzero(buffer, 256);
                read(client_sock, buffer, 256);

                bzero(response, 256);
                int ok = 0;
                for (int i = 0; i < cnt; i++)
                    if (strcmp(buffer, id[i]) == 0) {
                        ok = 1;
                        strcpy(response, email[i]);
                        // break;
                    }
                if (!ok) strcpy(response, "No such student ID");
                write(client_sock, response, 256);
            }
            else if (buffer[0] == '3') {
                break;
            }

        }

        close(client_sock);
    }

    close(server_sock);
    return 0;
}

