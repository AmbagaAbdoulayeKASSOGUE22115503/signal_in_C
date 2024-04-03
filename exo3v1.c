#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include "commun.h"

int main(int argc, const char argv[])
{
    pid_t pidFils;
    //initialiser l'alternance
    initialiserAlternance();
    //créer le fils==le second
    switch(pidFils=fork())
    {
        case -1: erreur("echec fork",1); break;
        case 0: traitementSecond(getppid(),"fils second"); break;
        default: traitementPremier(pidFils, "Père premier"); break;

    }

    return 0;
}
