# pwm-Yuri

# Projeto: Controle de Servomotor por PWM no RP2040

## Descrição
Este projeto implementa o controle de um servomotor utilizando PWM no microcontrolador RP2040. O código simula o controle de ângulo do servomotor padrão no simulador Wokwi, além de testar a interação com um LED RGB na GPIO 12.

## Cálculos Utilizados
Para garantir que o PWM funcione corretamente, alguns cálculos foram necessários:

### 1. Cálculo do TOP (Wrap Value)
O período do PWM para controlar o servomotor deve ser 20 ms (50 Hz). A fórmula para calcular o TOP do PWM é:

\[
\text{TOP} = \frac{\text{Clock PWM}}{\text{clkdiv} \times \text{Frequência desejada}} - 1
\]

Sabendo que o clock base do RP2040 é 125 MHZ e usamos um clkdiv = 80, temos:

\[
\text{TOP} = \frac{125000000}{80 \times 50} - 1 = 31250
\]

### 2. Cálculo do Duty Cycle para os Ângulos do Servomotor
Os valores de PWM necessários para ajustar o ângulo do servomotor são:

- 180° → Pulso de 2400 µs
- 90° → Pulso de 1470 µs
- 0° → Pulso de 500 µs

Para converter isso em valores de compare level do PWM:

\[
\text{Compare Value} = \left(\frac{\text{Pulso (µs)}}{\text{Período (µs)}} \right) \times \text{TOP}
\]

Exemplo para 180°:

\[
\text{Compare Value} = \left(\frac{2400}{20000} \right) \times 31250 = 3750
\]

Os mesmos cálculos são feitos para os outros ângulos:

- 90° → \( \frac{1470}{20000} \times 31250 = 2296 \)
- 0° → \( \frac{500}{20000} \times 31250 = 781 \)

## Funcionalidades Implementadas

### 1. Configuração do PWM na GPIO 22
- Configuração do PWM para 50 Hz (período de 20ms), ajustando o divisor de clock e o valor de "wrap" corretamente.

### 2. Controle do Servomotor
- Ajusta o ângulo do servomotor conforme os valores de duty cycle calculados.
- Mantém cada posição por 5 segundos.

### 3. Movimentação Suave do Servomotor
- Implementação de uma rotina que movimenta o braço do servomotor entre 0° e 180° de forma suave.
- O incremento do ciclo ativo é de ±5 µs com um atraso de 10ms para suavizar a transição.

### 4. Teste com LED RGB (GPIO 13)
- O mesmo sinal PWM aplicado ao servomotor é utilizado para acionar um LED RGB, permitindo observar o comportamento do LED com diferentes valores de PWM.

## Estrutura do Código

- `main.c`: Código principal que configura o PWM e executa os comandos de movimentação do servomotor.
- Funções principais:
  - `pwm_setup(pin)`: Configura o PWM na GPIO.
  - `anguloservo(pin, pulso)`: Ajusta o ângulo do servomotor conforme o pulso definido.
  - `circular(pin, comeco, final)`: Implementa a movimentação suave entre 0° e 180°.

## Requisitos do Projeto
- Configuração do PWM na GPIO 22 com frequência de 50 Hz.
- Controle do servomotor com ajustes de duty cycle.
- Movimentação periódica do braço do servomotor.
- Teste do LED RGB para analisar o comportamento do PWM na GPIO 13.
- Uso do Wokwi para simulação.
- Versionamento no GitHub com README.md explicativo.

## Como Executar
1. Compilar e rodar no VS Code com o SDK do RP2040.
2. Simular no Wokwi seguindo a configuração recomendada.
3. Observar a movimentação do servomotor conforme o código.
4. Analisar o comportamento do LED RGB na GPIO 13.

## Entrega
- Código-fonte completo com comentários e bem estruturado.
- README.md com instruções detalhadas.
- Vídeo de até 3 minutos demonstrando o funcionamento.
- Repositório no GitHub para versionamento e submissão da tarefa.

## Observações sobre o LED RGB
Durante o experimento com o LED RGB (GPIO 13), o comportamento da iluminação pode variar dependendo do duty cycle aplicado. Essa observação deve ser descrita no vídeo final.

---
Desenvolvido para a Unidade 4 - Capítulo 7 da disciplina de Sistemas Embarcados.

