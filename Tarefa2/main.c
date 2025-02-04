#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"

#define LED_PIN_RED 13
#define LED_PIN_BLUE 12
#define LED_PIN_GREEN 11
#define BUTTON_PIN 5

// Estados do sistema
typedef enum {
    STATE_OFF,       // LEDs desligados
    STATE_ALL_ON,    // Todos os LEDs ligados
    STATE_TWO_ON,    // Dois LEDs ligados
    STATE_ONE_ON     // Apenas um LED ligado
} traffic_light_state_t;

volatile traffic_light_state_t current_state = STATE_OFF;
volatile bool processing_timers = false; // Bloqueia novas execuções enquanto os temporizadores estão ativos

// Protótipos das funções
int64_t state_transition_callback(alarm_id_t id, void *user_data);
void set_leds(bool red, bool blue, bool green);

// Callback para transições entre os estados
int64_t state_transition_callback(alarm_id_t id, void *user_data) {
    switch (current_state) {
        case STATE_ALL_ON:
            set_leds(true, true, false); // Dois LEDs ligados
            current_state = STATE_TWO_ON;
            break;
        case STATE_TWO_ON:
            set_leds(true, false, false); // Apenas um LED ligado
            current_state = STATE_ONE_ON;
            break;
        case STATE_ONE_ON:
            set_leds(false, false, false); // LEDs desligados
            current_state = STATE_OFF;
            processing_timers = false; // Permite novas interações com o botão
            break;
        default:
            break;
    }

    return current_state == STATE_OFF ? 0 : 3000 * 1000; // 3 segundos para próximo estado
}

// Função para definir o estado dos LEDs
void set_leds(bool red, bool blue, bool green) {
    gpio_put(LED_PIN_RED, red);
    gpio_put(LED_PIN_BLUE, blue);
    gpio_put(LED_PIN_GREEN, green);
}

int main() {
    stdio_init_all();

    // Inicializa os GPIOs para LEDs e botão
    gpio_init(LED_PIN_RED);
    gpio_init(LED_PIN_BLUE);
    gpio_init(LED_PIN_GREEN);
    gpio_init(BUTTON_PIN);

    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN); // Resistor pull-up interno para o botão

    while (true) {
        // Detecta clique no botão apenas se os temporizadores não estiverem ativos
        if (!processing_timers && gpio_get(BUTTON_PIN) == 0) {
            set_leds(true, true, true); // Liga todos os LEDs
            current_state = STATE_ALL_ON;
            processing_timers = true;

            // Inicia a primeira chamada do alarme com 3 segundos
            add_alarm_in_ms(3000, state_transition_callback, NULL, true);

            // Espera o botão ser solto para evitar múltiplos acionamentos
            while (gpio_get(BUTTON_PIN) == 0) {
                sleep_ms(10);
            }
        }

        // Pausa pequena para evitar uso excessivo da CPU
        sleep_ms(10);
    }

    return 0;
}
