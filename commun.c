#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

//déclaration de variables globales
bool tourRecu = false;
sigset_t ens; //sigsuspend

void erreur(char *message, int exitNumber)
{
    perror(message);
    exit(exitNumber);
}

//Traitement du signal SIGUSR1
void traiterSignal(int sig)
{
    tourRecu = true;
}

void attendreTour()
{
    while(!tourRecu)
         sigsuspend(&ens);
}

void donnerTour(pid_t aQui)
{
    tourRecu = false;
    if(kill(aQui, SIGUSR1)==-1)
        erreur("erreur kill", 1);
}

void traitementPremier(pid_t pidSecond, const char *messTrace)
{
    pid_t mon_pid = getpid();
    while(true)
    {
        printf("Processus %s de pid %lu s'éxécute\n", messTrace, (unsigned long)mon_pid);
        sleep(1);
        printf("Process %s de pid %lu donne le tour à %lu \n", messTrace, (unsigned long)mon_pid, (unsigned long) pidSecond);
        donnerTour(pidSecond);
        attendreTour();
            
    }

}

void traitementSecond(pid_t pidPremier, const char *messTrace)
{
    pid_t mon_pid = getpid();
    while(true)
    {
        attendreTour();
        printf("Processus %s de pid %lu s'éxécute\n", messTrace, (unsigned long)mon_pid);
        sleep(1);
        printf("Process %s de pid %lu donne le tour à %lu \n", messTrace, (unsigned long)mon_pid, (unsigned long) pidPremier);
        donnerTour(pidPremier);
            
    }

}

void initialiserAlternance()
{
    //intercepter SIGUSR1
    struct sigaction action;
    action.sa_handler = traiterSignal;
    action.sa_flags =0;
    sigemptyset( &action.sa_mask);

    if(sigaction(SIGUSR1, &action, NULL)==-1)
    {
        erreur("echec sigaction", 2);
    }

    //bloquer SIGUSR1
    sigprocmask(SIG_SETMASK, NULL, &ens);
    sigaddset(&ens, SIGUSR1);  //ajout de USR1 pour le bloquer
    sigprocmask(SIG_SETMASK, &ens, NULL);
    sigdelset(&ens, SIGUSR1);



}
