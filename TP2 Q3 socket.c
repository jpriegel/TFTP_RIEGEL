#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

//UDP sur port 69

#define SIZE 500

char exitmsg[] = "bye bye...\n";
char ipserveur[256];
char argcmd[SIZE];

const char *port = "69";

struct addrinfo hints;
struct addrinfo *res, *tmp;

int s, sfd;

int main(int argc, char **argv) {
    char *serveur = argv[1];

    if (argc < 3) {
        write(STDOUT_FILENO, exitmsg, strlen(exitmsg));
        exit(EXIT_SUCCESS);
    } else {
        write(STDOUT_FILENO, "Bon nombre d'argument\n", strlen("Bon nombre d'argument\n"));
        for (int i = 0; i < argc; i++) {
            sprintf(argcmd, "%d : %s\n", i, argv[i]);
            write(STDOUT_FILENO, argcmd, strlen(argcmd));
        }
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_flags = 0;
        hints.ai_protocol = IPPROTO_UDP;

        s = getaddrinfo(serveur, port, &hints, &res);
        if (s != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
            exit(EXIT_FAILURE);
        }
        for (tmp = res; tmp != NULL; tmp = tmp->ai_next) {
            getnameinfo(tmp->ai_addr, tmp->ai_addrlen, ipserveur, sizeof(ipserveur), NULL, 0, NI_NUMERICHOST);
            puts(ipserveur);
        }
        sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sfd == socket(AF_INET, SOCK_DGRAM, 0)) {
            perror("socket error");
            exit(EXIT_FAILURE);
        }
        freeaddrinfo(res);
        exit(EXIT_SUCCESS);
    }

}