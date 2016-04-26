#ifndef INTERRUPCAO_EVENTOS_H
#define	INTERRUPCAO_EVENTOS_H

#include "sanusb/SanUSB1.h"
#include "sanusb/Interrupcao.h"

typedef struct {
    void (* funcao)(void *);
    void * parametro;
} Interrupcao;

typedef struct {
    Interrupcao b0;
    Interrupcao b1;
    Interrupcao b2;
    Interrupcao timerZero;
    Interrupcao timerUm;
    Interrupcao timerTres;
    Interrupcao serial;
} Interrupcoes;

typedef enum {
    EXT0 = ext0,
    EXT1 = ext1,
    EXT2 = ext2,
    TIMER0 = timer0,
    TIMER1 = timer1,
    TIMER3 = timer3,
    SERIAL = recep_serial
} TipoInterrupcao;

static const Interrupcoes interrupcoes;

extern void Interrupcoes_init(void);

extern void interrupcao();

/**
 * @param indentificador Constante identificadora interrupção
 * @param funcao         Função a ser chamada
 * @param parametro      Parâmetro a ser passado a função
 */
extern void naInterrupcao(TipoInterrupcao tipo, void (* funcao)(void *), void * parametro);

/**
 * Atribui o tempo para disparo da interrupção de tempo e a habilita
 * 
 * @param tipo    Tipo de interrupção de tempo que deseja ativar
 * @param tempoUs Tempo em µs que deverá ocorrer a interrupção
 */
extern void habilitarInterrupcaoTempo(TipoInterrupcao tipo, unsigned int tempoUs);

#endif