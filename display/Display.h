#ifndef DISPLAY_H
#define	DISPLAY_H

typedef enum {
    ANODO_COMUM = 0, CATODO_COMUM = 1
} DisplayTipo;

typedef enum {
    ZERO, UM, DOIS, TRES, QUATRO, CINCO, SEIS, SETE, OITO, NOVE, DEZ,
    A, B, C, D, E, F
} Caractere;

typedef struct {
    unsigned int pins[8];
    unsigned int controle;
    DisplayTipo tipo;
    
    /**
     * @param caractere O caractere é impresso se o display estiver ligado
     */
    void (* caractere)(void *, Caractere caractere);
    /**
     * Liga o display se o pino de controle != NULL
     */
    void (* liga)(void *);
    /**
     * Desliga o display se o pino de controle != NULL
     */
    void (* desliga)(void *);
} Display7Seg;

void Display_init(Display7Seg * display, DisplayTipo tipo, unsigned int controle);

#endif	/* DISPLAY_H */

