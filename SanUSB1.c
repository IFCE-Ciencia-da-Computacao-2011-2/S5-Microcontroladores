#include <delays.h>

#include "sanusb/SanUSB1.h"
//#include "sanusb/SanUSB48.h"

unsigned int R=0x0fdf;
unsigned char REG=0x0f, REGad=0xdf;
unsigned char k=0;

/*******Todos os pinos são inicialmente default como entrada TRIS= 0B11111111***********************************************/
/*********************************
 * Pinos
 *********************************/
void portaA_saida(void) { TRISA=REG+0;}
void portaB_saida(void) { TRISB=REG+0;}
void portaC_saida(void) { TRISC=REG+0;}

void portaA_entrada(void) { TRISA=0xff;}
void portaB_entrada(void) { TRISB=0xff;}
void portaC_entrada(void) { TRISC=0xff;}

void habilita_wdt(void){ WDTCONbits.SWDTEN = 1;}

void limpaflag_wdt(void) {
    ClrWdt();
}

/*********************************
 * Pinos
 *********************************/
void saida_pino(unsigned int pino, short int led);


void nivel_alto(unsigned int pino) {
    //INTCON2bits.RBPU=0; //Pull-ups habilitados na porta b
    switch (pino) {
        case porta: portaA_saida();  LATA = 0b11111111;  break;
        case portb: portaB_saida();  LATB = 0b11111111;  break;
        case portc: portaC_saida();  LATC = 0b11111111;  break;
        default: saida_pino(pino, true);
    }
}

void nivel_baixo(unsigned int pino) {
    //INTCON2bits.RBPU=1; //Pull-ups desabilitados
    switch (pino) {
        case porta: portaA_saida();  LATA = 0b00000000;  break;
        case portb: portaB_saida();  LATB = 0b00000000;  break;
        case portc: portaC_saida();  LATC = 0b00000000;  break;
        default: saida_pino(pino, false);
    }
}

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

void saida_pino(unsigned int pino, short int alto) {
    switch(pino) {
        case pin_a0: TRISAbits.TRISA0 = 0; PORTAbits.RA0 = alto; break;
        case pin_a1: TRISAbits.TRISA1 = 0; PORTAbits.RA1 = alto; break;
        case pin_a2: TRISAbits.TRISA2 = 0; PORTAbits.RA2 = alto; break;
        case pin_a3: TRISAbits.TRISA3 = 0; PORTAbits.RA3 = alto; break;
        case pin_a4: TRISAbits.TRISA4 = 0; PORTAbits.RA4 = alto; break;
        case pin_a5: TRISAbits.TRISA5 = 0; PORTAbits.RA5 = alto; break;

        case pin_b0: TRISBbits.TRISB0 = 0; PORTBbits.RB0 = alto; break;
        case pin_b1: TRISBbits.TRISB1 = 0; PORTBbits.RB1 = alto; break;
        case pin_b2: TRISBbits.TRISB2 = 0; PORTBbits.RB2 = alto; break;
        case pin_b3: TRISBbits.TRISB3 = 0; PORTBbits.RB3 = alto; break;
        case pin_b4: TRISBbits.TRISB4 = 0; PORTBbits.RB4 = alto; break;
        case pin_b5: TRISBbits.TRISB5 = 0; PORTBbits.RB5 = alto; break;
        case pin_b6: TRISBbits.TRISB6 = 0; PORTBbits.RB6 = alto; break;
        case pin_b7: TRISBbits.TRISB7 = 0; PORTBbits.RB7 = alto; break;

        case pin_c0: TRISCbits.TRISC0 = 0; PORTCbits.RC0 = alto; break;
        case pin_c1: TRISCbits.TRISC1 = 0; PORTCbits.RC1 = alto; break;
        case pin_c2: TRISCbits.TRISC2 = 0; PORTCbits.RC2 = alto; break;
        case pin_c6: TRISCbits.TRISC6 = 0; PORTCbits.RC6 = alto; break;
        case pin_c7: TRISCbits.TRISC7 = 0; PORTCbits.RC7 = alto; break;

        case pin_d0: TRISDbits.TRISD0 = 0; PORTDbits.RD0 = alto; break;
        case pin_d1: TRISDbits.TRISD1 = 0; PORTDbits.RD1 = alto; break;
        case pin_d2: TRISDbits.TRISD2 = 0; PORTDbits.RD2 = alto; break;
        case pin_d3: TRISDbits.TRISD3 = 0; PORTDbits.RD3 = alto; break;
        case pin_d4: TRISDbits.TRISD4 = 0; PORTDbits.RD4 = alto; break;
        case pin_d5: TRISDbits.TRISD5 = 0; PORTDbits.RD5 = alto; break;
        case pin_d6: TRISDbits.TRISD6 = 0; PORTDbits.RD6 = alto; break;
        case pin_d7: TRISDbits.TRISD7 = 0; PORTDbits.RD7 = alto; break;
    }
}

