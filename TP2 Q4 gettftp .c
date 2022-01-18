#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#define SIZE 500

char exitmsg[] = "bye bye...\n";
char ipserveur[256];

struct addrinfo hints;
struct addrinfo *res, *tmp;

const char *port = "69"; //UDP sur port 69

int s, sfd;


int main(int argc, char **argv) {
    char argcmd[SIZE];
    char *serveur = argv[1];
    char *filename = argv[2];

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
        } else {//RRQ
            char *cmd;
            cmd = malloc(SIZE);
            cmd[0] = 0;
            cmd[1] = 1;
            strcpy(cmd + 2, filename);
            strcpy(cmd + strlen(filename) + 3, "octet");
            int csend = sendto(sfd, cmd, (int) (4 + strlen(filename) + strlen("octet")), 0, res->ai_addr,
                               res->ai_addrlen);
            if (csend == -1) {
                perror("Erreur dans le premier envoi de données");
                exit(EXIT_FAILURE);
            }
            free(cmd);
        }
        freeaddrinfo(res);
        exit(EXIT_SUCCESS);
    }
}