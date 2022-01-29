// #include "pipe_networking.h"
//
// /*=========================
//   server_handshake
//   args: int * to_client
//
//   Performs the client side pipe 3 way handshake.
//   Sets *to_client to the file descriptor to the downstream pipe.
//
//   returns the file descriptor for the upstream pipe.
//   =========================*/
// int server_handshake(int *to_client) {
//     mkfifo(WKP, 0644);
//
//     int from_client = open(WKP, O_RDONLY);
//     char received[100];
//     int i = read(from_client, received, sizeof(received));
//     if (i) printf("%s\n", received);
//     remove(WKP);
//
//     *to_client = open(received, O_WRONLY);
//     write(*to_client, ACK, strlen(ACK));
//
//     i = read(from_client, received, sizeof(received));
//     if (i) printf("%s\n", received);
//
//     return from_client;
// }
//
//
// /*=========================
//   client_handshake
//   args: int * to_server
// x
//   Performs the client side pipe 3 way handshake.
//   Sets *to_server to the file descriptor for the upstream pipe.
//
//   returns the file descriptor for the downstream pipe.
//   =========================*/
// int client_handshake(int *to_server) {
//     int pidNum = getpid();
//     char pid[100];
//     char message[100];
//     sprintf(pid, "%d", pidNum);
//     mkfifo(pid, 0644);
//
//     *to_server = open(WKP, O_WRONLY);
//
//     write(*to_server, pid, strlen(pid));
//     printf("yes\n");
//     int from_server = open(pid, O_RDONLY);
//     int i = read(from_server, message, sizeof(message));
//     if (i) {
//         printf("%s", message);
//     }
//     remove(pid);
//
//     write(*to_server, ACK, strlen(ACK));
//     return from_server;
// }

#include "pipe_networking.h"

/*=========================
  server_handshake
  args: int * to_client
  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
    mkfifo(WKP, 0644);
    int from_client = open(WKP, O_RDONLY);
    char text[100];

    read(from_client, text, sizeof(text));
    printf("%s\n", text);
    remove(WKP);
    *to_client = open(text, O_WRONLY);
    write(*to_client, ACK, strlen(ACK));
    read(from_client, text, sizeof(text));
    printf("%s\n", text);
    return from_client;
}


/*=========================
  client_handshake
  args: int * to_server
x
  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
    char pid[100];
    char text[100];
    sprintf(pid, "%d", getpid());
    mkfifo(pid, 0644);

    pid[strlen(pid) - 2] = '\0';
    *to_server = open(WKP, O_WRONLY);
    write(*to_server, pid, strlen(pid));
    int from_server = open(pid, O_RDONLY);
    read(from_server, text, sizeof(text));
    printf("%s\n", text);
    remove(pid);
    write(*to_server, ACK, strlen(ACK));
    return from_server;
}
