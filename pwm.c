#include <stdio.h>        // Biblioteca padrão da linguagem C para entrada e saída
#include "pico/stdlib.h"  // Biblioteca do SDK do Raspberry Pi Pico para funcionalidades básicas
#include "hardware/pwm.h" // Biblioteca para controle do hardware de PWM

#define pinled 12   // Define o pino GPIO 12 para o LED (controlado via PWM)
#define servopin 22 // Define o pino GPIO 22 para o servomotor

// Função para configurar o módulo PWM no pino especificado
void pwm_setup(uint pin)
{
    gpio_set_function(pin, GPIO_FUNC_PWM); // Define o pino GPIO como saída PWM

    uint slice = pwm_gpio_to_slice_num(pin); // Obtém o número do slice PWM associado ao pino

    pwm_set_clkdiv(slice, 80); // Define o divisor de clock do PWM para ajustar a frequência

    pwm_set_wrap(slice, 31250); // Define o valor de "wrap" do PWM (duração total do ciclo)

    pwm_set_enabled(slice, true); // Habilita o PWM no slice correspondente
}

// Função para definir o ângulo do servomotor convertendo o pulso em duty cycle
void anguloservo(uint pin, float pulso)
{
    // Converte o tempo do pulso para um valor dentro da faixa do PWM
    uint level = (pulso / 20000) * 31250;
    pwm_set_gpio_level(pin, level); // Define o nível do PWM (duty cycle) no pino especificado
}

// Função para movimentar o servo em um ciclo semicircular entre dois ângulos
void circular(uint pin, float comeco, float final)
{
    float ciclo = 5.0;   // Incremento para mudança gradual do ângulo
    float delay = 10.0;  // Tempo de espera entre as mudanças de ângulo
    uint level;

    // Movimento do servo de "comeco" até "final"
    for (float i = comeco; i <= final; i += ciclo)
    {
        level = (i / 20000) * 31250; // Converte o valor para o PWM
        pwm_set_gpio_level(pin, level); // Aplica o duty cycle
        sleep_ms(delay); // Aguarda um pequeno intervalo para suavizar o movimento
    }

    // Retorno do servo de "final" até "comeco"
    for (float i = final; i >= comeco; i -= ciclo)
    {
        level = (i / 20000) * 31250; // Converte o valor para o PWM
        pwm_set_gpio_level(pin, level); // Aplica o duty cycle
        sleep_ms(delay); // Aguarda um pequeno intervalo para suavizar o movimento
    }
}

// Função principal
int main()
{
    stdio_init_all(); // Inicializa o sistema de entrada e saída padrão (UART)

    pwm_setup(servopin); // Configura o PWM para o pino do servomotor
    pwm_setup(pinled);   // Configura o PWM para o pino do LED

    // Define o ângulo do servo e do LED para 180 graus (pulso de 2400 µs)
    anguloservo(servopin, 2400);
    anguloservo(pinled, 2400);
    printf("Ângulo ajustado para 180 graus\n");

    sleep_ms(5000); // Aguarda 5 segundos

    // Define o ângulo do servo e do LED para 90 graus (pulso de 1470 µs)
    anguloservo(servopin, 1470);
    anguloservo(pinled, 1470);
    printf("Ângulo ajustado para 90 graus\n");

    sleep_ms(5000); // Aguarda 5 segundos

    // Define o ângulo do servo e do LED para 0 graus (pulso de 500 µs)
    anguloservo(servopin, 500);
    anguloservo(pinled, 500);
    printf("Ângulo ajustado para 0 graus\n");

    sleep_ms(5000); // Aguarda 5 segundos

    printf("Iniciando movimentação semicircular\n");

    // Loop principal para manter o servo e o LED em movimento semicircular contínuo
    while (true)
    {
        circular(servopin, 500, 2400); // Movimento semicircular do servomotor
        circular(pinled, 500, 2400);   // Movimento semicircular do LED (simulação)
    }
}
