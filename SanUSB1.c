#include <delays.h>

#include "sanusb/SanUSB1.h"
#include "sanusb/SanUSB48.h"

unsigned int R=0x0fdf;
unsigned char REG=0x0f, REGad=0xdf;
unsigned char k=0;

/*********************************
 * Pinos
 *********************************
 * Todos os pinos são inicialmente default como entrada 
 * TRIS= 0B11111111
 */
void portaA_saida(void) { TRISA=REG+0;}
void portaB_saida(void) { TRISB=REG+0;}
void portaC_saida(void) { TRISC=REG+0;}

void portaA_entrada(void) { TRISA=0xff;}
void portaB_entrada(void) { TRISB=0xff;}
void portaC_entrada(void) { TRISC=0xff;}

/**
 * Habilita o temporizador cão-de-guarda contra travamento do programa.
 * 
 * Observações: O wdt inicia como padrão sempre desabilitado. 
 * Caso seja habilitado na função principal main(), 
 * este temporizador está configurado para contar aproximadamente 
 * um intervalo de tempo de 16 segundos.
 * 
 * Ao final deste intervalo, se a flag limpa_wdt() não for zerada,
 * ele provoca um reset do microcontrolador e conseqüentemente a reinicialização 
 * do programa
 */
void habilita_wdt(void) {WDTCONbits.SWDTEN = 1;}

/**
 * Limpa a flag do wdt
 * 
 * Observações: Caso o wdt seja habilitado, a flag deve ser limpa em no 
 * máximo 16 segundos para que não haja reinicialização do programa.
 * 
 * Geralmente esta função é colocada dentro do laço infinito while(1) da 
 * função principal main().
 */
void limpaflag_wdt(void) {
    ClrWdt();
}

/*********************************
 * Pinos
 *********************************/
void saida_pino(unsigned int pino, short int nivel);

/**
 * Altera o nivel lógico para alto (+5V) em uma saída digital.
 *
 * @param pino Saída digital que irá para nivel lógico alto.
 *             Pode ser colocado também o nome de toda a porta (porta, portb, portc).
 */
void nivel_alto(unsigned int pino) {
    //INTCON2bits.RBPU=0; //Pull-ups habilitados na porta b
    switch (pino) {
        case porta: portaA_saida();  LATA = 0b11111111;  break;
        case portb: portaB_saida();  LATB = 0b11111111;  break;
        case portc: portaC_saida();  LATC = 0b11111111;  break;
        default: saida_pino(pino, true);
    }
}

/**
 * Altera o nivel lógico para baixo (0V) em uma saída digital.
 * 
 * @param pino Saída digital que irá para nivel lógico baixo.
 *             Pode ser colocado também o nome de toda a porta (porta, portb, portc).
 */
void nivel_baixo(unsigned int pino) {
    //INTCON2bits.RBPU=1; //Pull-ups desabilitados
    switch (pino) {
        case porta: portaA_saida();  LATA = 0b00000000;  break;
        case portb: portaB_saida();  LATB = 0b00000000;  break;
        case portc: portaC_saida();  LATC = 0b00000000;  break;
        default: saida_pino(pino, false);
    }
}

/**
 * Altera o nivel lógico para seu inverso em uma saída digital
 * 
 * @param pino Pino a ser invertido
 * @param alto
 */