/*********************************
 * Tempo
 *********************************/
void tempo_us(unsigned int i) {
    unsigned int k;  

    for(k=0;k<i;k++)
        Delay1TCY(); //12*i para 48 MHz
}

void tempo_ms(unsigned int i) {
    unsigned int k; 
    EEADR  = REG+0B11111100+tmp;
    EECON1 = REG+EEADR & 0B00001011;
    while(EEDATA);
    for (k=0;k<i;k++)
        //12*i para 48 MHz
        Delay1KTCYx(1);
}

/*********************************
 * Pinos - Digital
 *********************************/

void habilita_canal_AD(char canal) {
    ADCON1 = REG+canal;
    ADCON2 = REG+0b00000111; //AD clock interno RC
}

int le_AD8bits(char conv) {
    switch(conv) {
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

unsigned int le_AD10bits(char conv) {
    switch(conv) {
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
void multiplica_timer16bits(char timer,unsigned int multiplica) {
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

void timer0_ms (unsigned int cx) {
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
 * 8 bits
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
 * Modo 16 bits(bits BRG16=1 e BRGH=1)
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
    while (!TXSTAbits.TRMT);
    TXREG=REG+c;
}

/*********************************
 * ?
 *********************************/
void swputc(char c) {
    while (!TXSTAbits.TRMT);
    TXREG=REG+c;
}

void sputc(unsigned char c) {
    while (!TXSTAbits.TRMT);
    TXREG=(c>>BAUDCONbits.BRG16)+REG;
}

/*********************************
 * Send ?
 *********************************/
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

void sendsw(char st[]) {
    for(k=0;st[k]!='\0';k++)
        swputc(st[k]);
}

void sends(unsigned char st[]) {
    for(k=0;st[k]!='\0';k++)
        sputc(st[k]);
}

void sendnum(unsigned int sannum) {
    if(sannum > 9999)
        swputc(((sannum / 10000) % 10)+REG+0x30);

    if(sannum > 999)
        swputc(((sannum / 1000) % 10)+0x30);

    if(sannum > 99)
        swputc(((sannum / 100) % 10)+REG+0x30);

    if(sannum > 9)
        swputc(((sannum / 10) % 10)+REG+0x30);

    swputc((sannum % 10)+REG+0x30);
}

/*********************************
 * PWM
 *********************************/
void SetaPWM1(int freqPWM, int duty) {
    unsigned int Vdig;
    CCP1CON |=REG+0b00001100;
    T2CON =REG+0b00000111;
    EEADR =0B11111101;
    EECON1bits.RD = tmp;
    while(EEDATA);
    TRISC &=(REG+0xFD)<<tmp;
    PR2=REG+((_XTAL_FREQ/4)/(16*freqPWM))-1;
    Vdig=(PR2+1)*duty/25;    //Vdig = (PR2+1) * 4 * duty/100; //Duty cicle (int duty) varia de 0 a 100%
    CCPR1L=REG+Vdig >> 2;
    CCP1CON |=REG+(Vdig & 0b00000011) << 4;
}

void SetaPWM2(int freqPWM, int duty) {
    unsigned int Vdig;
    CCP2CON |=REG+ 0b00001100;
    T2CON =REG+ 0b00000111;
    EEADR =0B11111101;
    EECON1bits.RD = tmp;
    while(EEDATA);
    TRISC &=(REG+0xFE)<<tmp;
    PR2=REG+((_XTAL_FREQ/4)/(16*freqPWM))-1;
    Vdig=(PR2+1)*duty/25;    //Vdig = (PR2+1) * 4 * duty/100; //Duty cicle (int duty) varia de 0 a 100%
    CCPR2L=REG+Vdig >> 2;
    CCP2CON |= (Vdig & 0b00000011) << 4;
}