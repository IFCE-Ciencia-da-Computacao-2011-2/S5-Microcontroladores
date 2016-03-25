#include <stdio.h>
#include "sanusb/SanUSB1.h"
#include "Display.h"

boolean not(boolean valor);

unsigned char desenhos[] = {
    0b11111100, // 0
    0b01100000, // 1
    0b11011010, // 2
    0b11110010, // 3
    0b01100110, // 4
    0b10110110, // 5
    0b10111110, // 6
    0b11100000, // 7
    0b11111110, // 8
    0b11100110, // 9
    
    0b11101110, // A
    0b00111110, // B
    0b10011100, // C
    0b01111010, // D
    0b10011110, // E
    0b10001110, // F
};

void Display7Seg_caractere(void * self, Caractere caractere);

void Display7Seg_estado(void * self, boolean ligar);
void Display7Seg_liga(void * self);
void Display7Seg_desliga(void * self);

void Display7Seg_init(Display7Seg * display, DisplayTipo tipo, unsigned int pino_controle) {
    display->tipo = tipo;
    display->controle = pino_controle;
    
    display->caractere = &Display7Seg_caractere;

    display->liga    = &Display7Seg_liga;
    display->desliga = &Display7Seg_desliga;
}

void Display7Seg_caractere(void * self, Caractere caractere) {
    Display7Seg * display = (Display7Seg *) self;
    unsigned char character = desenhos[caractere];
    boolean acender = false;

    unsigned char i = 0;
    unsigned char comparador = 0b10000000;

    if (display->tipo == ANODO_COMUM)
        character = ~character;

    for (i=0; i<8; i++) {
        acender = (comparador & character) == comparador;

        saida_pino(display->pins[i], acender);
        comparador = comparador >> 1;
    }
}

void Display7Seg_liga(void * self) {
    Display7Seg_estado(self, true);
}

void Display7Seg_desliga(void * self) {
    Display7Seg_estado(self, false);
}

void Display7Seg_estado(void * self, boolean ligar) {
    Display7Seg * display = (Display7Seg *) self;

    if (display->tipo == CATODO_COMUM)
        ligar = !ligar;

    if (display->controle != NULL)
        saida_pino(display->controle, ligar);
}