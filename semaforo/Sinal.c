#include "sanusb/SanUSB1.h"
#include "Sinal.h"

void Sinal_sinalizar(void * self);


void Sinal_init(Sinal * sinal) {
    sinal->sinalizado = 0;

    Semaforo3_init(&sinal->semaforo, pin_b3, pin_b4, pin_b5);
    Semaforo2_init(&sinal->semaforoPedestre, pin_b6, pin_b7);
    
    sinal->sinalizar = &Sinal_sinalizar;
}

void Sinal_sinalizar(void * self) {
    Sinal * sinal = (Sinal *) self;

    sinal->sinalizado = true;
}