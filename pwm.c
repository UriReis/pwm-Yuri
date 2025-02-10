#include <stdio.h> //biblioteca padrão da linguagem C
#include "pico/stdlib.h" //subconjunto central de bibliotecas do SDK Pico
#include "hardware/pwm.h" //biblioteca para controlar o hardware de PWM

#define pinled 12 //pino do LED conectado a GPIO como PWM
#define servopin 22 // pino do servomotor


const uint16_t LED_STEP = 200; //passo de incremento/decremento para o duty cycle do LED
uint16_t led_level = 200; //nível inicial do pwm (duty cycle)

//função para configurar o módulo PWM
void pwm_setup(uint pin)
{
    gpio_set_function(pin, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM

    uint slice = pwm_gpio_to_slice_num(pin); //obter o canal PWM da GPIO

    pwm_set_clkdiv(slice, 80); //define o divisor de clock do PWM

    pwm_set_wrap(slice, 31250); //definir o valor de wrap

    pwm_set_enabled(slice, true); //habilita o pwm no slice correspondente
}

void anguloservo(uint pin, float pulso){

    uint level = (pulso / 20000.0) * 31250;
    pwm_set_gpio_level(pin, level); //define o nível atual do PWM (duty cycle)

}

void circular( uint pin, float comeco, float final){
    float ciclo = 5.0;
    float delay = 10.0;
}


//função principal
int main()
{
    stdio_init_all(); //inicializa o sistema padrão de I/O
    
    pwm_setup(servopin); //configura o PWM
   //pwm_setup(pinled);

    

    anguloservo(servopin, 2400);
    printf("Ângulo ajustado para 180 graus");

    sleep_ms(5000);

    anguloservo(servopin,1470);
    printf("Ângulo ajustado para 90 graus");

    sleep_ms(5000);

    anguloservo(servopin,1470);
    printf("Ângulo ajustado para 0 graus");

    sleep_ms(5000);

    printf(" Iniciando movimentação semicircular");

    //loop principal
    while (true) {

        
        /*if (up_down) 
        {
            led_level += LED_STEP; // Incrementa o nível do LED
            if (led_level >= WRAP_PERIOD)
                up_down = 0; // Muda direção para diminuir quando atingir o período máximo
        }
        else
        {
            led_level -= LED_STEP; // Decrementa o nível do LED
            if (led_level <= LED_STEP)
                up_down = 1; // Muda direção para aumentar quando atingir o mínimo
        }*/

    }
}