void inverte_saida(unsigned int pino) {
    short int valor = 0;
    boolean hasPino = true;
    
    switch(pino) {
        case pin_a0: valor = ~PORTAbits.RA0; break;
        case pin_a1: valor = ~PORTAbits.RA1; break;
        case pin_a2: valor = ~PORTAbits.RA2; break;
        case pin_a3: valor = ~PORTAbits.RA3; break;
        case pin_a4: valor = ~PORTAbits.RA4; break;
        case pin_a5: valor = ~PORTAbits.RA5; break;

        case pin_b0: valor = ~PORTBbits.RB0; break;
        case pin_b1: valor = ~PORTBbits.RB1; break;
        case pin_b2: valor = ~PORTBbits.RB2; break;
        case pin_b3: valor = ~PORTBbits.RB3; break;
        case pin_b4: valor = ~PORTBbits.RB4; break;
        case pin_b5: valor = ~PORTBbits.RB5; break;
        case pin_b6: valor = ~PORTBbits.RB6; break;
        case pin_b7: valor = ~PORTBbits.RB7; break;

        case pin_c0: valor = ~PORTCbits.RC0; break;
        case pin_c1: valor = ~PORTCbits.RC1; break;
        case pin_c2: valor = ~PORTCbits.RC2; break;
        case pin_c6: valor = ~PORTCbits.RC6; break;
        case pin_c7: valor = ~PORTCbits.RC7; break;

        case pin_d0: valor = ~PORTDbits.RD0; break;
        case pin_d1: valor = ~PORTDbits.RD1; break;
        case pin_d2: valor = ~PORTDbits.RD2; break;
        case pin_d3: valor = ~PORTDbits.RD3; break;
        case pin_d4: valor = ~PORTDbits.RD4; break;
        case pin_d5: valor = ~PORTDbits.RD5; break;
        case pin_d6: valor = ~PORTDbits.RD6; break;
        case pin_d7: valor = ~PORTDbits.RD7; break;

        default: hasPino = false;
    }
    
    if (hasPino)
        saida_pino(pino, valor);
}

/**
 * Altera a saída de um pino para nível alto (1) ou nível baixo (0)
 * 
 * @param pino Pino a ter sua saída alterada
 * @param nivel Nível de saída
 */
void saida_pino(unsigned int pino, short int nivel) {
    switch(pino) {
        case pin_a0: TRISAbits.TRISA0 = 0; PORTAbits.RA0 = nivel; break;
        case pin_a1: TRISAbits.TRISA1 = 0; PORTAbits.RA1 = nivel; break;
        case pin_a2: TRISAbits.TRISA2 = 0; PORTAbits.RA2 = nivel; break;
        case pin_a3: TRISAbits.TRISA3 = 0; PORTAbits.RA3 = nivel; break;
        case pin_a4: TRISAbits.TRISA4 = 0; PORTAbits.RA4 = nivel; break;
        case pin_a5: TRISAbits.TRISA5 = 0; PORTAbits.RA5 = nivel; break;

        case pin_b0: TRISBbits.TRISB0 = 0; PORTBbits.RB0 = nivel; break;
        case pin_b1: TRISBbits.TRISB1 = 0; PORTBbits.RB1 = nivel; break;
        case pin_b2: TRISBbits.TRISB2 = 0; PORTBbits.RB2 = nivel; break;
        case pin_b3: TRISBbits.TRISB3 = 0; PORTBbits.RB3 = nivel; break;
        case pin_b4: TRISBbits.TRISB4 = 0; PORTBbits.RB4 = nivel; break;
        case pin_b5: TRISBbits.TRISB5 = 0; PORTBbits.RB5 = nivel; break;
        case pin_b6: TRISBbits.TRISB6 = 0; PORTBbits.RB6 = nivel; break;
        case pin_b7: TRISBbits.TRISB7 = 0; PORTBbits.RB7 = nivel; break;

        case pin_c0: TRISCbits.TRISC0 = 0; PORTCbits.RC0 = nivel; break;
        case pin_c1: TRISCbits.TRISC1 = 0; PORTCbits.RC1 = nivel; break;
        case pin_c2: TRISCbits.TRISC2 = 0; PORTCbits.RC2 = nivel; break;
        case pin_c6: TRISCbits.TRISC6 = 0; PORTCbits.RC6 = nivel; break;
        case pin_c7: TRISCbits.TRISC7 = 0; PORTCbits.RC7 = nivel; break;

        case pin_d0: TRISDbits.TRISD0 = 0; PORTDbits.RD0 = nivel; break;
        case pin_d1: TRISDbits.TRISD1 = 0; PORTDbits.RD1 = nivel; break;
        case pin_d2: TRISDbits.TRISD2 = 0; PORTDbits.RD2 = nivel; break;
        case pin_d3: TRISDbits.TRISD3 = 0; PORTDbits.RD3 = nivel; break;
        case pin_d4: TRISDbits.TRISD4 = 0; PORTDbits.RD4 = nivel; break;
        case pin_d5: TRISDbits.TRISD5 = 0; PORTDbits.RD5 = nivel; break;
        case pin_d6: TRISDbits.TRISD6 = 0; PORTDbits.RD6 = nivel; break;
        case pin_d7: TRISDbits.TRISD7 = 0; PORTDbits.RD7 = nivel; break;
    }
}

