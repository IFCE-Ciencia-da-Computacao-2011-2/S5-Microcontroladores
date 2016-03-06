#include <stdio.h>

#include "evento/InterrupcaoEventos.h"
#include "sanusb/SanUSB1.h"
#include "semaforo/main.h"

void main() {
    Interrupcoes_init();
    clock_int_4MHz();

    start();
}