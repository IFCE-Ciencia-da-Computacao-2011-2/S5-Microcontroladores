#include <stdio.h>

#include "sanusb/SanUSB1.h"
#include "display/Display.h"

#include "DisplayTimer.h"

#define ATUALIZACOES_POR_SEGUNDO 50
#define TOTAL_DISPLAYS 2
#define TEMPO_LED 1000 /(ATUALIZACOES_POR_SEGUNDO * TOTAL_DISPLAYS) // 1000 ms = 1 seg

void intervaloCrescente(void * self, unsigned int inicio, unsigned int fim, unsigned int tempoMs);
void intervaloDecrescente(void * self, unsigned int inicio, unsigned int fim, unsigned int tempoMs);

void imprime(Display2Timer * timer, unsigned int valor, unsigned int totalPermuta);
void imprimeDisplay(Display7Seg * display, Caractere valor);


void Display2Timer_init(Display2Timer * timer, DisplayTipo tipoUnidade, unsigned int controleUnidade, DisplayTipo tipoDezena, unsigned int controleDezena) {
    Display7Seg_init(&timer->unidade, tipoUnidade, controleUnidade);
    Display7Seg_init(&timer->dezena, tipoDezena, controleDezena);

    timer->intervaloCrescente = &intervaloCrescente;
    timer->intervaloDecrescente = &intervaloDecrescente;
}

void intervaloCrescente(void * self, unsigned int inicio, unsigned int fim, unsigned int tempoMs) {
    Display2Timer * timer = (Display2Timer *) self;
    unsigned int valor = inicio;

    for (; valor<=fim; valor++)
        imprime(timer, valor, tempoMs);
}

void intervaloDecrescente(void * self, unsigned int inicio, unsigned int fim, unsigned int tempoMs) {
    Display2Timer * timer = (Display2Timer *) self;
    unsigned int valor = inicio;
    unsigned int max = 0 -1;

    unsigned int totalPermuta = (ATUALIZACOES_POR_SEGUNDO * TOTAL_DISPLAYS) * tempoMs/1000;

    for (; valor>=fim && valor < max; valor--)
        imprime(timer, valor, totalPermuta);
}

/**
 * @param invervaloMs Intervalo que cada led deverá ficar aceso
 */
void imprime(Display2Timer * timer, unsigned int valor, unsigned int totalPermuta) {

    for (;totalPermuta != 0; totalPermuta--) {
        imprimeDisplay(&timer->dezena, (Caractere) valor/10);
        imprimeDisplay(&timer->unidade, (Caractere) valor%10);
    }
}

void imprimeDisplay(Display7Seg * display, Caractere valor) {
    display->caractere(display, valor);
    display->liga(display);
    tempo_ms(TEMPO_LED);
    display->desliga(display);
}