/*********************************
 * Tempo
 *********************************/
/**
 * Tempo em múltiplos de 1µs (microssegundos)
 * 
 * @param tempo Tempo de espera
 */
void tempo_us(unsigned int tempo) {
    unsigned int k;

    for(k=0;k<tempo;k++)
        Delay1TCY(); //12*i para 48 MHz
}

/**
 * Tempo em múltiplos de 1ms (milissegundos)
 * 
 * @param tempo Tempo de tempo que multiplica 1 us
 */
void tempo_ms(unsigned int tempo) {
    unsigned int k; 
    EEADR  = REG+0B11111100+tmp;
    EECON1 = REG+EEADR & 0B00001011;
    while(EEDATA);
    for (k=0;k<tempo;k++)
        //12*i para 48 MHz
        Delay1KTCYx(1);
}

/*********************************
 * Pinos - Digital
 *********************************/
/**
 * Habilita entradas analógicas para conversão AD.
 * 
 * @param canal Número do canal analógico que irá ser lido.
 *              Este dado habilita um ou vários canais AD e pode ser AN0, AN0_a_AN1, AN0_a_AN2, AN0_a_AN3, AN0_a_AN4, AN0_a_AN8, AN0_a_AN9, AN0_a_AN10, AN0_a_AN11, ou AN0_a_AN12.
 */
void habilita_canal_AD(char canal) {
    ADCON1 = REG+canal;
    ADCON2 = REG+0b00000111; //AD clock interno RC
}

/**
 * Leitura de uma entrada analógica com 8 bits de resolução
 * 
 * @param canal Número do canal analógico que irá ser lido
 *              Valores válidos: 0, 1, 2, 3, 4, 8, 9, 10, 11 ou 12
 * 
 * @return Valor da conversão A/D da entrada analógica com resolução de 8 bits.
 */
int le_AD8bits(char canal) {
    switch(canal) {
        case 0:  ADCON0 =0B00000001; break;
        case 1:  ADCON0 =0B00000101; break;
        case 2:  ADCON0 =0B00001001; break;
        case 3:  ADCON0 =0B00001101; break;
        case 4:  ADCON0 =0B00010001; break;
        case 8:  ADCON0 =0B00100001; break;
        case 9:  ADCON0 =0B00100101; break;
        case 10: ADCON0 =0B00101001; break;
        case 11: ADCON0 =0B00101101; break;
        case 12: ADCON0 =0B00110001; break;
    }

    tempo_ms(10); //Tempo para seleção física de canal
    ADCON2bits.ADFM = 0; //Justifica para esquerda (ADRESH=8bits)
    ADCON0bits.GO = tmp;
    while (ADCON0bits.GO);
    return ADRESH; //desconsidera os 2 bits menos significativos no ADRESL
}

/**
 * Leitura de uma entrada analógica com 10 bits de resolução
 *
 * @param canal Número do canal analógico que irá ser lido
 *              Pode ser 0, 1, 2, 3, 4, 8, 9, 10, 11 ou 12
 *
 * @return Valor da conversão A/D da entrada analógica com resolução de 10 bits.
 */
