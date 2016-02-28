#include <stdio.h>

#include "sanusb/SanUSB1.h"
#include "semaforo/Semaforo.h"
#include "semaforo/Sinal.h"
#include "InterrupcaoEventos.h"

void sinalizar(void * self) {
    Sinal * sinal = (Sinal *) self;

    sinal->sinalizado = true;
}

void Sinal_init(Sinal * sinal) {
    sinal->sinalizado = 0;

    Semaforo3_init(&sinal->semaforo, pin_b3, pin_b4, pin_b5);
    Semaforo2_init(&sinal->semaforoPedestre, pin_b6, pin_b7);
    
    sinal->sinalizar = &sinalizar;
}

void init();

void main() {
    Interrupcoes_init();
    clock_int_4MHz();

    init();
}

void rodarSemaforo(Sinal *sinal);
void rodarSemaforoPedestre(Sinal *sinal);

void init() {
    Sinal sinal;

    Sinal_init(&sinal);

    naInterrupcao(ext1, sinal.sinalizar, &sinal);

    sinal.semaforoPedestre.vermelho(&sinal.semaforoPedestre);

    while(1) {
        if(!entrada_pin_e3)
            Reset();

        rodarSemaforo(&sinal);
        
        if (sinal.sinalizado) {
            rodarSemaforoPedestre(&sinal);
            sinal.sinalizado = false;
        } else {
            tempo_ms(3000);
        }
    }
}

void rodarSemaforo(Sinal *sinal) {
    Semaforo3 *semaforo = &sinal->semaforo;

    semaforo->verde(semaforo);
    tempo_ms(2000);

    semaforo->amarelo(semaforo);
    tempo_ms(1000);

    semaforo->vermelho(semaforo);
}

void rodarSemaforoPedestre(Sinal *sinal) {
    Semaforo2 *semaforo = &sinal->semaforoPedestre;

    tempo_ms(1000);

    semaforo->verde(semaforo);
    tempo_ms(2000);

    semaforo->vermelho(semaforo);
    tempo_ms(1000);
}
