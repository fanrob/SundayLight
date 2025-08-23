#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"

// Настройки
const uint LED_PIN = 15;      // К какому пину подключён свет
const uint ADC_PIN = 26;      // АЦП0 — GPIO26
const float THRESHOLD_ON = 2.0f;   // Вольты для включения
const float THRESHOLD_OFF = 1.5f;  // Вольты для выключения

int main() {
    stdio_init_all();

    adc_init();
    adc_gpio_init(ADC_PIN);
    adc_select_input(0); // GPIO26 = ADC0

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    bool light_on = false;

    while (true) {
        uint16_t raw = adc_read();
        float voltage = raw * 3.3f / 4095.0f; // Преобразуем в напряжение

        if (!light_on && voltage >= THRESHOLD_ON) {
            gpio_put(LED_PIN, 1);
            light_on = true;
        } else if (light_on && voltage <= THRESHOLD_OFF) {
            gpio_put(LED_PIN, 0);
            light_on = false;
        }

        sleep_ms(100);
    }
}