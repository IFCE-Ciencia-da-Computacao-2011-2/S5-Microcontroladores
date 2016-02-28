#include <stdio.h>

#include "SanUSB1.h"
#include "semaforo/Semaforo.h"
#include "semaforo/Sinal.h"
#include "Interrupcao.h"

void sinalizar(void * self) {
    Sinal * sinal = (Sinal *) self;

    sinal->sinalizado = true;
}

void Sinal_init(Sinal * sinal) {
    sinal->sinalizado = 0;

    Semaforo3_init(&sinal->semaforo, pin_b7, pin_b6, pin_b5);
    Semaforo2_init(&sinal->semaforoPedestre, pin_b4, pin_b3);
    
    sinal->sinalizar = &sinalizar;
}

void rodarSemaforo(Sinal *sinal);
void rodarSemaforoPedestre(Sinal *sinal);

Sinal sinal;

void main() {
    //habilita_interrupcao(ext1);
    Interrupcoes_init();
    clock_int_4MHz();

    Sinal_init(&sinal);
    
    sinal.semaforoPedestre.vermelho(&sinal.semaforoPedestre);
    
    naInterrupcao(ext1, sinal.sinalizar, &sinal);
    
    while(1) {
        if(!entrada_pin_e3)
            Reset();
        
        rodarSemaforo(&sinal);

        if (sinal.sinalizado)
            rodarSemaforoPedestre(&sinal);
        else
            tempo_ms(3000);
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

    // No fim, pois se alguém sinalizar durante o semáforo de pedestre
    // não deve chamar
    sinal->sinalizado = false;
}
