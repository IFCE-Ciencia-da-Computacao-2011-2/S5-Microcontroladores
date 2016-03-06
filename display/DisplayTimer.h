#ifndef DISPLAYTIMER_H
#define	DISPLAYTIMER_H

/**
 * Timer para dois displays
 */
typedef struct {
    Display7Seg dezena;
    Display7Seg unidade;
    
    /**
     * Conta de [inicio..fim]
     * 
     * @param inicio Valor inicial do cronômetro
     * @param fim Valor final do cronômetro (inclusive)
     * @param tempoMs tempo (em milissegundos) em que o valor incrementa
     */
    void (*intervaloCrescente)(void *, unsigned int inicio, unsigned int fim, unsigned int tempoMs);
    
    /**
     * Conta de [inicio..fim]
     * 
     * @param inicio Valor inicial do cronômetro
     * @param fim Valor final do cronômetro (inclusive)
     * @param tempoMs tempo (em milissegundos) em que o valor incrementa
     */
    void (*intervaloDecrescente)(void *, unsigned int inicio, unsigned int fim, unsigned int tempoMs);
} Display2Timer;

extern void Display2Timer_init(Display2Timer * timer, DisplayTipo tipoUnidade, unsigned int controleUnidade, DisplayTipo tipoDezena, unsigned int controleDezena);

#endif