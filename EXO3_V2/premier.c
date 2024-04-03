#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include "commun.h"


int main(void)
{
    pid monPid = getpid();
    pid_t pidSecond;

    initialiserAlternance();
    printf("Pid premier = %lu\n", (unsigned long)monPid);
    scanf("%lu",&pidSecond);
    traitementPremier(pidSecond , "Premier");

    return 0;
}
