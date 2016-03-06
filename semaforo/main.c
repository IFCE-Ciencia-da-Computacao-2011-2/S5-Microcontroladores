#include <stdio.h>

#include "evento/InterrupcaoEventos.h"
#include "sanusb/SanUSB1.h"

#include "display/Display.h"
#include "display/DisplayTimer.h"

#include "Semaforo.h"
#include "Sinal.h"

#include "main.h"

/**
 * Exemplo de uso para semáforo
 */
void initDisplay(Display7Seg * display);

void rodarSemaforo(Sinal *sinal);
void rodarSemaforoPedestre(Sinal *sinal, Display2Timer *timer);

void start() {
    Sinal sinal;
    Display2Timer timer;

    Display2Timer_init(&timer, CATODO_COMUM, pin_b0, ANODO_COMUM, pin_c2);

    initDisplay(&timer.unidade);
    initDisplay(&timer.dezena);

    Sinal_init(&sinal);

    naInterrupcao(EXT1, sinal.sinalizar, &sinal);

    sinal.semaforo.verde(&sinal.semaforo); //Faz dar erro na hora de gravar
    sinal.semaforoPedestre.vermelho(&sinal.semaforoPedestre);

    while(1) {
        if (!entrada_pin_e3)
            Reset();

        sinal.semaforo.verde(&sinal.semaforo);
        tempo_ms(10000);

        if (sinal.sinalizado) {
            rodarSemaforo(&sinal);
            rodarSemaforoPedestre(&sinal, &timer);

            sinal.sinalizado = false;
        }
    }
}

void rodarSemaforo(Sinal *sinal) {
    Semaforo3 *semaforo = &sinal->semaforo;

    semaforo->amarelo(semaforo);
    tempo_ms(3000);

    semaforo->vermelho(semaforo);
}


void desliga(Display7Seg * display) {
    display->desliga(display);
}

void rodarSemaforoPedestre(Sinal * sinal, Display2Timer * timer) {
    Semaforo2 *semaforo = &sinal->semaforoPedestre;

    tempo_ms(500);

    semaforo->verde(semaforo);
    timer->intervaloDecrescente(timer, 10, 0, 250);
    tempo_ms(100);
    desliga(&timer->dezena);
    desliga(&timer->unidade);

    semaforo->vermelho(semaforo);
    tempo_ms(500);
}

void initDisplay(Display7Seg * display) {
    display->pins[0] = pin_c0;
    display->pins[1] = pin_c1;
    display->pins[2] = pin_a2;
    display->pins[3] = pin_a1;
    
    display->pins[4] = pin_a0;
    display->pins[5] = pin_a5;
    display->pins[6] = pin_a4;
    display->pins[7] = pin_a3;
}