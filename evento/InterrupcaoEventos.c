#include <stdio.h>

#include "InterrupcaoEventos.h"

void Interrupcoes_init() {
    interrupcoes.b0.funcao = NULL;
    interrupcoes.b0.parametro = NULL;
    interrupcoes.b1.funcao = NULL;
    interrupcoes.b1.parametro = NULL;
    interrupcoes.b2.funcao = NULL;
    interrupcoes.b2.parametro = NULL;

    interrupcoes.timerZero.funcao = NULL;
    interrupcoes.timerZero.parametro = NULL;
    
    interrupcoes.timerUm.funcao = NULL;
    interrupcoes.timerUm.parametro = NULL;
    interrupcoes.timerTres.funcao = NULL;
    interrupcoes.timerTres.parametro = NULL;
}

#pragma interrupt interrupcao
void interrupcao() {
    Interrupcao *interrupcao = NULL;

    if (ext0_interrompeu) {
        ext0_interrompeu = 0;
        interrupcao = &interrupcoes.b0;

    } else if (ext1_interrompeu) {
        ext1_interrompeu = 0;
        interrupcao = &interrupcoes.b1;

    } else if (ext2_interrompeu) {
        ext2_interrompeu = 0;
        interrupcao = &interrupcoes.b2;
    
    } else if (timer0_interrompeu) {
        timer0_interrompeu = 0;
        interrupcao = &interrupcoes.timerZero;

    } else if (timer1_interrompeu) {
        timer1_interrompeu = 0;
        interrupcao = &interrupcoes.timerUm;

    } else if (timer3_interrompeu) {
        timer3_interrompeu = 0;
        interrupcao = &interrupcoes.timerTres;

    } else if (serial_interrompeu) {
        serial_interrompeu = 0;
        interrupcao = &interrupcoes.serial;

    } else
        return;
    
    if (interrupcao->funcao == NULL)
        return;
    
    interrupcao->funcao(interrupcao->parametro);
}

/**
 * @param indentificador Constante identificadora interrupção
 * @param funcao         Função a ser chamada
 * @param parametro      Parâmetro a ser passado a função
 */
extern void naInterrupcao(TipoInterrupcao tipo, void (* funcao)(void *), void * parametro) {
    Interrupcao * interrupcao = NULL;

    if (tipo == EXT0)
        interrupcao = &interrupcoes.b0;
    else if (tipo == EXT1)
        interrupcao = &interrupcoes.b1;
    else if (tipo == EXT2)
        interrupcao = &interrupcoes.b2;
    else if (tipo == SERIAL)
        interrupcao = &interrupcoes.serial;
    
    if (tipo == TIMER0)
        interrupcao = &interrupcoes.timerZero;
    else if (tipo == TIMER1)
        interrupcao = &interrupcoes.timerUm;
    else if (tipo == TIMER3)
        interrupcao = &interrupcoes.timerTres;

    else //Habilitar if interrupção != timer
        habilita_interrupcao(tipo);


    if (interrupcao == NULL)
        return;

    interrupcao->funcao = funcao;
    interrupcao->parametro = parametro;
}

void habilitarInterrupcaoTempo(TipoInterrupcao tipo, unsigned int tempoUs) {
    char timer = 0;

    switch(tipo) {
        case TIMER0: timer = 0; break;
        case TIMER1: timer = 1; break;
        //case TIMER2: timer = 2; break;
        case TIMER3: timer = 3; break;
        default: return;
    }

    tempo_timer16bits(timer, tempoUs);
    habilita_interrupcao(tipo);
}