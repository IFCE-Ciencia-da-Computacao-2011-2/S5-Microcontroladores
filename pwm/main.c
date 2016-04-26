#include <stdio.h>

#include "sanusb/SanUSB1.h"
#include "evento/InterrupcaoEventos.h"

#include "../TimerZero.h"
#include "main.h"

unsigned int lerSensor(short int posicao, short int maximo) {
    return (le_AD8bits(posicao)*maximo)/255;
}

void interrompido(int * valor) {
    SetaPWM1(10, 50);
    *valor += 10;
    if (*valor >= 100)
        *valor = 0;
}

void start_pwm() {
    //TimerZero t0;
    unsigned int leituraSensor = 0;
    boolean estado = false;
    
    //naInterrupcao(TIMER0, &interrompido, &teste);
    
    //multiplica_timer16bits(0, 2);
    //tempo_timer16bits(0, 10000);

    //TimerZero_init(&t0);
    //t0.setPeriodo(1000000);
    //t0.on();

    habilita_canal_AD(AN0_a_AN1);
    //saida_pino(pin_a0, 1);

    while(1) {
        if (!entrada_pin_e3) {
            //Reset();
            if (estado == false)
                estado = true;
            else
                estado = false;
            tempo_ms(200);
        }
            

        leituraSensor = lerSensor(0, 100);
        
        if (estado) {
            if (leituraSensor > 60) {
                SetaPWM1(10, 0);
            } else {
                SetaPWM1(10, 100);
            }
        } else {
            SetaPWM1(10, 100 - leituraSensor);
        }
        //SetaPWM2(10, lerPotenciometro(1, 100));

        tempo_ms(50);

        /*
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
        */
    }
}