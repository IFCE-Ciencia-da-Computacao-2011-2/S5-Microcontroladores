#ifndef SINAL_H
#define	SINAL_H

#include "semaforo/Semaforo.h"

typedef struct {
    Semaforo3 semaforo;
    Semaforo2 semaforoPedestre;
    int sinalizado;
    void (* sinalizar)(void *);
} Sinal;

#endif

