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

extern void Interrupcoes_init(void);

extern void interrupcao();

/**
 * @param indentificador Constante identificadora interrupção
 * @param funcao         Função a ser chamada
 * @param parametro      Parâmetro a ser passado a função
 */
extern void naInterrupcao(TipoInterrupcao tipo, void (* funcao)(void *), void * parametro);

#endif