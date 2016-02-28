#ifndef SEMAFORO_H
#define	SEMAFORO_H

#include <stdio.h>

typedef struct {
    unsigned int pino_vermelho;
    unsigned int pino_verde;
    
    /**
     * Mudar luz para vermelho
     * 
     * @param void * Semaforo2
     */
    void (* vermelho)(void *);
    
    /**
     * Mudar luz para verde
     * 
     * @param void * Semaforo2
     */
    void (* verde) (void *);
} Semaforo2;

typedef struct {
    unsigned int pino_vermelho;
    unsigned int pino_amarelo;
    unsigned int pino_verde;
    
    /**
     * Mudar luz para vermelho
     * 
     * @param void * Semaforo3
     */
    void (* vermelho)(void *);
    
    /**
     * Mudar luz para amarelo
     * 
     * @param void * Semaforo3
     */
    void (* amarelo) (void *);
    
    /**
     * Mudar luz para verde
     * 
     * @param void * Semaforo3
     */
    void (* verde) (void *);
} Semaforo3;

extern void Semaforo2_init(Semaforo2* semaforo, unsigned int vermelho, unsigned int verde);

extern void Semaforo3_init(Semaforo3* semaforo, unsigned int vermelho, unsigned int amarelo, unsigned int verde);

#endif