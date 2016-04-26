#ifndef DISPLAYTIMER_H
#define	DISPLAYTIMER_H

/**
 * Timer para dois displays
 */
typedef struct {
    Display7Seg dezena;
    Display7Seg unidade;
    
    int valorInicial;
    int valorFinal;
    int valorAtual;

    boolean emAndamento;
    
    /**
     * Conta de [inicio..fim]
     * 
     * @param inicio Valor inicial do cron�metro
     * @param fim Valor final do cron�metro (inclusive)
     * @param tempoMs tempo (em milissegundos) em que o valor incrementa
     */
    void (*intervaloCrescente)(void *, int inicio, int fim, unsigned int tempoMs);
    
    /**
     * Conta de [inicio..fim]
     * 
     * @param inicio Valor inicial do cron�metro
     * @param fim Valor final do cron�metro (inclusive)
     * @param tempoMs tempo (em milissegundos) em que o valor incrementa
     */
    void (*intervaloDecrescente)(void *, int inicio, int fim, unsigned int tempoMs);
    
    /**
     * Fun��o respons�vel por atualizar tempo
     * 
     * N�o chame-a! Ela � interna do sistema
     */
    void (*atualizador)(void * self);
} Display2Timer;

extern void Display2Timer_init(Display2Timer * timer, DisplayTipo tipoUnidade, unsigned int controleUnidade, DisplayTipo tipoDezena, unsigned int controleDezena);

#endif