#include <stdio.h>        //biblioteca padrão da linguagem C
#include "pico/stdlib.h"  //subconjunto central de bibliotecas do SDK Pico
#include "hardware/pwm.h" //biblioteca para controlar o hardware de PWM

#define pinled 12   // pino do LED conectado a GPIO como PWM
#define servopin 22 // pino do servomotor

// função para configurar o módulo PWM
void pwm_setup(uint pin)
{
    gpio_set_function(pin, GPIO_FUNC_PWM); // habilitar o pino GPIO como PWM

    uint slice = pwm_gpio_to_slice_num(pin); // obter o canal PWM da GPIO

    pwm_set_clkdiv(slice, 80); // define o divisor de clock do PWM

    pwm_set_wrap(slice, 31250); // definir o valor de wrap

    pwm_set_enabled(slice, true); // habilita o pwm no slice correspondente
}

void anguloservo(uint pin, float pulso)
{

    uint level = (pulso / 20000) * 31250;
    pwm_set_gpio_level(pin, level); // define o nível atual do PWM (duty cycle)
}

void circular(uint pin, float comeco, float final)
{
    float ciclo = 5.0;
    float delay = 10.0;
    uint level;

    for (float i = comeco; i <= final; i = i + ciclo)
    {

        level = (i / 20000) * 31250;
        pwm_set_gpio_level(pin, level);
        sleep_ms(delay);
    }
    for (float i = final; i >= comeco; i = i - ciclo)
    {

        level = (i / 20000) * 31250;
        pwm_set_gpio_level(pin, level);
        sleep_ms(delay);
    }
}

// função principal
int main()
{
    stdio_init_all(); // inicializa o sistema padrão de I/O

    pwm_setup(servopin); // configura o PWM
    pwm_setup(pinled);

    anguloservo(servopin, 2400);
    //anguloservo(pinled, 2400);
    anguloservo(pinled, 2400*2); // Para a placca
    printf("Ângulo ajustado para 180 graus\n");

    sleep_ms(5000);

    anguloservo(servopin, 1470);
    anguloservo(pinled, 1470);
    printf("Ângulo ajustado para 90 graus\n");

    sleep_ms(5000);

    anguloservo(servopin, 500);
    //anguloservo(pinled, 500);
    anguloservo(pinled, 500/2);// Para a placa
    printf("Ângulo ajustado para 0 graus\n");

    sleep_ms(5000);

    printf("Iniciando movimentação semicircular\n");

    // loop principal
    while (true)
    {

        //circular(pinled, 500,2400);
        circular(pinled, 500/2, 2400*2);//para a placa
        circular(servopin, 500, 2400);
    }
}