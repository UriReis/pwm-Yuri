# pwm-Yuri

# Projeto: Controle de Servomotor por PWM no RP2040

Nome: Yuri Silva Reis

Matrícula: TIC370101506

## Descrição
Este projeto implementa o controle de um servomotor utilizando PWM no microcontrolador RP2040. O código simula o controle de ângulo do servomotor padrão no simulador Wokwi, além de testar a interação com um LED RGB na GPIO 12.

## Configuração do PWM e Duty Cycle
Para garantir que o PWM funcione corretamente, foram definidos os seguintes parâmetros:

### 1. Configuração do PWM
- Frequência do PWM: 50 Hz (período de 20ms)
- Divisor de clock (clkdiv): 80
- Valor de wrap (TOP): 31250

### 2. Valores de Pulso para Controle do Servomotor
Os valores de PWM necessários para ajustar o ângulo do servomotor são:

- 180°: Pulso de 2400 µs → Compare Value = 3750
- 90°: Pulso de 1470 µs → Compare Value = 2296
- 0°: Pulso de 500 µs → Compare Value = 781

Esses valores são usados no código para ajustar o posicionamento do servomotor.

## Funcionalidades Implementadas

### 1. Configuração do PWM na GPIO 22
- Configuração do PWM para 50 Hz (período de 20ms), ajustando o divisor de clock e o valor de "wrap" corretamente.

### 2. Controle do Servomotor
- Ajusta o ângulo do servomotor conforme os valores de duty cycle calculados.
- Mantém cada posição por 5 segundos.

### 3. Movimentação Suave do Servomotor
- Implementação de uma rotina que movimenta o braço do servomotor entre 0° e 180° de forma suave.
- O incremento do ciclo ativo é de ±5 µs com um atraso de 10ms para suavizar a transição.

### 4. Teste com LED RGB (GPIO 12)
- O mesmo sinal PWM aplicado ao servomotor é utilizado para acionar um LED RGB, permitindo observar o comportamento do LED com diferentes valores de PWM.

## Estrutura do Código

- `main.c`: Código principal que configura o PWM e executa os comandos de movimentação do servomotor.
- Funções principais:
- `pwm_setup(pin)`: Configura o PWM na GPIO.
- `anguloservo(pin, pulso)`: Ajusta o ângulo do servomotor conforme o pulso definido.
- `circular(pin, comeco, final)`: Implementa a movimentação suave entre 0° e 180°.



## Como Executar
1. Compilar e rodar no VS Code com o SDK do RP2040.
2. Simular no Wokwi seguindo a configuração recomendada.
3. Observar a movimentação do servomotor conforme o código.
4. Analisar o comportamento do LED RGB na GPIO 12.



## Observações sobre o LED RGB
Durante o experimento com o LED RGB (GPIO 12), a mudança fica quase impossível de ser percebida pelo wokwi, porém na placa é  possível perceber de uma forma melhor, vale ressaltar também que caso fosse mudado o duty cicle a luminosidade seria alterada de uma maneira mais consideravel e percepitível. 


## Link para o vídeo da tarefa:

https://youtu.be/ZjHp6eZ35vE?si=MEj3ha89LV0IgVD8
