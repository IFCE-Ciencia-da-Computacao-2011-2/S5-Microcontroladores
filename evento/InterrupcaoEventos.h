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
 * @param indentificador Constante identificadora interrup��o
 * @param funcao         Fun��o a ser chamada
 * @param parametro      Par�metro a ser passado a fun��o
 */
extern void naInterrupcao(TipoInterrupcao tipo, void (* funcao)(void *), void * parametro);

#endif