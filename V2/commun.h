#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#ifndef ALTERNANCE_H
#define ALTERNANCE_H


void initialiserAlternance();
void attendreTour();
void donnerTour(pid_t aQui);
void traitementPremier(pid_t pidSecond, const char* messTrace);
void traitementSecond(pid_t pidPremier, const char *messTrace);
void erreur(char *message, int exitNumber);

#endif
