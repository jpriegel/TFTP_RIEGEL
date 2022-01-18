#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//UDP sur port 69

#define SIZE 500
char exitmsg[] = "bye bye...\n";
char argcmd[SIZE];

int main(int argc, char **argv) {

//    argv[0] = "gettftp1";
//    argv[1] = "srvtpinfo1.ensea.fr";
//    argv[2] = "lucas.txt";
    if (argc < 3) {//test pour avoir au moins 3 arguments
        write(STDOUT_FILENO, exitmsg, strlen(exitmsg));//exit msg
        exit(EXIT_SUCCESS);
    } else {
        write(STDOUT_FILENO, "Bon nombre d'argument\n", strlen("Bon nombre d'argument\n"));
        for (int i = 0; i < argc; i++) {
            sprintf(argcmd, "%d : %s\n", i, argv[i]);
            write(STDOUT_FILENO, argcmd, strlen(argcmd));//affiche l'indice et valeur de arg[i]
        }
    }

}