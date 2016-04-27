#ifndef SANUSB_H
#define SANUSB_H

#include <p18f4550.h>

extern void interrupcao(void);

// Declaração externa para funções assembly -------
//extern void tempo_us(unsigned char);

#define tmp                   OSCCONbits.IRCF1
#define timer0_interrompeu    INTCONbits.TMR0IF
#define timer1_interrompeu    PIR1bits.TMR1IF
#define timer2_interrompeu    PIR1bits.TMR2IF
#define timer3_interrompeu    PIR2bits.TMR3IF
#define ext0_interrompeu      INTCONbits.TMR0IF
#define ext1_interrompeu      INTCON3bits.INT1IF
#define ext2_interrompeu      INTCON3bits.INT2IF
#define ad_interrompeu        PIR1bits.ADIF
#define serial_interrompeu    PIR1bits.RCIF

/**
 * Lê o primeiro caractere recebido que está no buffer de recepção RS-232.
 * 
 * Observações: Quando outro byte é recebido, ele é armazenado na próxima posição 
 * livre do buffer de recepção, cuja capacidade é de 16 bytes.
 */
#define le_serial      getcUSART
#define escreve_serial printf
#define getchar        getcUSART
#define putc           putcUSART
#define kbhit          DataRdyUSART()
#define envia_byte() (!TXSTAbits.TRMT)

/*************************************************
 * Todos os pinos são inicialmente default como entrada TRIS= 0B11111111
 ***********************************************/
extern void portaA_saida(void);
extern void portaB_saida(void);
extern void portaC_saida(void);

extern void portaA_entrada(void);
extern void portaB_entrada(void);
extern void portaC_entrada(void);

#define entrada_pin_a0 PORTAbits.RA0
#define entrada_pin_a1 PORTAbits.RA1
#define entrada_pin_a2 PORTAbits.RA2
#define entrada_pin_a3 PORTAbits.RA3
#define entrada_pin_a4 PORTAbits.RA4
#define entrada_pin_a5 PORTAbits.RA5

#define entrada_pin_b0 PORTBbits.RB0
#define entrada_pin_b1 PORTBbits.RB1
#define entrada_pin_b2 PORTBbits.RB2
#define entrada_pin_b3 PORTBbits.RB3
#define entrada_pin_b4 PORTBbits.RB4
#define entrada_pin_b5 PORTBbits.RB5
#define entrada_pin_b6 PORTBbits.RB6
#define entrada_pin_b7 PORTBbits.RB7

#define entrada_pin_c0 PORTCbits.RC0
#define entrada_pin_c1 PORTCbits.RC1
#define entrada_pin_c2 PORTCbits.RC2
#define entrada_pin_c6 PORTCbits.RC6
#define entrada_pin_c7 PORTCbits.RC7

#define entrada_pin_d0 PORTBbits.RD0
#define entrada_pin_d1 PORTBbits.RD1
#define entrada_pin_d2 PORTBbits.RD2
#define entrada_pin_d3 PORTBbits.RD3
#define entrada_pin_d4 PORTBbits.RD4
#define entrada_pin_d5 PORTBbits.RD5
#define entrada_pin_d6 PORTBbits.RD6
#define entrada_pin_d7 PORTBbits.RD7

#define entrada_pin_e3 PORTEbits.RE3

#define false 0
#define true 1
#define byte int
#define boolean short int
#define getc getch

#define pin_a0  31744
#define pin_a1  31745
#define pin_a2  31746
#define pin_a3  31747
#define pin_a4  31748
#define pin_a5  31749
#define porta   3968  // 0xf80 = 3968 * 8 = 31744

#define pin_b0  31752
#define pin_b1  31753
#define pin_b2  31754
#define pin_b3  31755
#define pin_b4  31756
#define pin_b5  31757
#define pin_b6  31758
#define pin_b7  31759
#define portb   3969 // 0xf81 = 3969 * 8 = 31752

#define pin_c0  31760
#define pin_c1  31761
#define pin_c2  31762
#define pin_c6  31766
#define pin_c7  31767
#define portc   3970 // 0xf82 = 3970 * 8 = 31760

#define pin_d0  31768
#define pin_d1  31769
#define pin_d2  31770
#define pin_d3  31771
#define pin_d4  31772
#define pin_d5  31773
#define pin_d6  31774
#define pin_d7  31775
#define portd   3971 // 0xf83 = 3971 * 8 = 31768

#define port_e3 31779 // port_e = 0xf84 = 3972 * 8 = 31776 +3 = 31779

extern void habilita_wdt(void);
extern void limpaflag_wdt(void);

extern void nivel_alto(unsigned int pino);
extern void nivel_baixo(unsigned int pino);
extern void inverte_saida(unsigned int pino);
extern void saida_pino(unsigned int pino, short int alto);
boolean entrada_pino(unsigned int pino);

extern void tempo_us(unsigned int i);
extern void tempo_ms(unsigned int i);

#define AN0                    0x0E
#define AN0_a_AN1              0x0D
#define AN0_a_AN2              0x0C
#define AN0_a_AN3              0x0B
#define AN0_a_AN4              0x0A
#define AN0_a_AN8              0x06
#define AN0_a_AN9              0x05
#define AN0_a_AN10             0x04
#define AN0_a_AN11             0x03
#define AN0_a_AN12             0x02
#define AN0_a_AN1_VREF_POS     0x1D  //(VREF+ -> AN3)
#define AN0_a_AN1_VREF_POS_NEG 0x3D    //(VREF+ -> AN3 e VREF- -> AN2)

extern void habilita_canal_AD(char canal);
extern int le_AD8bits(short int conv);
extern unsigned int le_AD10bits(short int conv);

extern void multiplica_timer16bits(char timer,unsigned int multiplica);
extern void tempo_timer16bits(char timer,unsigned int conta_us);
extern void timer0_ms (unsigned int cx);

extern void escreve_eeprom(unsigned char endereco, unsigned char dado);
extern unsigned char le_eeprom(unsigned char endereco);

extern void clock_int_4MHz(void);

extern void taxa_serial(unsigned long taxa);
extern void serial_putc(char c);

extern void swputc(char c);
extern void sputc(unsigned char c);

extern void sendrw(static char rom *ByteROM);
extern void sendr(static char rom *ByteROM);
extern void sendsw(char string[]);
extern void sends(unsigned char string[]);
extern void sendnum(unsigned int numero);

extern void SetaPWM1(int frequencia, int cicloDeTrabalho);
extern void SetaPWM2(int frequencia, int cicloDeTrabalho);

#endif
