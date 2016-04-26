#include <stdio.h>

#include "sanusb/SanUSB1.h"
#include "display/Display.h"

#include "DisplayTimer.h"
#include "evento/InterrupcaoEventos.h"

#define ATUALIZACOES_POR_SEGUNDO 50
#define TOTAL_DISPLAYS 2
#define TEMPO_LED 1000 /(ATUALIZACOES_POR_SEGUNDO * TOTAL_DISPLAYS) // 1000 ms = 1 seg
#define TEMPO_LED_US TEMPO_LED * 1000

void intervaloCrescente(void * self, int inicio, int fim, unsigned int tempoMs);
void intervaloDecrescente(void * self, int inicio, int fim, unsigned int tempoMs);

void atualizarTimer(void * self);

void imprime(void * self);
void imprimeDisplay(Display7Seg * display, Caractere valor);

static char FLAG = 0;

void Display2Timer_init(Display2Timer * timer, DisplayTipo tipoUnidade, unsigned int controleUnidade, DisplayTipo tipoDezena, unsigned int controleDezena) {
    Display7Seg_init(&timer->unidade, tipoUnidade, controleUnidade);
    Display7Seg_init(&timer->dezena, tipoDezena, controleDezena);

    timer->emAndamento = false;

    timer->valorAtual = 0;
    timer->valorInicial = 0;
    timer->valorFinal = 0;

    timer->intervaloCrescente = &intervaloCrescente;
    timer->intervaloDecrescente = &intervaloDecrescente;
    

    naInterrupcao(TIMER1, &imprime, timer);
    multiplica_timer16bits(0, 2);
}


static void atualizarTimerCrescente(void * self) {
    Display2Timer * timer = (Display2Timer *) self;

    timer->valorAtual++;
    timer->emAndamento = timer->valorInicial <= timer->valorAtual && timer->valorAtual <= timer->valorFinal;
}

static void atualizarTimerDecrescente(void * self) {
    Display2Timer * timer = (Display2Timer *) self;

    timer->valorAtual--;        
    timer->emAndamento = timer->valorInicial >= timer->valorAtual && timer->valorAtual >= timer->valorFinal;
}


static void preparar(Display2Timer * timer, int inicio, int fim, void (*atualizador)(void * self));
void intervaloCrescente(void * self, int inicio, int fim, unsigned int tempoMs) {
    Display2Timer * timer = (Display2Timer *) self;

    preparar(timer, inicio, fim, &atualizarTimerCrescente);

    do {
        timer0_ms(tempoMs);
        atualizarTimer(timer);
    } while (timer->emAndamento);
}

void intervaloDecrescente(void * self, int inicio, int fim, unsigned int tempoMs) {
    Display2Timer * timer = (Display2Timer *) self;

    preparar(timer, inicio, fim, &atualizarTimerDecrescente);
    
    do {
        timer0_ms(tempoMs);
        atualizarTimer(timer);
    } while (timer->emAndamento);
}

static void preparar(Display2Timer * timer, int inicio, int fim, void (*atualizador)(void * self)) {
    timer->emAndamento = true;

    timer->valorInicial = inicio;
    timer->valorAtual = inicio;
    timer->valorFinal = fim;
    
    timer->atualizador = atualizador;

    habilitarInterrupcaoTempo(TIMER1, TEMPO_LED_US);
}

void atualizarTimer(void * self) {
    Display2Timer * timer = (Display2Timer *) self;

    timer->atualizador(timer);
}

/**
 * @param invervaloMs Intervalo que cada led deverá ficar aceso
 */
void imprime(void * self) {
    Display2Timer * timer = (Display2Timer *) self;
    if (timer->emAndamento)
        habilitarInterrupcaoTempo(TIMER1, TEMPO_LED_US);
    else
        return;

    FLAG = ~FLAG;
    if (FLAG) {
        timer->unidade.desliga(&timer->unidade);
        imprimeDisplay(&timer->dezena, (Caractere) timer->valorAtual/10);
        timer->dezena.liga(&timer->dezena);

    } else {
        timer->dezena.desliga(&timer->dezena);
        imprimeDisplay(&timer->unidade, (Caractere) timer->valorAtual%10);
        timer->unidade.liga(&timer->unidade);
    }
}

void imprimeDisplay(Display7Seg * display, Caractere valor) {
    display->caractere(display, valor);
}