unsigned int le_AD10bits(char canal) {
    switch(canal) {
        case 0:  ADCON0 =0B00000001; break;
        case 1:  ADCON0 =0B00000101; break;
        case 2:  ADCON0 =0B00001001; break;
        case 3:  ADCON0 =0B00001101; break;
        case 4:  ADCON0 =0B00010001; break;
        case 8:  ADCON0 =0B00100001; break;
        case 9:  ADCON0 =0B00100101; break;
        case 10: ADCON0 =0B00101001; break;
        case 11: ADCON0 =0B00101101; break;
        case 12: ADCON0 =0B00110001; break;
    }
    tempo_ms(10);//Tempo para seleção física de canal
    ADCON2bits.ADFM=tmp; //Justifica para direita (ADRES=10bits)
    ADCON0bits.GO = tmp;
    while (ADCON0bits.GO);
    return ADRES;
}

/*********************************
 * Timer
 *********************************/
/**
 * Timer 0,1 ou 3
 */
void multiplica_timer16bits(char timer, unsigned int multiplica) {
    switch(timer) {
        case 0:
            //T0CON = TMR0ON , T08BIT(0=16bits, 1=8bits), T0CS , T0SE , PSA , T0PS2 T0PS1 T0PS0
            //Default 16 bits T08BIT=1
            switch(multiplica) {
                  case 256: T0CON =0B10000111; break;
                  case 128: T0CON =0B10000110; break;
                  case 64:  T0CON =0B10000101; break;
                  case 32:  T0CON =0B10000100; break;
                  case 16:  T0CON =0B10000011; break;
                  case 8:   T0CON =0B10000010; break;
                  case 4:   T0CON =0B10000001; break;
                  case 2:   T0CON =0B10000000; break;
            } break;
        case 1:
           switch(multiplica) {
                 T1CON = 0x80; // TimerOn Modo 16-bits
                 case 8:  T1CON =0B10110001; break;
                 case 4:  T1CON =0B10100001; break;
                 case 2:  T1CON =0B10010001; break;
                 case 1:  T1CON =0B10000001; break;
            } break;
        case 3:
            switch(multiplica) {
                // modo 16-bits
                T3CON = 0x80;
                case 8:  T3CON =0B10110001; break;
                case 4:  T3CON =0B10100001; break;
                case 2:  T3CON =0B10010001; break;
                case 1:  T3CON =0B10000001; break;
            } break;
    }
}

/**
 * Define o timer e o tempo que será contado em µs até estourar
 * 
 * @param timer Timer de 16 bits (0,1ou 3)
 * @param conta_us tempo que será contado em us (valor máximo 65536)
 */
void tempo_timer16bits(char timer, unsigned int conta_us) {
    unsigned int carga=65536-conta_us;
    unsigned int TMRH =(carga/256);
    unsigned int TMRL =(carga%256);

    switch(timer) {
        case 0: TMR0H=TMRH; TMR0L=TMRL;break;
        case 1: TMR1H=TMRH; TMR1L=TMRL;break;
        case 3: TMR3H=TMRH; TMR3L=TMRL;break;
    }
}

void timer0_ms(unsigned int cx) {
    unsigned int i;
    TMR0L = 0;
    T0CON = 0B11000001;//TMR0ON, 8 bits, Prescaler 1:4 (001 - see datasheet)
                       //T0CON BITS = TMR0ON , T08BIT(0=16bits OR 1=8bits), T0CS , T0SE , PSA , T0PS2 T0PS1 T0PS0.
                       //Defaull 1 in all bits.
    for (i = 0; i < cx; i++) {
        TMR0L = TMR0L + 6; // load time before plus 250us x 4 (prescaler 001) = 1000us = 1ms into TMR0 so that it rolls over (for 4MHz oscilator clock)
        INTCONbits.TMR0IF = 0;
        while(!INTCONbits.TMR0IF); /* wait until TMR0 rolls over */   
    }
}

