## Descrição

Este repositório contém dois códigos desenvolvidos para a plataforma **Raspberry Pi Pico W**, utilizando o **Pico SDK** para controlar LEDs de um semáforo e um sistema de temporização acionado por um botão.O objetivo principal é aprender a utilizar funções de temporização como `add_repeating_timer_ms()` e `add_alarm_in_ms()` para criar sistemas de temporização simples e interativos com LEDs e botões.

---

## 1. **Tarefa 1**

### Objetivo:
Desenvolver um semáforo controlado por temporização de 3 segundos para cada alteração de sinal. O semáforo deve começar com o LED **vermelho** aceso, seguido pelo **azul** e depois **verde**.

### Funcionamento:
- **Microcontrolador**: Raspberry Pi Pico W.
- **Componentes**:
  - 3 LEDs (vermelho, azul, verde).
  - 3 resistores de 330 Ω para limitar a corrente.
  - **Função principal**: O temporizador de 3 segundos é controlado pela função `add_repeating_timer_ms()`, que chama periodicamente a função de callback `repeating_timer_callback()`.
  - **Estrutura do código**:
    - O semáforo inicia com o LED **vermelho** ligado.
    - A cada 3 segundos, o estado do semáforo muda para o próximo LED (azul → verde → vermelho).
    - Durante o tempo de execução, a rotina principal imprime a mensagem "1 segundo passou" a cada segundo.
  
### Requisitos para Funcionamento:
1. **Componentes**:
   - 3 LEDs conectados aos pinos **11**, **12** e **13** do Raspberry Pi Pico.
   - 3 resistores de 330 Ω.
2. **Alteração de sinal**:
   - O temporizador é ajustado para 3 segundos, utilizando `add_repeating_timer_ms()`.
   - O estado dos LEDs é alternado na função de callback do temporizador.
3. **Impressão de mensagem**:
   - A cada 1 segundo, o código imprime a mensagem "1 segundo passou" via porta serial.
4. **Ferramenta Educacional**:
   - O código foi simulado no BitDogLab utilizando o LED RGB no Raspberry Pi Pico W (pinos 11, 12 e 13).

### Fluxograma de Funcionamento:
O fluxo do semáforo é o seguinte:
1. **Estado Inicial (Vermelho)**: LED vermelho aceso.
2. **Após 3 segundos**: LED amarelo aceso.
3. **Após mais 3 segundos**: LED verde aceso.
4. **Ciclo continua** repetidamente.

---

## 2. **Tarefa 2**

### Objetivo:
Desenvolver um sistema de temporização para o acionamento de LEDs a partir de um botão (pushbutton). A cada clique, os LEDs devem passar por um ciclo de acendimento, começando com todos os LEDs ligados, seguido por dois LEDs e, por fim, apenas um LED.

### Funcionamento:
- **Microcontrolador**: Raspberry Pi Pico W.
- **Componentes**:
  - 3 LEDs (azul, vermelho e verde).
  - 3 resistores de 330 Ω.
  - **Botão (Pushbutton)**: Controla o ciclo de acionamento dos LEDs.
  - **Função principal**: O temporizador de 3 segundos é controlado pela função `add_alarm_in_ms()`, com a mudança de estado dos LEDs implementada em funções de callback.
  - O ciclo de LEDs só pode ser iniciado após o último LED ser desligado, evitando múltiplos acionamentos.

### Requisitos para Funcionamento:
1. **Componentes**:
   - 3 LEDs conectados aos pinos **11**, **12** e **13** do Raspberry Pi Pico.
   - 3 resistores de 330 Ω.
   - Botão conectado ao pino **GPIO 5**.
2. **Alteração de sinal**:
   - Ao pressionar o botão, todos os LEDs são acesos inicialmente.
   - A cada 3 segundos, o estado dos LEDs muda para 2 acesos, depois 1 aceso e finalmente todos desligados.
   - O temporizador é ajustado para 3 segundos, utilizando `add_alarm_in_ms()`.
3. **Controle do botão**:
   - O botão só pode alterar o estado dos LEDs quando o último LED for desligado, para evitar múltiplos acionamentos enquanto os temporizadores estão ativos.

### Fluxograma de Funcionamento:
O ciclo dos LEDs segue a ordem:
1. **Todos os LEDs acesos**.
2. **Após 3 segundos**: Dois LEDs acesos.
3. **Após mais 3 segundos**: Um LED aceso.
4. **Após mais 3 segundos**: Todos os LEDs desligados, pronto para reiniciar o ciclo com o próximo clique no botão.

---

## Desenvolvedor

**Raiane Damascena da Paixão**  
Email: rai.paixao2012@gmail.com
