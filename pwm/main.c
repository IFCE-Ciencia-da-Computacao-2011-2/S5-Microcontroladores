#include <stdio.h>

#include "evento/InterrupcaoEventos.h"
#include "sanusb/SanUSB1.h"

#include "main.h"

typedef struct {
    unsigned int pin;
    unsigned char valor;
    unsigned char step;
    unsigned char maximo;
} Led;

void aumentarLuz(Led * led);
void baixarLuz(Led * led);

void start_pwm() {
    int i = 0;
    Led led = {pin_b7, 0, 5, 100};

    naInterrupcao(EXT1, &aumentarLuz, &led);
    //naInterrupcao(EXT2, &baixarLuz, &led);

    while(1) {
        if (!entrada_pin_e3)
            Reset();
        /*if (!entrada_pin_e3) {
            baixarLuz(&led);
            tempo_ms(100);
        }*/
        for (i=0; i<=80; i++) {
            SetaPWM1(10, i);
            tempo_ms(20);
        }
        for (i=0; i<=80; i++) {
            SetaPWM2(10, i);
            tempo_ms(20);
        }
        for (i=80; i>0; i--) {
            SetaPWM2(10, i);
            tempo_ms(20);
        }
        for (i=80; i>0; i--) {
            SetaPWM1(10, i);
            tempo_ms(20);
        }
    }
}

void aumentarLuz(Led * led) {
    if (led->valor >= led->maximo)
        return;

    led->valor += led->step;
    SetaPWM1(10000, led->valor);
    tempo_ms(100);
}

void baixarLuz(Led * led) {
    if (led->valor == 0)
        return;

    led->valor -= led->step;
    SetaPWM1(10000, 0);
}