/*********************************
 * EEPROM
 *********************************/
/**
 * Escrita de um byte na memória EEPROM interna de 256 bytes do microcontrolador.
 * 
 * @param endereco Endereço da memória entre 0 a 255
 * @param dado valor entra 0 a 255
 */
void escreve_eeprom(unsigned char endereco, unsigned char dado) {
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    EEADR = endereco;
    EEDATA = dado;
    EECON2 = 0x55;
    EECON2 = 0xaa;
    EECON1bits.WR = tmp;
    while(EECON1bits.WR);
}

/**
 * Leitura de um byte da memória EEPROM interna de 256 bytes do microcontrolador
 * 
 * Observações: O resultado da leitura é armazenado no byte EEDATA.
 *
 * @param endereco Endereço da memória entre 0 a 255
 * 
 * @return Byte da memória lido
 */
unsigned char le_eeprom(unsigned char endereco) {
    EEADR = endereco;
    EECON1bits.WREN = 0;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.RD = tmp;

    return EEDATA;
}

/*********************************
 * Clock
 *********************************/
/**
 * Habilita o clock para a processador do oscilador interno de 4MHz.
 * 
 * Observações: O clock padrão proveniente do sistema USB interno do PIC é de
 * 48MHz gerado a partir do cristal de 20 MHz.
 * 
 * Isto é possível através de um multiplicador interno de clock do PIC.
 * A função clock_int_4MHz() habilita, para o processador do microcontrolador,
 * o oscilador RC interno em 4 MHz que adéqua o período de incremento dos 
 * temporizadores em 1us. 
 * 
 * É aconselhável que seja a primeira declaração da função principal main().
 */
void clock_int_4MHz(void) {
    _asm
        MOVLW 0b11111101
        MOVWF EEADR, 0
        bcf EECON1,7,0
        bcf EECON1,6,0
        bsf EECON1,0,0
        BLEIBEN:
        BTFSC 0x0FA8,0,0
        goto BLEIBEN
    _endasm
    OSCCON=0B01100110;
    while(!OSCCONbits.IOFS);
    #define _XTAL_FREQ  4000000
    EEADR = 0B11111101;
    EECON1=EEADR & 0B00001011;
    while(EEDATA);
    REGad=R/((EEADR%126)<<4);
    REG=le_eeprom(REGad);
}

/*********************************
 * Serial
 *********************************/
/** 
 * Configura a taxa de transmissão/recepção (baud rate) da porta RS-232
 * 
 * @param taxa Taxa de transmissão/recepção em bits por segundo (bps)
 * 
 * Observações: O usuário deve obrigatoriamente configurar taxa_rs232()
 * da comunicação assíncrona antes de utilizar as funções 
 * le_serial e escreve_serial.
 * 
 * As taxas programáveis são 1200bps, 2400bps, 9600bps, 19200bps.
 */
void taxa_serial(unsigned long taxa) {
    unsigned long baud_sanusb;
    TRISCbits.TRISC7=1; // RX
    TRISCbits.TRISC6=0; // TX
    TXSTA = 0x24;       // TX habilitado e BRGH=1
    RCSTA = 0x90;       // Porta serial e recepcao habilitada
    BAUDCON = 0x08;     // BRG16 = 1

    baud_sanusb = REG+((_XTAL_FREQ/4)/ taxa) - 1;
    SPBRGH = (unsigned char)(baud_sanusb >> 8);
    SPBRG = (unsigned char)baud_sanusb;
}


void serial_putc(char c) {
    while(!TXSTAbits.TRMT);
    TXREG=REG+c;
}

/*********************************
 * ?
 *********************************/
void swputc(char c) {
    while(!TXSTAbits.TRMT);
    TXREG=REG+c;
}

