#include <stdio.h>

#include "evento/InterrupcaoEventos.h"
#include "sanusb/SanUSB1.h"
#include "semaforo/main.h"

#include "display/Display.h"

void initDisplay(Display7Seg * display, DisplayTipo tipo, unsigned int controle);
void exemplo(Display7Seg * display);

void main() {
    Display7Seg display;
    Display7Seg displayDezena;

    Interrupcoes_init();
    clock_int_4MHz();

    //start();

    initDisplay(&display, ANODO_COMUM, pin_b0);
    initDisplay(&displayDezena, CATODO_COMUM, pin_c2);
    
    //saida_pino(pin_c2, 0);
    
    while (1) {
        if (!entrada_pin_e3)
            Reset();
        
        display.liga(&display);
        exemplo(&display);
        display.desliga(&display);
        
        displayDezena.liga(&displayDezena);
        exemplo(&displayDezena);
        displayDezena.desliga(&displayDezena);
    }
}

void initDisplay(Display7Seg * display, DisplayTipo tipo, unsigned int controle) {
    Display_init(display, tipo, controle);
    
    display->pins[0] = pin_c0;
    display->pins[1] = pin_c1;
    display->pins[2] = pin_a4;
    display->pins[3] = pin_a1;
    
    display->pins[4] = pin_a0;
    display->pins[5] = pin_a3;
    display->pins[6] = pin_a2;
    display->pins[7] = pin_a5;
}

void exemplo(Display7Seg * display) {
    int i = 0;

    for (i = 0; i < 16; i++) {
        display->caractere(display, (Caractere) i);
        tempo_ms(300);
    }
}