#include <stdio.h>

#include "evento/InterrupcaoEventos.h"
#include "sanusb/SanUSB1.h"
#include "Semaforo.h"
#include "Sinal.h"

/**
 * Exemplo de uso para semáforo
 */

void rodarSemaforo(Sinal *sinal);
void rodarSemaforoPedestre(Sinal *sinal);

void start() {
    Sinal sinal;

    Sinal_init(&sinal);

    naInterrupcao(ext1, sinal.sinalizar, &sinal);

    sinal.semaforo.verde(&sinal.semaforo);
    sinal.semaforoPedestre.vermelho(&sinal.semaforoPedestre);

    while(1) {
        if(!entrada_pin_e3)
            Reset();

        sinal.semaforo.verde(&sinal.semaforo);
        tempo_ms(1000);
        tempo_ms(1000);
        tempo_ms(1000);
        tempo_ms(1000);
        

        if (sinal.sinalizado) {
            rodarSemaforo(&sinal);
            rodarSemaforoPedestre(&sinal);

            sinal.sinalizado = false;
        }
    }
}

void rodarSemaforo(Sinal *sinal) {
    Semaforo3 *semaforo = &sinal->semaforo;

    semaforo->verde(semaforo);

    semaforo->amarelo(semaforo);
    tempo_ms(3000);

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
