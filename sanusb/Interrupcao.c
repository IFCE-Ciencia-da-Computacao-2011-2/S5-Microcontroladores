#include "SanUSB1.h"
#include "Interrupcao.h"

/**
 * Resetar
 */
#pragma code _RESET_INTERRUPT_VECTOR = 0x001000
void _reset(void) {
    _asm goto _startup _endasm
}
#pragma code //Volta ao código do programa

/**
 * Interrupções - HIGH
 */
#pragma code _HIGH_INTERRUPT_VECTOR = 0x001008
void _high_ISR(void) {
    _asm goto interrupcao _endasm
}
#pragma code

/**
 * Interrupções - LOW - Desabilitado
 */
#pragma code _LOW_INTERRUPT_VECTOR = 0x001018
void _low_ISR(void) { ; }
#pragma code


void habilita_interrupcao(unsigned int tipo) { //Timer 0,1 ou 3, recep_serial
    RCONbits.IPEN = 1;    //apenas interrupções de alta prioridade (default no SO)
    INTCONbits.GIEH = 1;  //Habilita interrupções de alta prioridade (0x1008)
    switch(tipo) {
        case timer0: INTCONbits.TMR0IE = 1; T0CONbits.TMR0ON = 1; break;
        case timer1: PIE1bits.TMR1IE = 1;  T1CONbits.TMR1ON = 1;  break;
        case timer2: PIE1bits.TMR2IE = 1;  T2CONbits.TMR2ON = 1;  break;
        case timer3: PIE2bits.TMR3IE = 1;  T3CONbits.TMR3ON = 1;  break;

        //interrupção na borda de descida
        case ext0: INTCONbits.INT0IE = 1;  INTCON2bits.INTEDG0 = 0; break;
        case ext1: INTCON3bits.INT1IE = 1; INTCON2bits.INTEDG1 = 0; break;
        case ext2: INTCON3bits.INT2IE = 1; INTCON2bits.INTEDG2 = 0; break;
       
        case ad:           PIE1bits.ADIE = 1;                                                break;
        case recep_serial: PIE1bits.RCIE = 1;       IPR1bits.RCIP = 1;                       break; //RCIP - Prioridade
    }
}
