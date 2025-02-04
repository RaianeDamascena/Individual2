#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

#define LED_PIN_RED 13
#define LED_PIN_BLUE 12
#define LED_PIN_GREEN 11

// Estados do semáforo
typedef enum {
    STATE_RED,
    STATE_BLUE,
    STATE_GREEN
} traffic_light_state_t;

volatile traffic_light_state_t current_state = STATE_RED;

// Função de callback do temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    // Alterna entre os estados do semáforo
    switch (current_state) {
        case STATE_RED:
            gpio_put(LED_PIN_RED, true);
            gpio_put(LED_PIN_BLUE, false);
            gpio_put(LED_PIN_GREEN, false);
            current_state = STATE_BLUE;
            break;
        case STATE_BLUE:
            gpio_put(LED_PIN_RED, false);
            gpio_put(LED_PIN_BLUE, true);
            gpio_put(LED_PIN_GREEN, false);
            current_state = STATE_GREEN;
            break;
        case STATE_GREEN:
            gpio_put(LED_PIN_RED, false);
            gpio_put(LED_PIN_BLUE, false);
            gpio_put(LED_PIN_GREEN, true);
            current_state = STATE_RED;
            break;
    }
    return true; // Mantém o temporizador ativo
}

int main() {
    stdio_init_all();

    // Inicializa os GPIOs para os LEDs
    gpio_init(LED_PIN_RED);
    gpio_init(LED_PIN_BLUE);
    gpio_init(LED_PIN_GREEN);

    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    // Configura e inicia o temporizador para 3 segundos (3000 ms)
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Variável para controle da impressão a cada segundo
    absolute_time_t next_log_time = delayed_by_ms(get_absolute_time(), 1000);

    while (true) {
        if (time_reached(next_log_time)) {
            printf("1 segundo passou\n");
            next_log_time = delayed_by_ms(next_log_time, 1000);
        }

        // Pequena pausa para evitar uso excessivo da CPU
        sleep_ms(1);
    }
}
