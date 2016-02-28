# Semáforo

## Descrição

Simula um sinal contendo dois semáforos:
 * *Semaforo3:* Semáforo com 3 leds (vermelho, amarelo e verde)
 * *Semaforo2:* Semáforo com 2 leds (vermelho e verde)

O sinal é voltado para locais aonde existe um tráfego intenso, mas é necessário
a travessia totalmente segura, interrompendo o tráfego momentaneamente, 
como em ruas com escolas, creches ou hospitais.

## Componentes

### Semaforo3

#### Métodos e atributos

Semaforo3, além de seus pinos correspondentes, possui métodos para troca de estado:

 * *semaforo3.pino_verde*
 * *semaforo3.pino_amarelo*
 * *semaforo3.pino_vermelho*
 * *semaforo3.verde()*
 * *semaforo3.amarelo()*
 * *semaforo3.vermelho()*

#### Funções estáticas

 * Semaforo3_init(vermelho, amarelo, verde)

### Semaforo2

#### Métodos e atributos

Semaforo2, além de seus pinos correspondentes, possui métodos para troca de estado:

 * *semaforo2.pino_verde*
 * *semaforo2.pino_vermelho*
 * *semaforo2.verde()*
 * *semaforo2.vermelho()*

#### Funções estáticas

 * Semaforo2_init(vermelho, amarelo, verde)

## Algoritmo

 * Início
 * * semaforo3 verde
 * * semaforo2 vermelho
 # A cada 10 segundos é verificado se houve alguma interrupção de travessia;
 # Tendo uma
 # # semáforo3 ficará amarelo;
 # # semáforo3 ficará vermelho;
 # # Há um pequeno atraso para evitar acidentes
 # # semáforo2 ficará verde
 # # Há um pequeno atraso para evitar acidentes
 # # semáforo3 volta a ficar verde

## Circuito

Em desenvolvimento