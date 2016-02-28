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
} Interrupcoes;

typedef enum {
    EXT0 = ext0,
    EXT1 = ext1,
    EXT2 = ext2
} TipoInterrupcao;

static const Interrupcoes interrupcoes;

extern void Interrupcoes_init() {
    interrupcoes.b0.funcao = NULL;
    interrupcoes.b0.parametro = NULL;
    interrupcoes.b1.funcao = NULL;
    interrupcoes.b1.parametro = NULL;
    interrupcoes.b2.funcao = NULL;
    interrupcoes.b2.parametro = NULL;
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
    else
        return;

    habilita_interrupcao(tipo);

    interrupcao->funcao = funcao;
    interrupcao->parametro = parametro;
}

#endif