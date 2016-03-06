#ifndef SINAL_H
#define	SINAL_H

#include "semaforo/Semaforo.h"
#include "display/Display.h"

#include "sanusb/SanUSB1.h"

typedef struct {
    Semaforo3 semaforo;
    Semaforo2 semaforoPedestre;
    boolean sinalizado;
    void (* sinalizar)(void *);
} Sinal;

extern void Sinal_init(Sinal * sinal);
#endif

