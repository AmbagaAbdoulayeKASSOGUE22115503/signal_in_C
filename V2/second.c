#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include "commun.h"


int main(int argc, char *argv[])
{
    pid_t monPid = getpid();
    pid_t pidPremier;

    if(argc!=2)
        fprintf(stderr, "usage : %s pidPremier\n", argv[0]);

    pidPremier = (pid_t)atol(argv[1]);
    initialiserAlternance();
    printf("Pid second = %lu\n", (unsigned long)monPid);
    traitementPremier(pidPremier , "Second");

    return 0;
}
