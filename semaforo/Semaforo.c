#include <stdio.h>
#include <stdlib.h>

#include "sanusb/SanUSB1.h"
#include "Semaforo.h"

void Semaforo2_verde(void * self);
void Semaforo2_vermelho(void * self);

void Semaforo2_init(Semaforo2* semaforo, unsigned int vermelho, unsigned int verde) {
    semaforo->pino_vermelho = vermelho;
    semaforo->pino_verde = verde;
    
    semaforo->verde = &Semaforo2_verde;
    semaforo->vermelho = &Semaforo2_vermelho;
}


void Semaforo2_vermelho(void * self) {
    Semaforo2 * semaforo = (Semaforo2*) self;

    nivel_baixo(semaforo->pino_verde);
    nivel_alto(semaforo->pino_vermelho);
}

void Semaforo2_verde(void * self) {
    Semaforo2 * semaforo = (Semaforo2*) self;

    nivel_baixo(semaforo->pino_vermelho);
    nivel_alto(semaforo->pino_verde);
}


void Semaforo3_verde(void * self);
void Semaforo3_amarelo(void * self);
void Semaforo3_vermelho(void * self);


void Semaforo3_init(Semaforo3* semaforo, unsigned int vermelho, unsigned int amarelo, unsigned int verde) {
    semaforo->pino_vermelho = vermelho;
    semaforo->pino_amarelo = amarelo;
    semaforo->pino_verde = verde;

    semaforo->vermelho = &Semaforo3_vermelho;
    semaforo->amarelo = &Semaforo3_amarelo;
    semaforo->verde = &Semaforo3_verde;
    
    nivel_baixo(semaforo->pino_vermelho);
    nivel_baixo(semaforo->pino_amarelo);
    nivel_baixo(semaforo->pino_verde);
}

void Semaforo3_vermelho(void * self) {
    Semaforo3 * semaforo = (Semaforo3*) self;

    nivel_baixo(semaforo->pino_verde);
    nivel_baixo(semaforo->pino_amarelo);
    
    nivel_alto(semaforo->pino_vermelho);
}

void Semaforo3_amarelo(void * self) {
    Semaforo3 * semaforo = (Semaforo3*) self;

    nivel_baixo(semaforo->pino_verde);
    nivel_baixo(semaforo->pino_vermelho);
    
    nivel_alto(semaforo->pino_amarelo);
}

void Semaforo3_verde(void * self) {
    Semaforo3 * semaforo = (Semaforo3*) self;

    nivel_baixo(semaforo->pino_amarelo);
    nivel_baixo(semaforo->pino_vermelho);

    nivel_alto(semaforo->pino_verde);
}