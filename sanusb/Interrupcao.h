#ifndef INTERRUPCAO_H
#define	INTERRUPCAO_H

extern void _startup(void); // Realocação de memória SanUSB

#define timer0                0xF220
#define timer1                0x9D01
#define timer2                0x9D02
#define timer3                0xA002

#define ext0                  0xF210
#define ext1                  0xF008
#define ext2                  0xF010

#define ad                    0x9D40
#define recep_serial          0x9D20

extern void habilita_interrupcao(unsigned int tipo);

#endif
