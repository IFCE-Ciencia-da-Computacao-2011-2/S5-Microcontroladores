# Sem�foro

## Descri��o

Simula um sinal contendo dois sem�foros:
 * *Semaforo3:* Sem�foro com 3 leds (vermelho, amarelo e verde)
 * *Semaforo2:* Sem�foro com 2 leds (vermelho e verde)

O sinal � voltado para locais aonde existe um tr�fego intenso, mas � necess�rio
a travessia totalmente segura, interrompendo o tr�fego momentaneamente, 
como em ruas com escolas, creches ou hospitais.

## Componentes

### Semaforo3

#### M�todos e atributos

Semaforo3, al�m de seus pinos correspondentes, possui m�todos para troca de estado:

 * *semaforo3.pino_verde*
 * *semaforo3.pino_amarelo*
 * *semaforo3.pino_vermelho*
 * *semaforo3.verde()*
 * *semaforo3.amarelo()*
 * *semaforo3.vermelho()*

#### Fun��es est�ticas

 * Semaforo3_init(vermelho, amarelo, verde)

### Semaforo2

#### M�todos e atributos

Semaforo2, al�m de seus pinos correspondentes, possui m�todos para troca de estado:

 * *semaforo2.pino_verde*
 * *semaforo2.pino_vermelho*
 * *semaforo2.verde()*
 * *semaforo2.vermelho()*

#### Fun��es est�ticas

 * Semaforo2_init(vermelho, amarelo, verde)

## Algoritmo

 * In�cio
 * * semaforo3 verde
 * * semaforo2 vermelho
 # A cada 10 segundos � verificado se houve alguma interrup��o de travessia;
 # Tendo uma
 # # sem�foro3 ficar� amarelo;
 # # sem�foro3 ficar� vermelho;
 # # H� um pequeno atraso para evitar acidentes
 # # sem�foro2 ficar� verde
 # # H� um pequeno atraso para evitar acidentes
 # # sem�foro3 volta a ficar verde

## Circuito

Em desenvolvimento