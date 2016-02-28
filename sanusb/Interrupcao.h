#ifndef INTERRUPCAO_H
#define	INTERRUPCAO_H

#define timer0                0xF220
#define timer1                0x9D01
#define timer2                0x9D02
#define timer3                0xA002

#define ext0                  0xF210
#define ext1                  0xF008
#define ext2                  0xF010

#define ad                    0x9D40
#define recep_serial          0x9D20

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

#endif
