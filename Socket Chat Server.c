#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <arpa/inet.h>

//#define DEFAULT_PORT 55555 //49152 to 65535

void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {

    char mode; // 's' for server and 'c' for client
    int port;
    char *serverIP;

    switch (argc) {
        case 1:
            mode = 's';
            srandom(getpid());
            port = 0xc000 | (random()&0x3fff);
            break;
        case 2:
            mode = 's';
            port = atoi(argv[1]);
            break;
        case 3:
            mode = 'c';
            serverIP = argv[1];
            port = atoi(argv[2]);
            break;
        default:
            fprintf(stderr, "Usage: %s [port]\n", argv[0]);
            exit(EXIT_FAILURE);
    }

    if (mode == 's') {
        int server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket == -1) {
            handle_error("Socket creation failed");
        }

        struct sockaddr_in server_address;
        memset(&server_address, 0, sizeof(struct sockaddr_in));
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(port);

        if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
            handle_error("Bind failed");
        }

        if (listen(server_socket, 20) == -1) {
            handle_error("Listen failed");
        }

        printf("The server is now listening on port %d\n", port);

        int client_socket = accept(server_socket, (struct sockaddr*)NULL, NULL);
        if (client_socket == -1) {
            handle_error("Accept failed");
        }
        printf("Connected to client\n");

        if (close(server_socket) == -1) {
            handle_error("Server socket close failed");
        }

        struct pollfd descriptors[2];
        descriptors[0].fd = client_socket;
        descriptors[0].events = POLLIN;
        descriptors[1].fd = STDIN_FILENO;
        descriptors[1].events = POLLIN;
        
        char buffer[4096];

        while(1) {
            int poll_result = poll(descriptors, 2, 60000);

            if (poll_result > 0) {

                if (descriptors[0].revents & POLLIN) {
                    ssize_t bytes_received = read(client_socket, buffer, sizeof(buffer));
                    if (bytes_received > 0) {
                        ssize_t bytes_written = write(STDOUT_FILENO, buffer, bytes_received);
                        if (bytes_written != bytes_received) {
                            handle_error("Write to STDOUT_FILENO failed");
                        }
                    }
                }

                if (descriptors[1].revents & POLLIN) {
                    ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
                    if (bytes_read > 0) {
                        ssize_t bytes_sent = write(client_socket, buffer, bytes_read);
                        if (bytes_sent != bytes_read) {
                            handle_error("Write to client socket failed");
                        }
                    }
                }

            }
            else if (poll_result == 0) {
                fprintf(stderr, "Timeout occurred\n");
                break;
            }
            else {
                handle_error("Poll error");
            }
        }
        if (close(client_socket) == -1) {
            handle_error("Client socket close failed");
        }
    }

    else if (mode == 'c') {
        int client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (client_socket == -1) {
            handle_error("Socket creation failed");
        }

        struct sockaddr_in server_address;

        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = inet_addr(serverIP);
        server_address.sin_port = htons(port);

        if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
            handle_error("Connection failed");
        }

        struct pollfd descriptors[2];
        descriptors[0].fd = client_socket;
        descriptors[0].events = POLLIN;
        descriptors[1].fd = STDIN_FILENO;
        descriptors[1].events = POLLIN;
        
        char buffer[4096];

        while(1) {
            int poll_result = poll(descriptors, 2, 60000);

            if (poll_result > 0) {

                if (descriptors[0].revents & POLLIN) {
                    ssize_t bytes_received = read(client_socket, buffer, sizeof(buffer));
                    if (bytes_received > 0) {
                        ssize_t bytes_written = write(STDOUT_FILENO, buffer, bytes_received);
                        if (bytes_written != bytes_received) {
                            handle_error("Write to STDOUT_FILENO failed");
                        }
                    }
                }

                if (descriptors[1].revents & POLLIN) {
                    ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
                    if (bytes_read > 0) {
                        ssize_t bytes_sent = write(client_socket, buffer, bytes_read);
                        if (bytes_sent != bytes_read) {
                            handle_error("Write to server socket failed");
                        }
                    }
                }

            }
            else if (poll_result == 0) {
                fprintf(stderr, "Timeout occurred\n");
                break;
            }
            else {
                handle_error("Poll error");
            }
        }
        if (close(client_socket) == -1) {
            handle_error("Client socket close failed");
        }
    }

    return 0;
}