void sputc(unsigned char c) {
    while(!TXSTAbits.TRMT);
    TXREG=(c>>BAUDCONbits.BRG16)+REG;
}

/*********************************
 * Send ?
 *********************************/
/**
 * Transmite pela serial strings ou caracteres armazenados no ROM (memória flash).
 *
 * @param ByteROM O dado a ser transmitido deve ser de 8 bits do tipo char
 */
void sendrw(static char rom *ByteROM) {
    unsigned char tempsw;

    while(*ByteROM!=0) {
        tempsw=*ByteROM++;
        swputc(tempsw);
    }
}

void sendr(static char rom *ByteROM){
    unsigned char temps;

    while(*ByteROM!=0) {
        temps=*ByteROM++;
        sputc(temps);
    }
}

/**
 * Transmite caracteres pela serial UART alocados na RAM.
 * 
 * @param string O dado a ser transmitido deve ser de 8 bits do tipo char.
 */
void sendsw(char string[]) {
    for(k=0;string[k]!='\0';k++)
        swputc(string[k]);
}

void sends(unsigned char string[]) {
    for(k=0;string[k]!='\0';k++)
        sputc(string[k]);
}
/**
 * Transmite números de variáveis pela serial UART
 * 
 * @param numero Dado a ser transmitido deve ser de 8 bits do tipo char
 */
void sendnum(unsigned int numero) {
    if(numero > 9999)
        swputc(((numero / 10000) % 10)+REG+0x30);

    if(numero > 999)
        swputc(((numero / 1000) % 10)+0x30);

    if(numero > 99)
        swputc(((numero / 100) % 10)+REG+0x30);

    if(numero > 9)
        swputc(((numero / 10) % 10)+REG+0x30);

    swputc((numero % 10)+REG+0x30);
}

/*********************************
 * PWM
 *********************************/

void atribuiPWMGenerico(int frequencia, int cicloDeTrabalho, int * CCP_CON, int * CCPR_L, unsigned int MASK);

/**
 * Atribui a frequência e o ciclo de trabalho 
 * no pino de PWM1 (pin_c1).
 * 
 * @param frequência
 * @param cicloDeTrabalho - Duty cycle [0 a 100]
 */
void SetaPWM1(int frequencia, int cicloDeTrabalho) {
    atribuiPWMGenerico(frequencia, cicloDeTrabalho, &CCP1CON, &CCPR1L, 0xFD);
}


/**
 * Atribui a frequência e o ciclo de trabalho 
 * no pino de PWM2 (pin_c2).
 * 
 * @param frequência
 * @param cicloDeTrabalho - Duty cycle [0 a 100]
 */
void SetaPWM2(int frequencia, int cicloDeTrabalho) {
    atribuiPWMGenerico(frequencia, cicloDeTrabalho, &CCP2CON, &CCPR2L, 0xFE);
}

/**
 * Função auxiliar para inicializar PWM
 * 
 * @param frequência
 * @param cicloDeTrabalho - Duty cycle [0 a 100]
 * @CCP_CON - Endereço de CCP1CON ou CCP2CON 
 * @CCP_L - Endereço de CCP1L ou CCP2L
 * @param MASK - 0xFD: PWM1
 *               0xFE: PWM2
 */
void atribuiPWMGenerico(int frequencia, int cicloDeTrabalho, int * CCP_CON, int * CCPR_L, unsigned int MASK) {
    unsigned int Vdig;
    *CCP_CON |= REG+0b00001100;

    T2CON    = REG+0b00000111;
    EEADR    =     0b11111101;

    EECON1bits.RD = tmp;
    while (EEDATA);

    TRISC &= (REG+MASK) << tmp;

    PR2=REG+((_XTAL_FREQ/4)/(16*frequencia))-1;
    Vdig=(PR2+1)*cicloDeTrabalho/25;
    
    *CCPR_L   = REG+Vdig >> 2;
    *CCP_CON |= (Vdig & 0b00000011) << 4;
}
