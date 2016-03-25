#include <stdio.h>

#include "evento/InterrupcaoEventos.h"
#include "sanusb/SanUSB1.h"

#include "display/Display.h"

#include "main.h"

void start_bluetooth() {
    
}
/*
void initDisplay(Display7Seg * display);

void atualizarDisplay(Display7Seg * display);

void start_bluetooth() {
    Display7Seg display;

    Display7Seg_init(&display, ANODO_COMUM, pin_c2);

    initDisplay(&display);

    naInterrupcao(SERIAL, &atualizarDisplay, &display);

    while(1) {
        if (!entrada_pin_e3)
            Reset();
    }
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

void atualizarDisplay(Display7Seg * display) {
    unsigned char comando = le_serial();
    display->caractere(display, comando);
}
 **/